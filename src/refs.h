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


#define SMVM_NAMED_REFS_DECLARE_FIELDS(name) size_t name;
#define SMVM_REFS_DECLARE_FIELDS SMVM_NAMED_REFS_DECLARE_FIELDS(refs)

#define SMVM_NAMED_REFS_INIT(object,name) \
    if (1) { \
        ((object)->name) = 0u; \
    } (void) 0
#define SMVM_REFS_INIT(object) SMVM_NAMED_REFS_INIT(object,refs)

#define SMVM_NAMED_REFS_ASSERT_IF_REFERENCED(object,name) \
    if (1) { \
        assert(((object)->name) <= 0u); \
    } (void) 0
#define SMVM_REFS_ASSERT_IF_REFERENCED(object) SMVM_NAMED_REFS_ASSERT_IF_REFERENCED(object,refs)

#define SMVM_NAMED_REFS_DECLARE_FUNCTIONS(type,name) \
    bool type ## _ ## name ## _ref(type * object); \
    void type ## _ ## name ## _unref(type * object);
#define SMVM_REFS_DECLARE_FUNCTIONS(type) SMVM_NAMED_REFS_DECLARE_FUNCTIONS(type,refs)

#define SMVM_NAMED_REFS_DEFINE_FUNCTIONS(type,name) \
    bool type ## _ ## name ## _ref(type * object) { \
        if (((object)->name) >= SIZE_MAX) \
            return false; \
        ((object)->name)++; \
        return true; \
    } \
    void type ## _ ## name ## _unref(type * object) { \
        assert(((object)->name) > 0u); \
        ((object)->name)--; \
    }
#define SMVM_REFS_DEFINE_FUNCTIONS(type) SMVM_NAMED_REFS_DEFINE_FUNCTIONS(type,refs)

#endif
