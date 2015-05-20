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

#include <pthread.h>
#include <stddef.h>
#include "extern_c.h"
#include "likely.h"


SHAREMIND_EXTERN_C_BEGIN

typedef struct SharemindMutex_ {
    pthread_mutex_t inner;
} SharemindMutex;

inline int SharemindMutex_init(SharemindMutex * mutex)
{ return pthread_mutex_init(&mutex->inner, NULL); }

inline int SharemindMutex_destroy(SharemindMutex * mutex)
{ return pthread_mutex_destroy(&mutex->inner); }

inline int SharemindMutex_lock(SharemindMutex * mutex)
{ return pthread_mutex_lock(&mutex->inner); }

inline int SharemindMutex_unlock(SharemindMutex * mutex)
{ return pthread_mutex_unlock(&mutex->inner); }

inline int SharemindMutex_trylock(SharemindMutex * mutex)
{ return pthread_mutex_trylock(&mutex->inner); }

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
inline int SharemindMutex_lock_const(
        const SharemindMutex * mutex)
{ return SharemindMutex_lock((SharemindMutex *) mutex); }

inline int SharemindMutex_unlock_const(
        const SharemindMutex * mutex)
{ return SharemindMutex_unlock((SharemindMutex *) mutex); }

inline int SharemindMutex_trylock_const(
        const SharemindMutex * mutex)
{ return SharemindMutex_trylock((SharemindMutex *) mutex); }
#pragma GCC diagnostic pop

SHAREMIND_EXTERN_C_END

#endif /* SHAREMIND_VECTOR_H */
