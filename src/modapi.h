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

#ifdef __cplusplus
extern "C" {
#endif


#define SHAREMIND_MOD_API_VERSIONS(v) const uint32_t SMVM_MOD_api_versions[] = { v, 0x0 }
#define SHAREMIND_MOD_NAME(n) const char * const SMVM_MOD_name = (n)
#define SHAREMIND_MOD_VERSION(v) const uint32_t SMVM_MOD_version = (v)


#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* SHAREMIND_MODAPI_H */