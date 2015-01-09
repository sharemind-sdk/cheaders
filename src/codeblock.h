/*
 * Copyright (C) 2015 Cybernetica
 *
 * Research/Commercial License Usage
 * Licensees holding a valid Research License or Commercial License
 * for the Software may use this file according to the written
 * agreement between you and Cybernetica.
 *
 * GNU General Public License Usage
 * Alternatively, this file may be used under the terms of the GNU
 * General Public License version 3.0 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.  Please review the following information to
 * ensure the GNU General Public License version 3.0 requirements will be
 * met: http://www.gnu.org/copyleft/gpl-3.0.html.
 *
 * For further information, please contact us at sharemind@cyber.ee.
 */

#ifndef SHAREMIND_CODEBLOCK_H
#define SHAREMIND_CODEBLOCK_H

#include <stddef.h>
#include <stdint.h>
#include "extern_c.h"
#include "static_assert.h"


SHAREMIND_EXTERN_C_BEGIN

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
SHAREMIND_STATIC_ASSERT(sizeof(void (*)(void)) <= sizeof(uint64_t));
SHAREMIND_STATIC_ASSERT(sizeof(SharemindCodeBlock) == sizeof(uint64_t));

SHAREMIND_EXTERN_C_END

#endif /* SHAREMIND_CODEBLOCK_H */
