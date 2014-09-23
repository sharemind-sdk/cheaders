/*
 * This file is a part of the Sharemind framework.
 * Copyright (C) Cybernetica AS
 *
 * All rights are reserved. Reproduction in whole or part is prohibited
 * without the written consent of the copyright owner. The usage of this
 * code is subject to the appropriate license agreement.
 */

#ifndef SHAREMIND_LOCKS_H
#define SHAREMIND_LOCKS_H

#include "abort.h"
#include "likely.h"
#include "mutex.h"


#define SHAREMIND_NAMED_LOCK_DEFINE(mutexName) SharemindMutex mutexName
#define SHAREMIND_LOCK_DECLARE_FIELDS SHAREMIND_NAMED_LOCK_DEFINE(mutex)

#define SHAREMIND_NAMED_LOCK_INIT(className,mutexName) \
    (SharemindMutex_init(&className->mutexName) == SHAREMIND_MUTEX_OK)
#define SHAREMIND_LOCK_INIT(className) \
    SHAREMIND_NAMED_LOCK_INIT(className, mutex)

#define SHAREMIND_NAMED_LOCK_DEINIT(className,mutexName) \
    if (unlikely(SharemindMutex_destroy(&className->mutexName) \
                 != SHAREMIND_MUTEX_OK)) \
    { \
        SHAREMIND_ABORT("SNLD"); \
    } else (void) 0
#define SHAREMIND_LOCK_DEINIT(className) \
    SHAREMIND_NAMED_LOCK_DEINIT(className, mutex)

#define SHAREMIND_NAMED_LOCK_FUNCTIONS_DECLARE__(CN,f,FunName) \
    void CN ## _ ## f ## FunName(CN * c) \
            __attribute__ ((nonnull(1))); \
    void CN ## _ ## f ## Const ## FunName(CN const * c) \
            __attribute__ ((nonnull(1)))
#define SHAREMIND_NAMED_LOCK_FUNCTIONS_DECLARE(CN,FunName) \
    SHAREMIND_NAMED_LOCK_FUNCTIONS_DECLARE__(CN,lock,FunName); \
    SHAREMIND_NAMED_LOCK_FUNCTIONS_DECLARE__(CN,unlock,FunName)
#define SHAREMIND_LOCK_FUNCTIONS_DECLARE(CN) \
    SHAREMIND_NAMED_LOCK_FUNCTIONS_DECLARE(CN,)

#define SHAREMIND_NAMED_LOCK_FUNCTIONS_DEFINE__(CN,f,FunName,mutexName) \
    void CN ## _ ## f ## FunName(CN * c) { \
        assert(c); \
        if (unlikely(SharemindMutex_ ## f(&c->mutexName) \
            != SHAREMIND_MUTEX_OK)) \
            SHAREMIND_ABORT("SNLFD1"); \
    } \
    void CN ## _ ## f ## Const ## FunName(CN const * c) { \
        assert(c); \
        if (unlikely(SharemindMutex_ ## f ## _const(&c->mutexName) \
            != SHAREMIND_MUTEX_OK)) \
            SHAREMIND_ABORT("SNLFD2"); \
    }
#define SHAREMIND_NAMED_LOCK_FUNCTIONS_DEFINE(CN,FunName,mutexName) \
    SHAREMIND_NAMED_LOCK_FUNCTIONS_DEFINE__(CN,lock,FunName,mutexName) \
    SHAREMIND_NAMED_LOCK_FUNCTIONS_DEFINE__(CN,unlock,FunName,mutexName)
#define SHAREMIND_LOCK_FUNCTIONS_DEFINE(CN) \
    SHAREMIND_NAMED_LOCK_FUNCTIONS_DEFINE(CN,,mutex)

#endif /* SHAREMIND_LOCKS_H */

