/*
 * This file is a part of the Sharemind framework.
 * Copyright (C) Cybernetica AS
 *
 * All rights are reserved. Reproduction in whole or part is prohibited
 * without the written consent of the copyright owner. The usage of this
 * code is subject to the appropriate license agreement.
 */

#ifndef STACK_H
#define STACK_H

#include "likely.h"


/**
  \todo Allow for more fine-grained declarations and definitions (e.g. to
        specify linking constraints etc).
*/

#ifdef __cplusplus
#define SVM_STACK_EXTERN_C_BEGIN extern "C" {
#define SVM_STACK_EXTERN_C_END   }
#else
#define SVM_STACK_EXTERN_C_BEGIN
#define SVM_STACK_EXTERN_C_END
#endif

#define SVM_STACK_DECLARE(name,datatype,extradata) \
    SVM_STACK_EXTERN_C_BEGIN \
    struct name ## _item; \
    struct name { \
        struct name ## _item * d; \
        extradata \
    }; \
    void name ## _init (struct name * s) __attribute__ ((nonnull(1))); \
    void name ## _destroy (struct name * s) __attribute__ ((nonnull(1))); \
    void name ## _destroy_with(struct name * const s, void (*destroyer)(datatype *)) __attribute__ ((nonnull(1, 2))); \
    datatype * name ## _push (struct name * s) __attribute__ ((nonnull(1))); \
    void name ## _pop (struct name * s) __attribute__ ((nonnull(1))); \
    datatype * name ## _top (struct name * s) __attribute__ ((nonnull(1), warn_unused_result)); \
    int name ## _empty (struct name * s) __attribute__ ((nonnull(1), warn_unused_result)); \
    void name ## _foreach (struct name * s, void (*f)(datatype *)) __attribute__ ((nonnull(1, 2))); \
    SVM_STACK_EXTERN_C_END

#define SVM_STACK_DEFINE(name,datatype,mymalloc,myfree) \
    SVM_STACK_EXTERN_C_BEGIN \
    struct name ## _item { \
        datatype value; \
        struct name ## _item * prev; \
    }; \
    void name ## _init (struct name * s) { \
        assert(s); \
        s->d = NULL; \
    } \
    void name ## _destroy (struct name * s) { \
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
    void name ## _destroy_with(struct name * const s, void (*destroyer)(datatype *)) { \
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
    datatype * name ## _push (struct name * s) { \
        assert(s); \
        struct name ## _item * n = mymalloc(sizeof(struct name ## _item)); \
        if (unlikely(!n)) \
            return NULL; \
        n->prev = s->d; \
        s->d = n; \
        return &n->value; \
    } \
    void name ## _pop (struct name * s) { \
        assert(s); \
        struct name ## _item * d = s->d; \
        assert(d); \
        s->d = d->prev; \
        myfree(d); \
    } \
    datatype * name ## _top (struct name * s) { \
        assert(s); \
        struct name ## _item * d = s->d; \
        assert(d); \
        return &d->value; \
    } \
    int name ## _empty (struct name * s) { \
        assert(s); \
        return s->d == NULL; \
    } \
    void name ## _foreach (struct name * s, void (*f)(datatype *)) { \
        assert(s); \
        struct name ## _item * d = s->d; \
        while (d) { \
            (*f)(&d->value); \
            d = d->prev; \
        } \
    } \
    SVM_STACK_EXTERN_C_END

#endif /* STACK_H */
