/*
 *
 * Copyright 2018 Asylo authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "asylo/platform/posix/signal/signal_manager.h"
#include "absl/memory/memory.h"
#include "absl/strings/str_cat.h"

namespace asylo {

SignalManager *SignalManager::GetInstance() {
  static SignalManager *instance = new SignalManager();
  return instance;
}

Status SignalManager::HandleSignal(int signum, siginfo_t *info,
                                   void *ucontext) {
  const struct sigaction *act = GetSigAction(signum);
  if (!act) {
    return Status(
        error::GoogleError::INTERNAL,
        absl::StrCat("No handler has been registered for signal: ", signum));
  }
  bool is_siginfo = act->sa_flags & SA_SIGINFO;
  if (is_siginfo && act->sa_sigaction) {
    act->sa_sigaction(signum, info, ucontext);
  } else if (!is_siginfo && act->sa_handler) {
    act->sa_handler(signum);
  } else {
    return Status(
        error::GoogleError::INTERNAL,
        absl::StrCat("Handler registered for signal: ", signum, " is invalid"));
  }
  return Status::OkStatus();
}

void SignalManager::SetSigAction(int signum, const struct sigaction *act) {
  absl::MutexLock lock(&signal_to_sigaction_lock_);
  signal_to_sigaction_[signum] = absl::make_unique<struct sigaction>(*act);
}

const struct sigaction *SignalManager::GetSigAction(int signum) const {
  absl::MutexLock lock(&signal_to_sigaction_lock_);
  auto sigaction_iterator = signal_to_sigaction_.find(signum);
  if (sigaction_iterator == signal_to_sigaction_.end()) {
    return nullptr;
  }
  return sigaction_iterator->second.get();
}

}  // namespace asylo
