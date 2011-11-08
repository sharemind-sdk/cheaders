/*
 * This file is a part of the Sharemind framework.
 * Copyright (C) Cybernetica AS
 *
 * All rights are reserved. Reproduction in whole or part is prohibited
 * without the written consent of the copyright owner. The usage of this
 * code is subject to the appropriate license agreement.
 */

#ifndef SHAREMIND_MODAPI_H
#define SHAREMIND_MODAPI_H

#define SHAREMIND_MOD_API_VERSIONS(v) const uint32_t SMVM_MOD_API_VERSIONS[] = { v, 0x0 }
#define SHAREMIND_MOD_NAME(n) const char * const SMVM_MOD_NAME = (n)
#define SHAREMIND_MOD_VERSION(v) const uint32_t SMVM_MOD_VERSION = (v)

#include "modapi_0x1.h"

#endif /* SHAREMIND_MODAPI_H */
