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

#include <string.h>
#include "fnv.h"


#define SM_STRINGMAP_DECLARE(name,valueType,inlinePerhaps) \
    SM_MAP_DECLARE(name,char *,const char * const,valueType,inlinePerhaps)

SM_MAP_EXTERN_C_BEGIN

inline int SMVM_StringMap_key_equals(const char * k1, const char * k2) {
    return strcmp(k1, k2) == 0;
}

inline int SMVM_StringMap_key_less_than(const char * k1, const char * k2) {
    return strcmp(k1, k2) < 0;
}

SM_MAP_EXTERN_C_END

#define SM_STRINGMAP_DEFINE(name,valueType,mymalloc,myfree,mystrdup,inlinePerhaps) \
    SM_MAP_EXTERN_C_BEGIN \
    inline int name ## _key_copy(char ** const pDest, const char * src) { \
        (*pDest) = mystrdup(src); \
        return (*pDest) != NULL; \
    } \
    SM_MAP_EXTERN_C_END \
    SM_MAP_DEFINE(name,char *,const char * const,valueType,fnv_16a_str(key),SMVM_StringMap_key_equals,SMVM_StringMap_key_less_than,name ## _key_copy,myfree,mymalloc,myfree,inlinePerhaps)

#endif /* SHAREMIND_STRINGMAP_H */
