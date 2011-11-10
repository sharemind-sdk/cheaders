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

#include <stddef.h>
#include <stdint.h>
#include "likely.h"


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

#define SM_MAP_KEYFREE_REGULAR(unused)
#define SM_MAP_KEYCOPY_REGULAR(pDest,src) ((*(pDest)) = (src), 1)

#define SM_MAP_KEY_EQUALS_DEFINE(name,keytype) \
    inline int name(keytype const k1, keytype const k2) { return k1 == k2; }

#define SM_MAP_KEY_LESS_THAN_DEFINE(name,keytype) \
    inline int name(keytype const k1, keytype const k2) { return k1 < k2; }

#define _SM_MAP_KEY_COMPARATORS_DEFINE(keytype_str,keytype) \
    SM_MAP_KEY_EQUALS_DEFINE(SM_MAP_KEY_EQUALS_ ## keytype_str, keytype) \
    SM_MAP_KEY_LESS_THAN_DEFINE(SM_MAP_KEY_LESS_THAN_ ## keytype_str, keytype)

#define SM_MAP_KEY_COMPARATORS_DEFINE(keytype) _SM_MAP_KEY_COMPARATORS_DEFINE(keytype,keytype)

SM_MAP_KEY_COMPARATORS_DEFINE(char)
_SM_MAP_KEY_COMPARATORS_DEFINE(signed_char,signed char)
_SM_MAP_KEY_COMPARATORS_DEFINE(unsigned_char,unsigned char)
SM_MAP_KEY_COMPARATORS_DEFINE(short)
_SM_MAP_KEY_COMPARATORS_DEFINE(unsigned_short,unsigned short)
SM_MAP_KEY_COMPARATORS_DEFINE(int)
SM_MAP_KEY_COMPARATORS_DEFINE(unsigned)
_SM_MAP_KEY_COMPARATORS_DEFINE(unsigned_int,unsigned int)
SM_MAP_KEY_COMPARATORS_DEFINE(long)
_SM_MAP_KEY_COMPARATORS_DEFINE(unsigned_long,unsigned long)
SM_MAP_KEY_COMPARATORS_DEFINE(size_t)
SM_MAP_KEY_COMPARATORS_DEFINE(int8_t)
SM_MAP_KEY_COMPARATORS_DEFINE(int16_t)
SM_MAP_KEY_COMPARATORS_DEFINE(int32_t)
SM_MAP_KEY_COMPARATORS_DEFINE(int64_t)
SM_MAP_KEY_COMPARATORS_DEFINE(uint8_t)
SM_MAP_KEY_COMPARATORS_DEFINE(uint16_t)
SM_MAP_KEY_COMPARATORS_DEFINE(uint32_t)
SM_MAP_KEY_COMPARATORS_DEFINE(uint64_t)
SM_MAP_KEY_COMPARATORS_DEFINE(int_fast8_t)
SM_MAP_KEY_COMPARATORS_DEFINE(int_fast16_t)
SM_MAP_KEY_COMPARATORS_DEFINE(int_fast32_t)
SM_MAP_KEY_COMPARATORS_DEFINE(int_fast64_t)
SM_MAP_KEY_COMPARATORS_DEFINE(uint_fast8_t)
SM_MAP_KEY_COMPARATORS_DEFINE(uint_fast16_t)
SM_MAP_KEY_COMPARATORS_DEFINE(uint_fast32_t)
SM_MAP_KEY_COMPARATORS_DEFINE(uint_fast64_t)
SM_MAP_KEY_COMPARATORS_DEFINE(int_least8_t)
SM_MAP_KEY_COMPARATORS_DEFINE(int_least16_t)
SM_MAP_KEY_COMPARATORS_DEFINE(int_least32_t)
SM_MAP_KEY_COMPARATORS_DEFINE(int_least64_t)
SM_MAP_KEY_COMPARATORS_DEFINE(uint_least8_t)
SM_MAP_KEY_COMPARATORS_DEFINE(uint_least16_t)
SM_MAP_KEY_COMPARATORS_DEFINE(uint_least32_t)
SM_MAP_KEY_COMPARATORS_DEFINE(uint_least64_t)

#define SM_MAP_DECLARE(name,keytype,valuetype,inlinePerhaps) \
    SM_MAP_EXTERN_C_BEGIN \
    struct name ## _item; \
    typedef struct { \
        struct name ## _item * d[65536]; \
    } name; \
    inlinePerhaps void name ## _init (name * s) __attribute__ ((nonnull(1))); \
    inlinePerhaps void name ## _destroy (name * s) __attribute__ ((nonnull(1))); \
    inlinePerhaps int name ## _foreach (name * s, int (*f)(valuetype *)) __attribute__ ((nonnull(1, 2))); \
    inlinePerhaps void name ## _foreach_void (name * s, void (*f)(valuetype *)) __attribute__ ((nonnull(1, 2))); \
    inlinePerhaps valuetype * name ## _insert (name * s, keytype key) __attribute__ ((nonnull(1))); \
    inlinePerhaps int name ## _remove (name * s, keytype key) __attribute__ ((nonnull(1))); \
    inlinePerhaps valuetype * name ## _get (name * s, keytype key) __attribute__ ((nonnull(1), warn_unused_result)); \
    SM_MAP_EXTERN_C_END

#define SM_MAP_DEFINE(name,keytype,valuetype,keyhashfunction,keyequals,keylessthan,keycopy,keyfree,mymalloc,myfree,inlinePerhaps) \
    SM_MAP_EXTERN_C_BEGIN \
    struct name ## _item { \
        keytype key; \
        valuetype value; \
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
                keyfree(s->d[i]->key); \
                myfree(s->d[i]); \
                s->d[i] = next; \
            } \
        } \
    } \
    inlinePerhaps int name ## _foreach (name * s, int (*f)(valuetype *)) { \
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
    inlinePerhaps void name ## _foreach_void (name * s, void (*f)(valuetype *)) { \
        assert(s); \
        assert(f); \
        for (size_t i = 0; i < 65536; i++) { \
            struct name ## _item * item = s->d[i]; \
            while (item) { \
                struct name ## _item * next = item->next; \
                (*f)(&item->value); \
                item = next; \
            } \
        } \
    } \
    inlinePerhaps valuetype * name ## _insert (name * s, keytype key) { \
        assert(s); \
        uint16_t hash = keyhashfunction(key); \
        struct name ## _item ** l = &s->d[hash]; \
        struct name ## _item * p; \
        if (*l) { \
            do { \
                if (keylessthan(key, (*l)->key)) \
                    break; \
                if (keyequals(key, (*l)->key)) { \
                    keyfree((*l)->key); \
                    keycopy(&(*l)->key, key); \
                    return &(*l)->value; \
                } \
                l = &(*l)->next; \
            } while (*l); \
            p = *l; \
        } else { \
            p = NULL; \
        } \
        *l = (struct name ## _item *) mymalloc(sizeof(struct name ## _item)); \
        if (!(*l)) { \
            *l = p; \
            return NULL; \
        } \
        if (!keycopy(&(*l)->key, key)) { \
            myfree(*l); \
            *l = p; \
            return NULL; \
        } \
        (*l)->next = p; \
        return &(*l)->value; \
    } \
    inlinePerhaps int name ## _remove (name * s, keytype key) { \
        assert(s); \
        uint16_t hash = keyhashfunction(key); \
        struct name ## _item ** prevPtr = &s->d[hash]; \
        struct name ## _item * l = *prevPtr; \
        while (l) { \
            if (keyequals(key, l->key)) { \
                *prevPtr = l->next; \
                keyfree(l->key); \
                myfree(l); \
                return 1; \
            } \
            if (keylessthan(key, l->key)) \
                return 0; \
            prevPtr = &l->next; \
            l = *prevPtr; \
        } \
        return 0; \
    } \
    inlinePerhaps valuetype * name ## _get (name * s, keytype key) { \
        assert(s); \
        uint16_t hash = keyhashfunction(key); \
        struct name ## _item * l = s->d[hash]; \
        while (l) { \
            if (keyequals(key, l->key)) \
                return &l->value; \
            if (keylessthan(key, l->key)) \
                return NULL; \
            l = l->next; \
        } \
        return NULL; \
    } \
    SM_MAP_EXTERN_C_END

#endif /* MAP_H */
