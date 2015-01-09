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
