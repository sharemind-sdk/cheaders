/*
 * This file is a part of the Sharemind framework.
 * Copyright (C) Cybernetica AS
 *
 * All rights are reserved. Reproduction in whole or part is prohibited
 * without the written consent of the copyright owner. The usage of this
 * code is subject to the appropriate license agreement.
 */

#ifndef SHAREMIND_STACK_H
#define SHAREMIND_STACK_H

#include "likely.h"


/**
  \todo Allow for more fine-grained declarations and definitions (e.g. to
        specify linking constraints etc).
*/

#ifdef __cplusplus
#define SM_STACK_EXTERN_C_BEGIN extern "C" {
#define SM_STACK_EXTERN_C_END   }
#else
#define SM_STACK_EXTERN_C_BEGIN
#define SM_STACK_EXTERN_C_END
#endif

#define SM_STACK_DECLARE(name,datatype,extradata,inlinePerhaps) \
    SM_STACK_EXTERN_C_BEGIN \
    struct name ## _item; \
    typedef struct { \
        struct name ## _item * d; \
        extradata \
    } name; \
    inlinePerhaps void name ## _init (name * s) __attribute__ ((nonnull(1))); \
    inlinePerhaps void name ## _destroy (name * s) __attribute__ ((nonnull(1))); \
    inlinePerhaps void name ## _destroy_with(name * const s, void (*destroyer)(datatype *)) __attribute__ ((nonnull(1, 2))); \
    inlinePerhaps datatype * name ## _push (name * s) __attribute__ ((nonnull(1))); \
    inlinePerhaps void name ## _pop (name * s) __attribute__ ((nonnull(1))); \
    inlinePerhaps datatype * name ## _top (name * s) __attribute__ ((nonnull(1), warn_unused_result)); \
    inlinePerhaps int name ## _empty (name * s) __attribute__ ((nonnull(1), warn_unused_result)); \
    inlinePerhaps void name ## _foreach (name * s, void (*f)(datatype *)) __attribute__ ((nonnull(1, 2))); \
    SM_STACK_EXTERN_C_END

#define SM_STACK_DEFINE(name,datatype,mymalloc,myfree,inlinePerhaps) \
    SM_STACK_EXTERN_C_BEGIN \
    struct name ## _item { \
        datatype value; \
        struct name ## _item * prev; \
    }; \
    inlinePerhaps void name ## _init (name * s) { \
        assert(s); \
        s->d = NULL; \
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
        struct name ## _item * n = (struct name ## _item *) mymalloc(sizeof(struct name ## _item)); \
        if (unlikely(!n)) \
            return NULL; \
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
    inlinePerhaps int name ## _empty (name * s) { \
        assert(s); \
        return s->d == NULL; \
    } \
    inlinePerhaps void name ## _foreach (name * s, void (*f)(datatype *)) { \
        assert(s); \
        struct name ## _item * d = s->d; \
        while (d) { \
            (*f)(&d->value); \
            d = d->prev; \
        } \
    } \
    SM_STACK_EXTERN_C_END

#endif /* SHAREMIND_STACK_H */
