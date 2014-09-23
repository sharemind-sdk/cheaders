/*
 * This file is a part of the Sharemind framework.
 * Copyright (C) Cybernetica AS
 *
 * All rights are reserved. Reproduction in whole or part is prohibited
 * without the written consent of the copyright owner. The usage of this
 * code is subject to the appropriate license agreement.
 */

#ifndef SHAREMIND_RECURSIVE_LOCKS_H
#define SHAREMIND_RECURSIVE_LOCKS_H

#include "abort.h"
#include "likely.h"
#include "recursive_mutex.h"


#define SHAREMIND_NAMED_RECURSIVE_LOCK_DEFINE(mutexName) \
    SharemindRecursiveMutex mutexName
#define SHAREMIND_RECURSIVE_LOCK_DECLARE_FIELDS \
    SHAREMIND_NAMED_RECURSIVE_LOCK_DEFINE(mutex)

#define SHAREMIND_NAMED_RECURSIVE_LOCK_INIT(className,mutexName) \
    (likely(SharemindRecursiveMutex_init(&className->mutexName) \
            == SHAREMIND_RECURSIVE_MUTEX_OK))
#define SHAREMIND_RECURSIVE_LOCK_INIT(className) \
    SHAREMIND_NAMED_RECURSIVE_LOCK_INIT(className, mutex)

#define SHAREMIND_NAMED_RECURSIVE_LOCK_DEINIT(className,mutexName) \
    if (unlikely(SharemindRecursiveMutex_destroy(&className->mutexName) \
                 != SHAREMIND_RECURSIVE_MUTEX_OK)) \
    { \
        SHAREMIND_ABORT("SNRLD"); \
    } else (void) 0
#define SHAREMIND_RECURSIVE_LOCK_DEINIT(className) \
    SHAREMIND_NAMED_RECURSIVE_LOCK_DEINIT(className, mutex)

#define SHAREMIND_NAMED_RECURSIVE_LOCK_FUNCTIONS_DECLARE__(CN,f,FunName) \
    void CN ## _ ## f ## FunName(CN * c) \
            __attribute__ ((nonnull(1))); \
    void CN ## _ ## f ## Const ## FunName(CN const * c) \
            __attribute__ ((nonnull(1)))
#define SHAREMIND_NAMED_RECURSIVE_LOCK_FUNCTIONS_DECLARE(CN,FunName) \
    SHAREMIND_NAMED_RECURSIVE_LOCK_FUNCTIONS_DECLARE__(CN,lock,FunName); \
    SHAREMIND_NAMED_RECURSIVE_LOCK_FUNCTIONS_DECLARE__(CN,unlock,FunName)
#define SHAREMIND_RECURSIVE_LOCK_FUNCTIONS_DECLARE(CN) \
    SHAREMIND_NAMED_RECURSIVE_LOCK_FUNCTIONS_DECLARE(CN,)

#define SHAREMIND_NAMED_RECURSIVE_LOCK_FUNCTIONS_DEFINE__(CN,f,FunName,mutexName) \
    void CN ## _ ## f ## FunName(CN * c) { \
        assert(c); \
        if (unlikely(SharemindRecursiveMutex_ ## f(&c->mutexName) \
            != SHAREMIND_RECURSIVE_MUTEX_OK)) \
            SHAREMIND_ABORT("SNRLFD1"); \
    } \
    void CN ## _ ## f ## Const ## FunName(CN const * c) { \
        assert(c); \
        if (unlikely(SharemindRecursiveMutex_ ## f ## _const(&c->mutexName) \
            != SHAREMIND_RECURSIVE_MUTEX_OK)) \
            SHAREMIND_ABORT("SNRLFD2"); \
    }
#define SHAREMIND_NAMED_RECURSIVE_LOCK_FUNCTIONS_DEFINE(CN,FunName,mutexName) \
    SHAREMIND_NAMED_RECURSIVE_LOCK_FUNCTIONS_DEFINE__(CN,lock,FunName,mutexName) \
    SHAREMIND_NAMED_RECURSIVE_LOCK_FUNCTIONS_DEFINE__(CN,unlock,FunName,mutexName)
#define SHAREMIND_RECURSIVE_LOCK_FUNCTIONS_DEFINE(CN) \
    SHAREMIND_NAMED_RECURSIVE_LOCK_FUNCTIONS_DEFINE(CN,,mutex)

#endif /* SHAREMIND_RECURSIVE_LOCKS_H */

