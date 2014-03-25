/*
 * This file is a part of the Sharemind framework.
 * Copyright (C) Cybernetica AS
 *
 * All rights are reserved. Reproduction in whole or part is prohibited
 * without the written consent of the copyright owner. The usage of this
 * code is subject to the appropriate license agreement.
 */

#ifndef SHAREMIND_RECURSIVEMUTEX_H
#define SHAREMIND_RECURSIVEMUTEX_H

#include "mutex.h"


#ifdef __cplusplus
extern "C" {
#endif

struct SharemindRecursiveMutex_ {
    SharemindMutex inner;
};
typedef struct SharemindRecursiveMutex_ SharemindRecursiveMutex;

typedef SharemindMutexError SharemindRecursiveMutexError;

inline SharemindRecursiveMutexError SharemindRecursiveMutex_init(
        SharemindRecursiveMutex * mutex)
{
    pthread_mutexattr_t attr;
    if (pthread_mutexattr_init(&attr) != 0)
        return SHAREMIND_MUTEX_ERROR;

    SharemindRecursiveMutexError r;
    /* If you get undeclared errors on this, define _XOPEN_SOURCE >= 600: */
    if (pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE) != 0) {
        r = SHAREMIND_MUTEX_ERROR;
        goto SharemindRecursiveMutex_init_recursive_end;
    }

    r = likely(pthread_mutex_init(&mutex->inner, &attr) == 0)
        ? SHAREMIND_MUTEX_OK
        : SHAREMIND_MUTEX_ERROR;

SharemindRecursiveMutex_init_recursive_end:

    pthread_mutexattr_destroy(&attr);
    return r;
}

inline SharemindRecursiveMutexError SharemindRecursiveMutex_destroy(
        SharemindRecursiveMutex * mutex)
{
    return (SharemindRecursiveMutexError) SharemindMutex_destroy(&mutex->inner);
}

inline SharemindRecursiveMutexError SharemindRecursiveMutex_lock(
        SharemindRecursiveMutex * mutex)
{
    return (SharemindRecursiveMutexError) SharemindMutex_lock(&mutex->inner);
}

inline SharemindRecursiveMutexError SharemindRecursiveMutex_unlock(
        SharemindRecursiveMutex * mutex)
{
    return (SharemindRecursiveMutexError) SharemindMutex_unlock(&mutex->inner);
}

inline SharemindRecursiveMutexError SharemindRecursiveMutex_trylock(
        SharemindRecursiveMutex * mutex)
{
    return (SharemindRecursiveMutexError) SharemindMutex_trylock(&mutex->inner);
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
inline SharemindRecursiveMutexError SharemindRecursiveMutex_lock_const(
        const SharemindRecursiveMutex * mutex)
{
    return SharemindRecursiveMutex_lock((SharemindRecursiveMutex *) mutex);
}

inline SharemindRecursiveMutexError SharemindRecursiveMutex_unlock_const(
        const SharemindRecursiveMutex * mutex)
{
    return SharemindRecursiveMutex_unlock((SharemindRecursiveMutex *) mutex);
}

inline SharemindRecursiveMutexError SharemindRecursiveMutex_trylock_const(
        const SharemindRecursiveMutex * mutex)
{
    return SharemindRecursiveMutex_trylock((SharemindRecursiveMutex *) mutex);
}
#pragma GCC diagnostic pop

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* SHAREMIND_RECURSIVEMUTEX_H */
