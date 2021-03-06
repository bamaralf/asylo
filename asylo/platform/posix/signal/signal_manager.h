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

#ifndef ASYLO_PLATFORM_POSIX_SIGNAL_SIGNAL_MANAGER_H_
#define ASYLO_PLATFORM_POSIX_SIGNAL_SIGNAL_MANAGER_H_

#include <signal.h>
#include <memory>
#include <unordered_map>

#include "absl/synchronization/mutex.h"
#include "asylo/util/status.h"

namespace asylo {

// SignalManager class is a singleton responsible for maintaining mapping
// between signum and registered signal handlers.
class SignalManager {
 public:
  static SignalManager *GetInstance();

  // Locates and calls the handler registered for |signum|.
  Status HandleSignal(int signum, siginfo_t *info, void *ucontext);

  // Sets a signal handler pointer for a specific signal |signum|.
  void SetSigAction(int signum, const struct sigaction *act)
      LOCKS_EXCLUDED(signal_to_sigaction_lock_);

  // Gets a signal handler for a specific signal |signum|.
  const struct sigaction *GetSigAction(int signum) const
      LOCKS_EXCLUDED(signal_to_sigaction_lock_);

 private:
  SignalManager() = default;  // Private to enforce singleton.
  SignalManager(SignalManager const &) = delete;
  void operator=(SignalManager const &) = delete;

  mutable absl::Mutex signal_to_sigaction_lock_;
  std::unordered_map<int, std::unique_ptr<struct sigaction>>
      signal_to_sigaction_ GUARDED_BY(signal_to_sigaction_lock_);
};

}  // namespace asylo

#endif  // ASYLO_PLATFORM_POSIX_SIGNAL_SIGNAL_MANAGER_H_
