/*
 * This file is a part of the Sharemind framework.
 * Copyright (C) Cybernetica AS
 *
 * All rights are reserved. Reproduction in whole or part is prohibited
 * without the written consent of the copyright owner. The usage of this
 * code is subject to the appropriate license agreement.
 */

#ifndef SHAREMIND_CODEBLOCK_H
#define SHAREMIND_CODEBLOCK_H

#include <stddef.h>
#include <stdint.h>
#include "static_assert.h"


#ifdef __cplusplus
extern "C" {
#endif


typedef union {
    uint64_t uint64[1];
    uint32_t uint32[2];
    uint16_t uint16[4];
    uint8_t  uint8[8];
    int64_t int64[1];
    int32_t int32[2];
    int16_t int16[4];
    int8_t  int8[8];
    char chr[8];
    uint32_t float32[2];
    uint64_t float64[1];
    size_t sizet[1];
    ptrdiff_t ptrdiff[1];
    void * p[1];
    const void * cp[1];
    void (* fp[1])(void);
} SharemindCodeBlock;

SHAREMIND_STATIC_ASSERT(sizeof(char) == sizeof(uint8_t));
SHAREMIND_STATIC_ASSERT(sizeof(size_t) <= sizeof(uint64_t));
SHAREMIND_STATIC_ASSERT(sizeof(ptrdiff_t) <= sizeof(uint64_t));
SHAREMIND_STATIC_ASSERT(sizeof(void *) <= sizeof(uint64_t));
SHAREMIND_STATIC_ASSERT(sizeof(SharemindCodeBlock) == sizeof(uint64_t));

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* SHAREMIND_CODEBLOCK_H */
