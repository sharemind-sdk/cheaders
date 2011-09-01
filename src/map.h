/*
 * This file is a part of the Sharemind framework.
 * Copyright (C) Cybernetica AS
 *
 * All rights are reserved. Reproduction in whole or part is prohibited
 * without the written consent of the copyright owner. The usage of this
 * code is subject to the appropriate license agreement.
 */

#ifndef MAP_H
#define MAP_H

#include "../likely.h"


/**
  \todo Allow for more fine-grained declarations and definitions (e.g. to
        specify linking constraints etc).
*/

#ifdef __cplusplus
#define SM_MAP_EXTERN_C_BEGIN extern "C" {
#define SM_MAP_EXTERN_C_END   }
#else
#define SM_MAP_EXTERN_C_BEGIN
#define SM_MAP_EXTERN_C_END
#endif

#define SM_MAP_DECLARE(name,keytype,valuetype,inlinePerhaps) \
    SM_MAP_EXTERN_C_BEGIN \
    struct name ## _item; \
    struct name { \
        struct name ## _item * d[65536]; \
    }; \
    inlinePerhaps void name ## _init (struct name * s) __attribute__ ((nonnull(1))); \
    inlinePerhaps void name ## _destroy (struct name * s) __attribute__ ((nonnull(1))); \
    inlinePerhaps int name ## _foreach (struct name * s, int (*f)(valuetype *)) __attribute__ ((nonnull(1, 2))); \
    inlinePerhaps valuetype * name ## _insert (struct name * s, keytype key) __attribute__ ((nonnull(1))); \
    inlinePerhaps int name ## _remove (struct name * s, keytype key) __attribute__ ((nonnull(1))); \
    inlinePerhaps valuetype * name ## _get (struct name * s, keytype key) __attribute__ ((nonnull(1), warn_unused_result)); \
    SM_MAP_EXTERN_C_END

#define SM_MAP_DEFINE(name,keytype,valuetype,keyhashfunction,mymalloc,myfree,inlinePerhaps) \
    SM_MAP_EXTERN_C_BEGIN \
    struct name ## _item { \
        keytype key; \
        valuetype value; \
        struct name ## _item * next; \
    }; \
    inlinePerhaps void name ## _init (struct name * s) { \
        assert(s); \
        for (size_t i = 0; i < 65536; i++) \
            s->d[i] = NULL; \
    } \
    inlinePerhaps void name ## _destroy (struct name * s) { \
        assert(s); \
        for (size_t i = 0; i < 65536; i++) { \
            while (s->d[i]) { \
                struct name ## _item * next = s->d[i]->next; \
                myfree(s->d[i]); \
                s->d[i] = next; \
            } \
        } \
    } \
    inlinePerhaps int name ## _foreach (struct name * s, int (*f)(valuetype *)) { \
        assert(s); \
        assert(f); \
        for (size_t i = 0; i < 65536; i++) { \
            struct name ## _item * item = s->d[i]; \
            while (item) { \
                struct name ## _item * next = item->next; \
                if (!((*f)(&item->value))) \
                    return 0; \
                item = next; \
            } \
        } \
        return 1; \
    } \
    inlinePerhaps valuetype * name ## _insert (struct name * s, keytype key) { \
        assert(s); \
        uint16_t hash = keyhashfunction(key); \
        struct name ## _item ** l = &s->d[hash]; \
        struct name ## _item * p; \
        if (*l) { \
            do { \
                if ((*l)->key > key) \
                    break; \
                if ((*l)->key == key) \
                    return &(*l)->value; \
                l = &(*l)->next; \
            } while (*l); \
            p = *l; \
        } else { \
            p = NULL; \
        } \
        *l = mymalloc(sizeof(struct name ## _item)); \
        if (!(*l)) { \
            *l = p; \
            return NULL; \
        } \
        (*l)->key = key; \
        (*l)->next = p; \
        return &(*l)->value; \
    } \
    inlinePerhaps int name ## _remove (struct name * s, keytype key) { \
        assert(s); \
        uint16_t hash = keyhashfunction(key); \
        struct name ## _item ** prevPtr = &s->d[hash]; \
        struct name ## _item * l = *prevPtr; \
        while (l) { \
            if (l->key == key) { \
                *prevPtr = l->next; \
                myfree(l); \
                return 1; \
            } \
            if (l->key > key) \
                return 0; \
            prevPtr = &l->next; \
            l = *prevPtr; \
        } \
        return 0; \
    } \
    inlinePerhaps valuetype * name ## _get (struct name * s, keytype key) { \
        assert(s); \
        uint16_t hash = keyhashfunction(key); \
        struct name ## _item * l = s->d[hash]; \
        while (l) { \
            if (l->key == key) \
                return &l->value; \
            if (l->key > key) \
                return NULL; \
            l = l->next; \
        } \
        return NULL; \
    } \
    SM_MAP_EXTERN_C_END

#endif /* MAP_H */
