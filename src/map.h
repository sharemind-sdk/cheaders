/*
 * This file is a part of the Sharemind framework.
 * Copyright (C) Cybernetica AS
 *
 * All rights are reserved. Reproduction in whole or part is prohibited
 * without the written consent of the copyright owner. The usage of this
 * code is subject to the appropriate license agreement.
 */

#ifndef SHAREMIND_MAP_H
#define SHAREMIND_MAP_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "comma.h"
#include "likely.h"


/**
  \todo Allow for more fine-grained declarations and definitions (e.g. to
        specify linking constraints etc).
*/

#ifdef __cplusplus
#define SHAREMIND_MAP_EXTERN_C_BEGIN extern "C" {
#define SHAREMIND_MAP_EXTERN_C_END   }
#define SHAREMIND_MAP_ALLOC_CAST(type) ((type))
#else
#define SHAREMIND_MAP_EXTERN_C_BEGIN
#define SHAREMIND_MAP_EXTERN_C_END
#define SHAREMIND_MAP_ALLOC_CAST(type)
#endif

#define SHAREMIND_MAP_KEYINIT_REGULAR(unused) (1)
#define SHAREMIND_MAP_KEYFREE_REGULAR(unused)
#define SHAREMIND_MAP_KEYCOPY_REGULAR(pDest,src) ((*(pDest)) = (src), 1)

#define SHAREMIND_MAP_KEY_EQUALS_DEFINE(name,keytype) \
    inline bool name(keytype const k1, keytype const k2) { return k1 == k2; }

#define SHAREMIND_MAP_KEY_LESS_THAN_DEFINE(name,keytype) \
    inline bool name(keytype const k1, keytype const k2) { return k1 < k2; }

#define SHAREMIND_MAP_KEY_COMPARATORS_DEFINE_(keytype_str,keytype) \
    SHAREMIND_MAP_KEY_EQUALS_DEFINE(SHAREMIND_MAP_KEY_EQUALS_ ## keytype_str, keytype) \
    SHAREMIND_MAP_KEY_LESS_THAN_DEFINE(SHAREMIND_MAP_KEY_LESS_THAN_ ## keytype_str, keytype)

#define SHAREMIND_MAP_KEY_COMPARATORS_DEFINE(keytype) SHAREMIND_MAP_KEY_COMPARATORS_DEFINE_(keytype,keytype)

SHAREMIND_MAP_KEY_COMPARATORS_DEFINE(char)
SHAREMIND_MAP_KEY_COMPARATORS_DEFINE_(signed_char,signed char)
SHAREMIND_MAP_KEY_COMPARATORS_DEFINE_(unsigned_char,unsigned char)
SHAREMIND_MAP_KEY_COMPARATORS_DEFINE(short)
SHAREMIND_MAP_KEY_COMPARATORS_DEFINE_(unsigned_short,unsigned short)
SHAREMIND_MAP_KEY_COMPARATORS_DEFINE(int)
SHAREMIND_MAP_KEY_COMPARATORS_DEFINE(unsigned)
SHAREMIND_MAP_KEY_COMPARATORS_DEFINE_(unsigned_int,unsigned int)
SHAREMIND_MAP_KEY_COMPARATORS_DEFINE(long)
SHAREMIND_MAP_KEY_COMPARATORS_DEFINE_(unsigned_long,unsigned long)
SHAREMIND_MAP_KEY_COMPARATORS_DEFINE(size_t)
SHAREMIND_MAP_KEY_COMPARATORS_DEFINE(int8_t)
SHAREMIND_MAP_KEY_COMPARATORS_DEFINE(int16_t)
SHAREMIND_MAP_KEY_COMPARATORS_DEFINE(int32_t)
SHAREMIND_MAP_KEY_COMPARATORS_DEFINE(int64_t)
SHAREMIND_MAP_KEY_COMPARATORS_DEFINE(uint8_t)
SHAREMIND_MAP_KEY_COMPARATORS_DEFINE(uint16_t)
SHAREMIND_MAP_KEY_COMPARATORS_DEFINE(uint32_t)
SHAREMIND_MAP_KEY_COMPARATORS_DEFINE(uint64_t)
SHAREMIND_MAP_KEY_COMPARATORS_DEFINE(int_fast8_t)
SHAREMIND_MAP_KEY_COMPARATORS_DEFINE(int_fast16_t)
SHAREMIND_MAP_KEY_COMPARATORS_DEFINE(int_fast32_t)
SHAREMIND_MAP_KEY_COMPARATORS_DEFINE(int_fast64_t)
SHAREMIND_MAP_KEY_COMPARATORS_DEFINE(uint_fast8_t)
SHAREMIND_MAP_KEY_COMPARATORS_DEFINE(uint_fast16_t)
SHAREMIND_MAP_KEY_COMPARATORS_DEFINE(uint_fast32_t)
SHAREMIND_MAP_KEY_COMPARATORS_DEFINE(uint_fast64_t)
SHAREMIND_MAP_KEY_COMPARATORS_DEFINE(int_least8_t)
SHAREMIND_MAP_KEY_COMPARATORS_DEFINE(int_least16_t)
SHAREMIND_MAP_KEY_COMPARATORS_DEFINE(int_least32_t)
SHAREMIND_MAP_KEY_COMPARATORS_DEFINE(int_least64_t)
SHAREMIND_MAP_KEY_COMPARATORS_DEFINE(uint_least8_t)
SHAREMIND_MAP_KEY_COMPARATORS_DEFINE(uint_least16_t)
SHAREMIND_MAP_KEY_COMPARATORS_DEFINE(uint_least32_t)
SHAREMIND_MAP_KEY_COMPARATORS_DEFINE(uint_least64_t)
SHAREMIND_MAP_KEY_COMPARATORS_DEFINE_(voidptr,void *)

#define SHAREMIND_MAP_DECLARE(name,keytype,constkeytype,valuetype,inlinePerhaps) \
    SHAREMIND_MAP_EXTERN_C_BEGIN \
    struct name ## _item; \
    typedef struct { \
        size_t size; \
        struct name ## _item * d[65536]; \
    } name; \
    inlinePerhaps void name ## _init (name * s) __attribute__ ((nonnull(1))); \
    inlinePerhaps void name ## _destroy (name * s) __attribute__ ((nonnull(1))); \
    inlinePerhaps void name ## _destroy_with (name * s, void (*destroyer)(constkeytype *, valuetype *)) __attribute__ ((nonnull(1))); \
    inlinePerhaps constkeytype * name ## _key_at (name const * s, size_t index) __attribute__ ((nonnull(1))); \
    inlinePerhaps valuetype * name ## _value_at (name const * s, size_t index) __attribute__ ((nonnull(1))); \
    inlinePerhaps bool name ## _foreach (name * s, bool (*f)(constkeytype *, valuetype *)) __attribute__ ((nonnull(1, 2))); \
    inlinePerhaps void name ## _foreach_void (name * s, void (*f)(constkeytype *, valuetype *)) __attribute__ ((nonnull(1, 2))); \
    inlinePerhaps void * name ## _insertHint(name * s, constkeytype key) __attribute__ ((nonnull(1))); \
    inlinePerhaps valuetype * name ## _insertAtHint(name * s, constkeytype key, void * const hint) __attribute__ ((nonnull(1,3))); \
    inlinePerhaps valuetype * name ## _insertNew(name * s, constkeytype key) __attribute__ ((nonnull(1))); \
    inlinePerhaps valuetype * name ## _get_or_insert (name * s, constkeytype key) __attribute__ ((deprecated,nonnull(1))); \
    inlinePerhaps bool name ## _remove (name * s, constkeytype key) __attribute__ ((nonnull(1))); \
    inlinePerhaps bool name ## _remove_with (name * s, constkeytype key, void (*destroyer)(valuetype *)) __attribute__ ((nonnull(1))); \
    inlinePerhaps valuetype * name ## _get (name const * s, constkeytype key) __attribute__ ((nonnull(1), warn_unused_result)); \
    SHAREMIND_MAP_EXTERN_C_END

#define SHAREMIND_MAP_DECLARE_FOREACH_WITH(name,constkeytype,valuetype,withname,types,inlinePerhaps) \
    SHAREMIND_MAP_EXTERN_C_BEGIN \
    inlinePerhaps bool name ## _foreach_with_ ## withname (name * s, bool (*f)(constkeytype *, valuetype * types) types) __attribute__ ((nonnull(1, 2))); \
    SHAREMIND_MAP_EXTERN_C_END

#define SHAREMIND_MAP_DECLARE_FOREACH_WITH_INLINE(prefix,name,withname,params) \
    SHAREMIND_MAP_EXTERN_C_BEGIN \
    prefix name ## _foreach_with_ ## withname (name * s params) \
            __attribute__ ((nonnull(1))); \
    SHAREMIND_MAP_EXTERN_C_END

#define SHAREMIND_MAP_DEFINE(name,keytype,constkeytype,valuetype,keyhashfunction,keyequals,keylessthan,keyinit,keycopy,keyfree,mymalloc,myfree,inlinePerhaps) \
    SHAREMIND_MAP_EXTERN_C_BEGIN \
    struct name ## _item { \
        keytype key; \
        valuetype value; \
        struct name ## _item * next; \
    }; \
    inlinePerhaps void name ## _init (name * s) { \
        assert(s); \
        s->size = 0u; \
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
    inlinePerhaps void name ## _destroy_with (name * s, void (*destroyer)(constkeytype *, valuetype *)) { \
        assert(s); \
        assert(destroyer); \
        for (size_t i = 0; i < 65536; i++) { \
            while (s->d[i]) { \
                struct name ## _item * next = s->d[i]->next; \
                destroyer((constkeytype *) &s->d[i]->key, &s->d[i]->value); \
                keyfree(s->d[i]->key); \
                myfree(s->d[i]); \
                s->d[i] = next; \
            } \
        } \
    } \
    inlinePerhaps constkeytype * name ## _key_at (name const * s, size_t index) { \
        assert(s); \
        for (size_t i = 0; i < 65536; i++) { \
            struct name ## _item * item = s->d[i]; \
            while (item) { \
                struct name ## _item * next = item->next; \
                if (!index) \
                    return (constkeytype *) &item->key; \
                index--; \
                item = next; \
            } \
        } \
        return NULL; \
    } \
    inlinePerhaps valuetype * name ## _value_at (name const * s, size_t index) { \
        assert(s); \
        for (size_t i = 0; i < 65536; i++) { \
            struct name ## _item * item = s->d[i]; \
            while (item) { \
                if (!index) \
                    return &item->value; \
                index--; \
                item = item->next; \
            } \
        } \
        return NULL; \
    } \
    inlinePerhaps bool name ## _foreach (name * s, bool (*f)(constkeytype *, valuetype *)) { \
        assert(s); \
        assert(f); \
        for (size_t i = 0; i < 65536; i++) { \
            struct name ## _item * item = s->d[i]; \
            while (item) { \
                struct name ## _item * next = item->next; \
                if (!((*f)((constkeytype *) &item->key, &item->value))) \
                    return false; \
                item = next; \
            } \
        } \
        return true; \
    } \
    inlinePerhaps void name ## _foreach_void (name * s, void (*f)(constkeytype *, valuetype *)) { \
        assert(s); \
        assert(f); \
        for (size_t i = 0; i < 65536; i++) { \
            struct name ## _item * item = s->d[i]; \
            while (item) { \
                struct name ## _item * next = item->next; \
                (*f)((constkeytype *) &item->key, &item->value); \
                item = next; \
            } \
        } \
    } \
    inlinePerhaps void * name ## _insertHint(name * s, constkeytype key) { \
        assert(s); \
        if (s->size == SIZE_MAX) \
            return NULL; \
        struct name ## _item ** l = &s->d[(uint16_t) (keyhashfunction)]; \
        while ((*l) && !(keylessthan(key, (*l)->key))) { \
            if (keyequals(key, (*l)->key)) \
                return NULL; \
            l = &(*l)->next; \
        } \
        return l; \
    } \
    inlinePerhaps valuetype * name ## _insertAtHint(name * s, \
                                                    constkeytype key, \
                                                    void * const hint) \
    { \
        assert(s); \
        assert(hint); \
        struct name ## _item * newItem = \
                SHAREMIND_MAP_ALLOC_CAST(struct name ## _item *) mymalloc(sizeof(struct name ## _item)); \
        if (!newItem) \
            return NULL; \
        if (!keycopy(&newItem->key, key)) { \
            myfree(newItem); \
            return NULL; \
        } \
        struct name ## _item ** l = (struct name ## _item **) hint; \
        newItem->next = (*l); \
        (*l) = newItem; \
        s->size++; \
        return &newItem->value; \
    } \
    inlinePerhaps valuetype * name ## _insertNew(name * s, constkeytype key) { \
        assert(s); \
        void * const hint = name ## _insertHint(s, key); \
        assert(hint); \
        return name ## _insertAtHint(s, key, hint);\
    } \
    inlinePerhaps valuetype * name ## _get_or_insert (name * s, constkeytype key) { \
        assert(s); \
        if (s->size == SIZE_MAX) \
            return NULL; \
        uint16_t hash = (uint16_t) (keyhashfunction); \
        struct name ## _item ** l = &s->d[hash]; \
        struct name ## _item * p; \
        if (*l) { \
            do { \
                if (keylessthan(key, (*l)->key)) \
                    break; \
                if (keyequals(key, (*l)->key)) { \
                    if (!keycopy(&(*l)->key, key)) \
                        return NULL; \
                    return &(*l)->value; \
                } \
                l = &(*l)->next; \
            } while (*l); \
            p = *l; \
        } else { \
            p = NULL; \
        } \
        *l = SHAREMIND_MAP_ALLOC_CAST(struct name ## _item *) mymalloc(sizeof(**l)); \
        if (!(*l)) { \
            *l = p; \
            return NULL; \
        } \
        if (!keyinit(&(*l)->key) || !keycopy(&(*l)->key, key)) { \
            myfree(*l); \
            *l = p; \
            return NULL; \
        } \
        (*l)->next = p; \
        s->size++; \
        return &(*l)->value; \
    } \
    inlinePerhaps bool name ## _remove (name * s, constkeytype key) { \
        assert(s); \
        uint16_t hash = (uint16_t) (keyhashfunction); \
        struct name ## _item ** prevPtr = &s->d[hash]; \
        struct name ## _item * l = *prevPtr; \
        while (l) { \
            if (keyequals(key, l->key)) { \
                *prevPtr = l->next; \
                keyfree(l->key); \
                myfree(l); \
                s->size--; \
                return true; \
            } \
            if (keylessthan(key, l->key)) \
                return false; \
            prevPtr = &l->next; \
            l = *prevPtr; \
        } \
        return false; \
    } \
    inlinePerhaps bool name ## _remove_with (name * s, constkeytype key, void (*destroyer)(valuetype *)) { \
        assert(s); \
        uint16_t hash = (uint16_t) (keyhashfunction); \
        struct name ## _item ** prevPtr = &s->d[hash]; \
        struct name ## _item * l = *prevPtr; \
        while (l) { \
            if (keyequals(key, l->key)) { \
                *prevPtr = l->next; \
                destroyer(&l->value); \
                keyfree(l->key); \
                myfree(l); \
                s->size--; \
                return true; \
            } \
            if (keylessthan(key, l->key)) \
                return false; \
            prevPtr = &l->next; \
            l = *prevPtr; \
        } \
        return false; \
    } \
    inlinePerhaps valuetype * name ## _get (name const * s, constkeytype key) { \
        assert(s); \
        uint16_t hash = (uint16_t) (keyhashfunction); \
        struct name ## _item * l = s->d[hash]; \
        while (l) { \
            if (keyequals(key, l->key)) \
                return &l->value; \
            if (keylessthan(key, l->key)) \
                return NULL; \
            l = l->next; \
        } \
        return NULL; \
    }

#define SHAREMIND_MAP_DEFINE_FOREACH_WITH(name,constkeytype,valuetype,withname,types,params,args,inlinePerhaps) \
    SHAREMIND_MAP_EXTERN_C_BEGIN \
    inlinePerhaps bool name ## _foreach_with_ ## withname (name * s, bool (*f)(constkeytype *, valuetype *, types) params) { \
        assert(s); \
        assert(f); \
        for (size_t i = 0; i < 65536; i++) { \
            struct name ## _item * item = s->d[i]; \
            while (item) { \
                struct name ## _item * next = item->next; \
                if (!((*f)((constkeytype *) &item->key, &item->value args))) \
                    return false; \
                item = next; \
            } \
        } \
        return true; \
    } \
    SHAREMIND_MAP_EXTERN_C_END

#define SHAREMIND_MAP_DEFINE_FOREACH_WITH_INLINE(prefix,name,withname,params,decls,doneResult,...) \
    SHAREMIND_MAP_EXTERN_C_BEGIN \
    prefix name ## _foreach_with_ ## withname(name * s params) { \
        assert(s); \
        decls \
        for (size_t i = 0u; i < 65536u; i++) { \
            struct name ## _item * item = s->d[i]; \
            while (item) { \
                struct name ## _item * const next = item->next; \
                { (void) item; __VA_ARGS__ } \
                item = next; \
            } \
        } \
        return (doneResult); \
    } \
    SHAREMIND_MAP_EXTERN_C_END

#endif /* SHAREMIND_MAP_H */
