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

#ifndef ASYLO_IDENTITY_NULL_IDENTITY_NULL_IDENTITY_UTIL_H_
#define ASYLO_IDENTITY_NULL_IDENTITY_NULL_IDENTITY_UTIL_H_

#include "asylo/identity/identity.pb.h"

#include "asylo/identity/null_identity/null_identity_constants.h"

namespace asylo {

// Sets |assertion_description| to describe a null assertion.
inline void SetNullAssertionDescription(
    AssertionDescription *assertion_description) {
  assertion_description->set_identity_type(EnclaveIdentityType::NULL_IDENTITY);
  assertion_description->set_authority_type(kNullAssertionAuthority);
}

// Sets |identity_description| to describe a null identity.
inline void SetNullIdentityDescription(
    EnclaveIdentityDescription *identity_description) {
  identity_description->set_identity_type(EnclaveIdentityType::NULL_IDENTITY);
  identity_description->set_authority_type(kNullAuthorizationAuthority);
}

}  // namespace asylo

#endif  // ASYLO_IDENTITY_NULL_IDENTITY_NULL_IDENTITY_UTIL_H_
