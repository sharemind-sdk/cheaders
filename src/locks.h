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

#ifndef SHAREMIND_LOCKS_H
#define SHAREMIND_LOCKS_H

#include <assert.h>
#include "abort.h"
#include "extern_c.h"
#include "likely.h"
#include "mutex.h"
#include "wrap.h"


#define SHAREMIND_NAMED_LOCK_DEFINE(mutexName) SharemindMutex mutexName
#define SHAREMIND_LOCK_DECLARE_FIELDS SHAREMIND_NAMED_LOCK_DEFINE(mutex)

#define SHAREMIND_NAMED_LOCK_INIT(className,mutexName) \
    (SharemindMutex_init(&className->mutexName) == 0)
#define SHAREMIND_LOCK_INIT(className) \
    SHAREMIND_NAMED_LOCK_INIT(className, mutex)

#define SHAREMIND_NAMED_LOCK_DEINIT(className,mutexName) \
    if (unlikely(SharemindMutex_destroy(&className->mutexName))) { \
        SHAREMIND_ABORT("SNLD"); \
    } else (void) 0
#define SHAREMIND_LOCK_DEINIT(className) \
    SHAREMIND_NAMED_LOCK_DEINIT(className, mutex)

#define SHAREMIND_NAMED_LOCK_FUNCTIONS_DECLARE__(CN,inlinePerhaps,f,FunName,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps void CN ## _ ## f ## FunName(CN * c) \
            __attribute__ ((nonnull(1) __VA_ARGS__)); \
    inlinePerhaps void CN ## _ ## f ## Const ## FunName(CN const * c) \
            __attribute__ ((nonnull(1) __VA_ARGS__)); \
    SHAREMIND_EXTERN_C_END
#define SHAREMIND_NAMED_LOCK_FUNCTIONS_DECLARE(CN,inlinePerhaps,FunName,...) \
    SHAREMIND_NAMED_LOCK_FUNCTIONS_DECLARE__(CN,inlinePerhaps,lock,FunName,SHAREMIND_WRAP(__VA_ARGS__)) \
    SHAREMIND_NAMED_LOCK_FUNCTIONS_DECLARE__(CN,inlinePerhaps,unlock,FunName,SHAREMIND_WRAP(__VA_ARGS__))
#define SHAREMIND_LOCK_FUNCTIONS_DECLARE(CN,inlinePerhaps,...) \
    SHAREMIND_NAMED_LOCK_FUNCTIONS_DECLARE(CN,,inlinePerhaps,,SHAREMIND_WRAP(__VA_ARGS__))

#define SHAREMIND_NAMED_LOCK_FUNCTIONS_DEFINE__(CN,inlinePerhaps,f,FunName,mutexName) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps void CN ## _ ## f ## FunName(CN * c) { \
        assert(c); \
        if (unlikely(SharemindMutex_ ## f(&c->mutexName))) \
            SHAREMIND_ABORT("SNLFD1"); \
    } \
    inlinePerhaps void CN ## _ ## f ## Const ## FunName(CN const * c) { \
        assert(c); \
        if (unlikely(SharemindMutex_ ## f ## _const(&c->mutexName))) \
            SHAREMIND_ABORT("SNLFD2"); \
    } \
    SHAREMIND_EXTERN_C_END
#define SHAREMIND_NAMED_LOCK_FUNCTIONS_DEFINE(CN,inlinePerhaps,FunName,mutexName) \
    SHAREMIND_NAMED_LOCK_FUNCTIONS_DEFINE__(CN,inlinePerhaps,lock,FunName,mutexName) \
    SHAREMIND_NAMED_LOCK_FUNCTIONS_DEFINE__(CN,inlinePerhaps,unlock,FunName,mutexName)
#define SHAREMIND_LOCK_FUNCTIONS_DEFINE(CN,inlinePerhaps) \
    SHAREMIND_NAMED_LOCK_FUNCTIONS_DEFINE(CN,inlinePerhaps,,mutex)

#define SHAREMIND_NAMED_LOCK_FUNCTIONS_DECLARE_DEFINE(CN,inlinePerhaps,FunName,mutexName,...) \
    SHAREMIND_NAMED_LOCK_FUNCTIONS_DECLARE(CN,inlinePerhaps,FunName,SHAREMIND_WRAP(__VA_ARGS__)) \
    SHAREMIND_NAMED_LOCK_FUNCTIONS_DEFINE(CN,inlinePerhaps,FunName,mutexName)
#define SHAREMIND_LOCK_FUNCTIONS_DECLARE_DEFINE(CN,inlinePerhaps,...) \
    SHAREMIND_LOCK_FUNCTIONS_DECLARE(CN,inlinePerhaps,SHAREMIND_WRAP(__VA_ARGS__)) \
    SHAREMIND_LOCK_FUNCTIONS_DEFINE(CN,inlinePerhaps)

#endif /* SHAREMIND_LOCKS_H */

