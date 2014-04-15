/*
 * This file is a part of the Sharemind framework.
 * Copyright (C) Cybernetica AS
 *
 * All rights are reserved. Reproduction in whole or part is prohibited
 * without the written consent of the copyright owner. The usage of this
 * code is subject to the appropriate license agreement.
 */

#ifndef SHAREMIND_SIMPLESET_H
#define SHAREMIND_SIMPLESET_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "likely.h"


/**
  \todo Allow for more fine-grained declarations and definitions (e.g. to
        specify linking constraints etc).
*/

#ifdef __cplusplus
#define SHAREMIND_SIMPLESET_EXTERN_C_BEGIN extern "C" {
#define SHAREMIND_SIMPLESET_EXTERN_C_END   }
#define SHAREMIND_SIMPLESET_ALLOC_CAST(type) ((type))
#else
#define SHAREMIND_SIMPLESET_EXTERN_C_BEGIN
#define SHAREMIND_SIMPLESET_EXTERN_C_END
#define SHAREMIND_SIMPLESET_ALLOC_CAST(type)
#endif

#define SHAREMIND_SIMPLESET_DECLARE(name,datatype,inlinePerhaps) \
    SHAREMIND_SIMPLESET_EXTERN_C_BEGIN \
    struct name ## _item; \
    typedef struct { \
        struct name ## _item * d[65536]; \
    } name; \
    inlinePerhaps void name ## _init (name * s) __attribute__ ((nonnull(1))); \
    inlinePerhaps void name ## _destroy (name * s) __attribute__ ((nonnull(1))); \
    inlinePerhaps bool name ## _insert (name * s, datatype value) __attribute__ ((nonnull(1))); \
    inlinePerhaps bool name ## _contains (const name * s, datatype value) __attribute__ ((nonnull(1), warn_unused_result)); \
    inlinePerhaps bool name ## _foreach(name * s, bool (*f)(datatype)) __attribute__ ((nonnull(1, 2))); \
    inlinePerhaps void name ## _foreach_void(name * s, void (*f)(datatype)) __attribute__ ((nonnull(1, 2))); \
    SHAREMIND_SIMPLESET_EXTERN_C_END

#define SHAREMIND_SIMPLESET_DEFINE(name,datatype,mymalloc,myfree,inlinePerhaps) \
    SHAREMIND_SIMPLESET_EXTERN_C_BEGIN \
    struct name ## _item { \
        datatype value; \
        struct name ## _item * next; \
    }; \
    inlinePerhaps void name ## _init (name * s) { \
        assert(s); \
        for (size_t i = 0; i < 65536; i++) \
            s->d[i] = NULL; \
    } \
    inlinePerhaps void name ## _destroy (name * s) { \
        assert(s); \
        for (size_t i = 0; i < 65536; i++) { \
            while (s->d[i]) { \
                struct name ## _item * next = s->d[i]->next; \
                myfree(s->d[i]); \
                s->d[i] = next; \
            } \
        } \
    } \
    inlinePerhaps bool name ## _insert (name * s, datatype v) { \
        assert(s); \
        uint16_t hash = (uint16_t) v; \
        struct name ## _item ** l = &s->d[hash]; \
        struct name ## _item * p; \
        if (*l) { \
            do { \
                if ((*l)->value > v) \
                    break; \
                if ((*l)->value == v) \
                    return true; \
                l = &(*l)->next; \
            } while (*l); \
            p = *l; \
        } else { \
            p = NULL; \
        } \
        *l = SHAREMIND_SIMPLESET_ALLOC_CAST(struct name ## _item *) mymalloc(sizeof(**l)); \
        if (!(*l)) { \
            *l = p; \
            return false; \
        } \
        (*l)->value = v; \
        (*l)->next = p; \
        return true; \
    } \
    inlinePerhaps bool name ## _contains (const name * s, datatype v) { \
        assert(s); \
        uint16_t hash = (uint16_t) v; \
        struct name ## _item * l = s->d[hash]; \
        while (l) { \
            if (l->value == v) \
                return true; \
            if (l->value > v) \
                return false; \
            l = l->next; \
        } \
        return false; \
    } \
    inlinePerhaps bool name ## _foreach(name * s, bool (*f)(datatype)) { \
        assert(s); \
        for (size_t i = 0; i < 65536; i++) { \
            struct name ## _item * current = s->d[i]; \
            while (current) { \
                struct name ## _item * next = current->next; \
                if (!(*f)(current->value)) \
                    return false; \
                current = next; \
            } \
        } \
        return true; \
    } \
    inlinePerhaps void name ## _foreach_void(name * s, void (*f)(datatype)) { \
        assert(s); \
        for (size_t i = 0; i < 65536; i++) { \
            struct name ## _item * current = s->d[i]; \
            while (current) { \
                struct name ## _item * next = current->next; \
                (*f)(current->value); \
                current = next; \
            } \
        } \
    } \
    SHAREMIND_SIMPLESET_EXTERN_C_END

#endif /* SHAREMIND_SIMPLESET_H */
