/*
 * This file is a part of the Sharemind framework.
 * Copyright (C) Cybernetica AS
 *
 * All rights are reserved. Reproduction in whole or part is prohibited
 * without the written consent of the copyright owner. The usage of this
 * code is subject to the appropriate license agreement.
 */

#ifndef SHAREMIND_INSTRSET_H
#define SHAREMIND_INSTRSET_H

#include <stddef.h>
#include <stdint.h>
#include "likely.h"


/**
  \todo Allow for more fine-grained declarations and definitions (e.g. to
        specify linking constraints etc).
*/

#ifdef __cplusplus
#define SM_INSTRSET_EXTERN_C_BEGIN extern "C" {
#define SM_INSTRSET_EXTERN_C_END   }
#else
#define SM_INSTRSET_EXTERN_C_BEGIN
#define SM_INSTRSET_EXTERN_C_END
#endif

#define SM_INSTRSET_DECLARE(name,inlinePerhaps) \
    SM_INSTRSET_EXTERN_C_BEGIN \
    struct name ## _item; \
    typedef struct { \
        struct name ## _item * d[65536]; \
    } name; \
    inlinePerhaps void name ## _init (name * s) __attribute__ ((nonnull(1))); \
    inlinePerhaps void name ## _destroy (name * s) __attribute__ ((nonnull(1))); \
    inlinePerhaps int name ## _insert (name * s, uintptr_t value) __attribute__ ((nonnull(1))); \
    inlinePerhaps int name ## _contains (const name * s, uintptr_t value) __attribute__ ((nonnull(1), warn_unused_result)); \
    SM_INSTRSET_EXTERN_C_END

#define SM_INSTRSET_DEFINE(name,mymalloc,myfree,inlinePerhaps) \
    SM_INSTRSET_EXTERN_C_BEGIN \
    struct name ## _item { \
        uintptr_t value; \
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
    inlinePerhaps int name ## _insert (name * s, uintptr_t v) { \
        assert(s); \
        uint16_t hash = (uint16_t) v; \
        struct name ## _item ** l = &s->d[hash]; \
        struct name ## _item * p; \
        if (*l) { \
            do { \
                if ((*l)->value > v) \
                    break; \
                if ((*l)->value == v) \
                    return 1; \
                l = &(*l)->next; \
            } while (*l); \
            p = *l; \
        } else { \
            p = NULL; \
        } \
        *l = (struct name ## _item *) mymalloc(sizeof(struct name ## _item)); \
        if (!(*l)) { \
            *l = p; \
            return 0; \
        } \
        (*l)->value = v; \
        (*l)->next = p; \
        return 1; \
    } \
    inlinePerhaps int name ## _contains (const name * s, uintptr_t v) { \
        assert(s); \
        uint16_t hash = (uint16_t) v; \
        struct name ## _item * l = s->d[hash]; \
        while (l) { \
            if (l->value == v) \
                return 1; \
            if (l->value > v) \
                return 0; \
            l = l->next; \
        } \
        return 0; \
    } \
    SM_INSTRSET_EXTERN_C_END

#endif /* SHAREMIND_INSTRSET_H */
