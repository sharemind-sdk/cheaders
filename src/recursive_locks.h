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

#ifndef SHAREMIND_RECURSIVE_LOCKS_H
#define SHAREMIND_RECURSIVE_LOCKS_H

#include <assert.h>
#include "abort.h"
#include "extern_c.h"
#include "likely.h"
#include "recursive_mutex.h"
#include "wrap.h"


#define SHAREMIND_NAMED_RECURSIVE_LOCK_DEFINE(mutexName) \
    SharemindRecursiveMutex mutexName
#define SHAREMIND_RECURSIVE_LOCK_DECLARE_FIELDS \
    SHAREMIND_NAMED_RECURSIVE_LOCK_DEFINE(mutex)

#define SHAREMIND_NAMED_RECURSIVE_LOCK_INIT(className,mutexName) \
    (likely(SharemindRecursiveMutex_init(&className->mutexName) == 0))
#define SHAREMIND_RECURSIVE_LOCK_INIT(className) \
    SHAREMIND_NAMED_RECURSIVE_LOCK_INIT(className, mutex)

#define SHAREMIND_NAMED_RECURSIVE_LOCK_DEINIT(className,mutexName) \
    do { \
        int const r = SharemindRecursiveMutex_destroy(&className->mutexName); \
        if (unlikely(r)) \
            SHAREMIND_ABORT("SNRLD %d", r); \
    } while(0)
#define SHAREMIND_RECURSIVE_LOCK_DEINIT(className) \
    SHAREMIND_NAMED_RECURSIVE_LOCK_DEINIT(className, mutex)

#define SHAREMIND_NAMED_RECURSIVE_LOCK_FUNCTIONS_DECLARE_(CN,inlinePerhaps,f,FunName,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps void CN ## _ ## f ## FunName(CN * c) \
            __attribute__ ((nonnull(1), __VA_ARGS__)); \
    inlinePerhaps void CN ## _ ## f ## Const ## FunName(CN const * c) \
            __attribute__ ((nonnull(1), __VA_ARGS__)); \
    SHAREMIND_EXTERN_C_END
#define SHAREMIND_NAMED_RECURSIVE_LOCK_FUNCTIONS_DECLARE(CN,inlinePerhaps,FunName,...) \
    SHAREMIND_NAMED_RECURSIVE_LOCK_FUNCTIONS_DECLARE_(CN,inlinePerhaps,lock,FunName,SHAREMIND_WRAP(__VA_ARGS__)) \
    SHAREMIND_NAMED_RECURSIVE_LOCK_FUNCTIONS_DECLARE_(CN,inlinePerhaps,unlock,FunName,SHAREMIND_WRAP(__VA_ARGS__))
#define SHAREMIND_RECURSIVE_LOCK_FUNCTIONS_DECLARE(CN,inlinePerhaps,...) \
    SHAREMIND_NAMED_RECURSIVE_LOCK_FUNCTIONS_DECLARE(CN,inlinePerhaps,,SHAREMIND_WRAP(__VA_ARGS__))

#define SHAREMIND_NAMED_RECURSIVE_LOCK_FUNCTIONS_DEFINE_(CN,inlinePerhaps,f,FunName,mutexName) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps void CN ## _ ## f ## FunName(CN * c) { \
        assert(c); \
        int const r = SharemindRecursiveMutex_ ## f(&c->mutexName); \
        if (unlikely(r)) \
            SHAREMIND_ABORT("SNRLFD1 %d", r); \
    } \
    inlinePerhaps void CN ## _ ## f ## Const ## FunName(CN const * c) { \
        assert(c); \
        int const r = SharemindRecursiveMutex_ ## f ## _const(&c->mutexName); \
        if (unlikely(r)) \
            SHAREMIND_ABORT("SNRLFD2 %d", r); \
    } \
    SHAREMIND_EXTERN_C_END
#define SHAREMIND_NAMED_RECURSIVE_LOCK_FUNCTIONS_DEFINE(CN,inlinePerhaps,FunName,mutexName) \
    SHAREMIND_NAMED_RECURSIVE_LOCK_FUNCTIONS_DEFINE_(CN,inlinePerhaps,lock,FunName,mutexName) \
    SHAREMIND_NAMED_RECURSIVE_LOCK_FUNCTIONS_DEFINE_(CN,inlinePerhaps,unlock,FunName,mutexName)
#define SHAREMIND_RECURSIVE_LOCK_FUNCTIONS_DEFINE(CN,inlinePerhaps) \
    SHAREMIND_NAMED_RECURSIVE_LOCK_FUNCTIONS_DEFINE(CN,inlinePerhaps,,mutex)

#define SHAREMIND_NAMED_RECURSIVE_LOCK_FUNCTIONS_DECLARE_DEFINE(CN,inlinePerhaps,FunName,mutexName,...) \
    SHAREMIND_NAMED_RECURSIVE_LOCK_FUNCTIONS_DECLARE(CN,inlinePerhaps,FunName,SHAREMIND_WRAP(__VA_ARGS__)) \
    SHAREMIND_NAMED_RECURSIVE_LOCK_FUNCTIONS_DEFINE(CN,inlinePerhaps,FunName,mutexName)
#define SHAREMIND_RECURSIVE_LOCK_FUNCTIONS_DECLARE_DEFINE(CN,inlinePerhaps,...) \
    SHAREMIND_RECURSIVE_LOCK_FUNCTIONS_DECLARE(CN,inlinePerhaps,SHAREMIND_WRAP(__VA_ARGS__)) \
    SHAREMIND_RECURSIVE_LOCK_FUNCTIONS_DEFINE(CN,inlinePerhaps)

#endif /* SHAREMIND_RECURSIVE_LOCKS_H */

