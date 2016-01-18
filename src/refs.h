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

#ifndef SHAREMIND_REFS_H
#define SHAREMIND_REFS_H

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include "mutex.h"


#define SHAREMIND_NAMED_REFS_DECLARE_FIELDS(name) size_t name;
#define SHAREMIND_REFS_DECLARE_FIELDS SHAREMIND_NAMED_REFS_DECLARE_FIELDS(refs)

#define SHAREMIND_NAMED_REFS_INIT(object,name) \
    do { \
        ((object)->name) = 0u; \
    } while ((0))
#define SHAREMIND_REFS_INIT(object) SHAREMIND_NAMED_REFS_INIT(object,refs)

#define SHAREMIND_NAMED_REFS_ASSERT_IF_REFERENCED(object,name) \
    do { \
        assert(((object)->name) <= 0u); \
    } while ((0))
#define SHAREMIND_REFS_ASSERT_IF_REFERENCED(object) SHAREMIND_NAMED_REFS_ASSERT_IF_REFERENCED(object,refs)

#define SHAREMIND_NAMED_REFS_DECLARE_FUNCTIONS(type,name) \
    bool type ## _ ## name ## _ref(type * object); \
    void type ## _ ## name ## _unref(type * object);
#define SHAREMIND_REFS_DECLARE_FUNCTIONS(type) SHAREMIND_NAMED_REFS_DECLARE_FUNCTIONS(type,refs)

#define SHAREMIND_NAMED_REFS_DEFINE_FUNCTIONS(type,name) \
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
#define SHAREMIND_NAMED_REFS_DEFINE_FUNCTIONS_WITH_NAMED_MUTEX_(type,name,mutex,mutexType) \
    bool type ## _ ## name ## _ref(type * object) { \
        mutexType ## _lock(&(object)->mutex); \
        if (((object)->name) >= SIZE_MAX) { \
            mutexType ## _unlock(&(object)->mutex); \
            return false; \
        } \
        ((object)->name)++; \
        mutexType ## _unlock(&(object)->mutex); \
        return true; \
    } \
    void type ## _ ## name ## _unref(type * object) { \
        mutexType ## _lock(&(object)->mutex); \
        assert(((object)->name) > 0u); \
        ((object)->name)--; \
        mutexType ## _unlock(&(object)->mutex); \
    }

#define SHAREMIND_NAMED_REFS_DEFINE_FUNCTIONS_WITH_MUTEX(type,name) \
    SHAREMIND_NAMED_REFS_DEFINE_FUNCTIONS_WITH_NAMED_MUTEX_(type,name,mutex,SharemindMutex)

#define SHAREMIND_NAMED_REFS_DEFINE_FUNCTIONS_WITH_RECURSIVE_MUTEX(type,name) \
    SHAREMIND_NAMED_REFS_DEFINE_FUNCTIONS_WITH_NAMED_MUTEX_(type,name,mutex,SharemindRecursiveMutex)

#define SHAREMIND_REFS_DEFINE_FUNCTIONS(type) \
    SHAREMIND_NAMED_REFS_DEFINE_FUNCTIONS(type,refs)

#define SHAREMIND_REFS_DEFINE_FUNCTIONS_WITH_MUTEX(type) \
    SHAREMIND_NAMED_REFS_DEFINE_FUNCTIONS_WITH_NAMED_MUTEX_(type,refs,mutex,SharemindMutex)

#define SHAREMIND_REFS_DEFINE_FUNCTIONS_WITH_NAMED_MUTEX(type,mutex) \
    SHAREMIND_NAMED_REFS_DEFINE_FUNCTIONS_WITH_NAMED_MUTEX_(type,refs,mutex,SharemindMutex)

#define SHAREMIND_REFS_DEFINE_FUNCTIONS_WITH_RECURSIVE_MUTEX(type) \
    SHAREMIND_NAMED_REFS_DEFINE_FUNCTIONS_WITH_NAMED_MUTEX_(type,refs,mutex,SharemindRecursiveMutex)

#define SHAREMIND_REFS_DEFINE_FUNCTIONS_WITH_NAMED_RECURSIVE_MUTEX(type,mutex) \
    SHAREMIND_NAMED_REFS_DEFINE_FUNCTIONS_WITH_NAMED_MUTEX_(type,refs,mutex,SharemindRecursiveMutex)

#endif
