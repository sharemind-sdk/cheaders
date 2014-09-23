/*
 * This file is a part of the Sharemind framework.
 * Copyright (C) Cybernetica AS
 *
 * All rights are reserved. Reproduction in whole or part is prohibited
 * without the written consent of the copyright owner. The usage of this
 * code is subject to the appropriate license agreement.
 */

#ifndef SHAREMIND_MUTEX_H
#define SHAREMIND_MUTEX_H

#include <assert.h>
#include <pthread.h>
#include <stddef.h>
#include "extern_c.h"
#include "likely.h"


SHAREMIND_EXTERN_C_BEGIN

typedef pthread_mutex_t SharemindMutex;

enum SharemindMutexError_ {
    SHAREMIND_MUTEX_OK = 0,
    SHAREMIND_MUTEX_ERROR
};
typedef enum SharemindMutexError_ SharemindMutexError;

inline SharemindMutexError SharemindMutex_init(SharemindMutex * mutex) {
    return likely(pthread_mutex_init(mutex, NULL) == 0)
            ? SHAREMIND_MUTEX_OK
            : SHAREMIND_MUTEX_ERROR;
}

inline SharemindMutexError SharemindMutex_destroy(SharemindMutex * mutex) {
    return likely(pthread_mutex_destroy(mutex) == 0)
            ? SHAREMIND_MUTEX_OK
            : SHAREMIND_MUTEX_ERROR;
}

inline SharemindMutexError SharemindMutex_lock(SharemindMutex * mutex) {
    return likely(pthread_mutex_lock(mutex) == 0)
            ? SHAREMIND_MUTEX_OK
            : SHAREMIND_MUTEX_ERROR;
}

inline SharemindMutexError SharemindMutex_unlock(SharemindMutex * mutex) {
    return likely(pthread_mutex_unlock(mutex) == 0)
            ? SHAREMIND_MUTEX_OK
            : SHAREMIND_MUTEX_ERROR;
}

inline SharemindMutexError SharemindMutex_trylock(SharemindMutex * mutex) {
    return likely(pthread_mutex_trylock(mutex) == 0)
            ? SHAREMIND_MUTEX_OK
            : SHAREMIND_MUTEX_ERROR;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
inline SharemindMutexError SharemindMutex_lock_const(
        const SharemindMutex * mutex)
{ return SharemindMutex_lock((SharemindMutex *) mutex); }

inline SharemindMutexError SharemindMutex_unlock_const(
        const SharemindMutex * mutex)
{ return SharemindMutex_unlock((SharemindMutex *) mutex); }

inline SharemindMutexError SharemindMutex_trylock_const(
        const SharemindMutex * mutex)
{ return SharemindMutex_trylock((SharemindMutex *) mutex); }
#pragma GCC diagnostic pop

SHAREMIND_EXTERN_C_END

#endif /* SHAREMIND_VECTOR_H */
