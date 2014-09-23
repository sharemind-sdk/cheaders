/*
 * This file is a part of the Sharemind framework.
 * Copyright (C) Cybernetica AS
 *
 * All rights are reserved. Reproduction in whole or part is prohibited
 * without the written consent of the copyright owner. The usage of this
 * code is subject to the appropriate license agreement.
 */

#ifndef SHAREMIND_STRINGMAP_H
#define SHAREMIND_STRINGMAP_H

#include "map.h"

#include <stdbool.h>
#include <string.h>
#include "fnv.h"


#define SHAREMIND_STRINGMAP_DECLARE(name,valueType,inlinePerhaps) \
    SHAREMIND_MAP_DECLARE(name,char *,const char * const,valueType,inlinePerhaps)

SHAREMIND_MAP_EXTERN_C_BEGIN

inline bool SMVM_StringMap_key_equals(const char * k1, const char * k2) {
    return strcmp(k1, k2) == 0;
}

inline bool SMVM_StringMap_key_less_than(const char * k1, const char * k2) {
    return strcmp(k1, k2) < 0;
}

SHAREMIND_MAP_EXTERN_C_END

#define SHAREMIND_STRINGMAP_DEFINE(name,valueType,mymalloc,myfree,mystrdup,inlinePerhaps) \
    SHAREMIND_MAP_EXTERN_C_BEGIN \
    inline bool name ## _key_init(char ** const pDest) { \
        (*pDest) = NULL; \
        return true; \
    } \
    inline bool name ## _key_copy(char ** const pDest, const char * src) { \
        return ((*pDest) = mystrdup(src)); \
    } \
    SHAREMIND_MAP_EXTERN_C_END \
    SHAREMIND_MAP_DEFINE(name,char *,const char * const,valueType,fnv_16a_str(key),SMVM_StringMap_key_equals,SMVM_StringMap_key_less_than,name ## _key_init,name ## _key_copy,myfree,mymalloc,myfree,inlinePerhaps)

#endif /* SHAREMIND_STRINGMAP_H */
