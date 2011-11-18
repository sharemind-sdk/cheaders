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
#ifdef SMVM_SOFT_FLOAT
#include "3rdparty/softfloat/softfloat.h"
#endif


#ifdef __cplusplus
extern "C" {
#endif


#ifdef SMVM_SOFT_FLOAT
typedef sf_float32 smvm_float32;
#else
typedef float smvm_float32;
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
    smvm_float32 float32[2];
    size_t sizet[1];
    void * p[1];
} SMVM_CodeBlock;


#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* SHAREMIND_CODEBLOCK_H */
