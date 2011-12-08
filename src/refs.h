/*
 * This file is a part of the Sharemind framework.
 * Copyright (C) Cybernetica AS
 *
 * All rights are reserved. Reproduction in whole or part is prohibited
 * without the written consent of the copyright owner. The usage of this
 * code is subject to the appropriate license agreement.
 */

#ifndef SHAREMIND_REFS_H
#define SHAREMIND_REFS_H

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>


#define SMVM_REFS_DECLARE_FIELDS size_t refs;

#define SMVM_REFS_INIT(object) \
    if (1) { \
        (object)->refs = 0u; \
    } (void) 0

#define SMVM_REFS_ASSERT_IF_REFERENCED(object) \
    if (1) { \
        assert((object)->refs <= 0u); \
    } (void) 0

#define SMVM_REFS_DECLARE_FUNCTIONS(type) \
    bool type ## _ref(type * object); \
    void type ## _unref(type * object);

#define SMVM_REFS_DEFINE_FUNCTIONS(type) \
    bool type ## _ref(type * object) { \
        if ((object)->refs >= SIZE_MAX) \
            return false; \
        (object)->refs++; \
        return true; \
    } \
    void type ## _unref(type * object) { \
        assert((object)->refs > 0u); \
        (object)->refs--; \
    }

#endif
