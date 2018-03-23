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

#ifndef SHAREMIND_RECURSIVE_MUTEX_H
#define SHAREMIND_RECURSIVE_MUTEX_H

#include <pthread.h>
#include "casts.h"
#include "extern_c.h"
#include "likely.h"


SHAREMIND_EXTERN_C_BEGIN

typedef struct SharemindRecursiveMutex_ {
    pthread_mutex_t inner;
} SharemindRecursiveMutex;

inline int SharemindRecursiveMutex_init(
        SharemindRecursiveMutex * mutex)
{
    pthread_mutexattr_t attr;
    int r;
    if ((r = pthread_mutexattr_init(&attr)))
        return r;
    if (!(r = pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE)))
        r = pthread_mutex_init(&mutex->inner, &attr);
    pthread_mutexattr_destroy(&attr);
    return r;
}

inline int SharemindRecursiveMutex_destroy(SharemindRecursiveMutex * mutex)
{ return pthread_mutex_destroy(&mutex->inner); }

inline int SharemindRecursiveMutex_lock(SharemindRecursiveMutex * mutex)
{ return pthread_mutex_lock(&mutex->inner); }

inline int SharemindRecursiveMutex_unlock(SharemindRecursiveMutex * mutex)
{ return pthread_mutex_unlock(&mutex->inner); }

inline int SharemindRecursiveMutex_trylock(SharemindRecursiveMutex * mutex)
{ return pthread_mutex_trylock(&mutex->inner); }

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
inline int SharemindRecursiveMutex_lock_const(
        SharemindRecursiveMutex const * mutex)
{
    return SharemindRecursiveMutex_lock(
                SHAREMIND_CONST_CAST(SharemindRecursiveMutex *)(mutex));
}

inline int SharemindRecursiveMutex_unlock_const(
        SharemindRecursiveMutex const * mutex)
{
    return SharemindRecursiveMutex_unlock(
                SHAREMIND_CONST_CAST(SharemindRecursiveMutex *)(mutex));
}

inline int SharemindRecursiveMutex_trylock_const(
        SharemindRecursiveMutex const * mutex)
{
    return SharemindRecursiveMutex_trylock(
                SHAREMIND_CONST_CAST(SharemindRecursiveMutex *)(mutex));
}
#pragma GCC diagnostic pop

SHAREMIND_EXTERN_C_END

#endif /* SHAREMIND_RECURSIVE_MUTEX_H */
