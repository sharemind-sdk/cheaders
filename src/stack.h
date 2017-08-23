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

#ifndef SHAREMIND_STACK_H
#define SHAREMIND_STACK_H

#include <stdbool.h>
#include "DebugOnly.h"
#include "extern_c.h"
#include "likely.h"
#include "null.h"


/**
  \todo Allow for more fine-grained declarations and definitions (e.g. to
        specify linking constraints etc).
*/

#define SHAREMIND_STACK_DECLARE(name,datatype,extradata,inlinePerhaps,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    struct name ## _item; \
    typedef struct { \
        struct name ## _item * d; \
        extradata \
    } name; \
    inlinePerhaps void name ## _init (name * s) \
            __attribute__ ((SHAREMIND_NDEBUG_ONLY(nonnull(1),) __VA_ARGS__)); \
    inlinePerhaps void name ## _destroy (name * s) \
            __attribute__ ((SHAREMIND_NDEBUG_ONLY(nonnull(1),) __VA_ARGS__)); \
    inlinePerhaps void name ## _destroy_with( \
            name * const s, \
            void (*destroyer)(datatype *)) \
            __attribute__ ((SHAREMIND_NDEBUG_ONLY(nonnull(1, 2),) \
                            __VA_ARGS__)); \
    inlinePerhaps datatype * name ## _push (name * s) \
            __attribute__ ((SHAREMIND_NDEBUG_ONLY(nonnull(1),) __VA_ARGS__)); \
    inlinePerhaps void name ## _pop (name * s) \
            __attribute__ ((SHAREMIND_NDEBUG_ONLY(nonnull(1),) __VA_ARGS__)); \
    inlinePerhaps datatype * name ## _top (name * s) \
            __attribute__ ((SHAREMIND_NDEBUG_ONLY(nonnull(1),) \
                            warn_unused_result, \
                            __VA_ARGS__)); \
    inlinePerhaps bool name ## _empty (name * s) \
            __attribute__ ((SHAREMIND_NDEBUG_ONLY(nonnull(1),) \
                            warn_unused_result, \
                            __VA_ARGS__)); \
    inlinePerhaps void name ## _foreach (name * s, void (*f)(datatype *)) \
            __attribute__ ((SHAREMIND_NDEBUG_ONLY(nonnull(1, 2),) \
                            __VA_ARGS__)); \
    SHAREMIND_EXTERN_C_END

#define SHAREMIND_STACK_DEFINE(name,datatype,mymalloc,myfree,inlinePerhaps) \
    SHAREMIND_EXTERN_C_BEGIN \
    struct name ## _item { \
        datatype value; \
        struct name ## _item * prev; \
    }; \
    inlinePerhaps void name ## _init (name * s) { \
        assert(s); \
        s->d = SHAREMIND_NULL; \
    } \
    inlinePerhaps void name ## _destroy (name * s) { \
        assert(s); \
        struct name ## _item * d = s->d; \
        if (d) { \
            struct name ## _item * prev = d->prev; \
            for (;;) { \
                myfree(d); \
                if (!prev) \
                    break; \
                d = prev; \
                prev = d->prev; \
            } \
        } \
    } \
    inlinePerhaps void name ## _destroy_with(name * const s, void (*destroyer)(datatype *)) { \
        assert(s); \
        assert(destroyer); \
        struct name ## _item * d = s->d; \
        if (d) { \
            struct name ## _item * prev = d->prev; \
            for (;;) { \
                (*destroyer)(&d->value); \
                myfree(d); \
                if (!prev) \
                    break; \
                d = prev; \
                prev = d->prev; \
            } \
        } \
    } \
    inlinePerhaps datatype * name ## _push (name * s) { \
        assert(s); \
        struct name ## _item * const n = \
                (struct name ## _item *) mymalloc(sizeof(*n)); \
        if (unlikely(!n)) \
            return SHAREMIND_NULL; \
        n->prev = s->d; \
        s->d = n; \
        return &n->value; \
    } \
    inlinePerhaps void name ## _pop (name * s) { \
        assert(s); \
        struct name ## _item * d = s->d; \
        assert(d); \
        s->d = d->prev; \
        myfree(d); \
    } \
    inlinePerhaps datatype * name ## _top (name * s) { \
        assert(s); \
        struct name ## _item * d = s->d; \
        assert(d); \
        return &d->value; \
    } \
    inlinePerhaps bool name ## _empty (name * s) { \
        assert(s); \
        return s->d == SHAREMIND_NULL; \
    } \
    inlinePerhaps void name ## _foreach (name * s, void (*f)(datatype *)) { \
        assert(s); \
        struct name ## _item * d = s->d; \
        while (d) { \
            (*f)(&d->value); \
            d = d->prev; \
        } \
    } \
    SHAREMIND_EXTERN_C_END

#endif /* SHAREMIND_STACK_H */
