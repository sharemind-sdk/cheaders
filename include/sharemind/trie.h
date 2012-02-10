/*
 * This file is a part of the Sharemind framework.
 * Copyright (C) Cybernetica AS
 *
 * All rights are reserved. Reproduction in whole or part is prohibited
 * without the written consent of the copyright owner. The usage of this
 * code is subject to the appropriate license agreement.
 */

#ifndef SHAREMIND_TRIE_H
#define SHAREMIND_TRIE_H

#include <assert.h>
#include "likely.h"


/**
  \todo Allow for more fine-grained declarations and definitions (e.g. to
        specify linking constraints etc).
*/

#ifdef __cplusplus
#define SHAREMIND_TRIE_EXTERN_C_BEGIN extern "C" {
#define SHAREMIND_TRIE_EXTERN_C_END   }
#else
#define SHAREMIND_TRIE_EXTERN_C_BEGIN
#define SHAREMIND_TRIE_EXTERN_C_END
#endif

#define SHAREMIND_TRIE_DECLARE(name,datatype,inlinePerhaps) \
    SHAREMIND_TRIE_EXTERN_C_BEGIN \
    struct _ ## name { \
        struct _ ## name * children[255]; \
        unsigned char hasData; \
        datatype data; \
    }; \
    typedef struct _ ## name name; \
    inlinePerhaps void name ## _init(name * const t) __attribute__ ((nonnull(1))); \
    inlinePerhaps void name ## _destroy(name * const t) __attribute__ ((nonnull(1))); \
    inlinePerhaps void name ## _destroy_with(name * const t, void (*destroyer)(datatype *)) __attribute__ ((nonnull(1, 2))); \
    inlinePerhaps datatype * name ## _get_or_insert(name * t, const char * key, int * newValue) __attribute__ ((nonnull(1, 2))); \
    inlinePerhaps datatype * name ## _find(name * t, const char * key) __attribute__ ((nonnull(1, 2))); \
    inlinePerhaps int name ## _foreach(name * const t, int (*f)(datatype *)) __attribute__ ((nonnull(1, 2))); \
    SHAREMIND_TRIE_EXTERN_C_END

#define SHAREMIND_TRIE_DECLARE_FOREACH_WITH(name,datatype,withname,types,params,inlinePerhaps) \
    SHAREMIND_VECTOR_EXTERN_C_BEGIN \
    inlinePerhaps int name ## _foreach_with_ ## withname (name * t, int (*f)(datatype *, types), params) __attribute__ ((nonnull(1, 2))); \
    SHAREMIND_VECTOR_EXTERN_C_END

#define SHAREMIND_TRIE_DEFINE(name,datatype,mymalloc,myfree,inlinePerhaps) \
    SHAREMIND_TRIE_EXTERN_C_BEGIN \
    inlinePerhaps void name ## _init(name * const t) { \
        assert(t); \
        for (size_t i = 0u; i < 255u; i++) \
            t->children[i] = NULL; \
        t->hasData = 0u; \
    } \
    inlinePerhaps void name ## _destroy(name * const t) { \
        assert(t); \
        for (size_t i = 0; i < 255; i++) { \
            if (t->children[i]) { \
                name ## _destroy(t->children[i]); \
                myfree(t->children[i]); \
            } \
        } \
    } \
    inlinePerhaps void name ## _destroy_with(name * const t, void (*destroyer)(datatype *)) { \
        assert(t); \
        assert(destroyer); \
        if (t->hasData) \
            (*destroyer)(&t->data); \
        for (size_t i = 0; i < 255; i++) { \
            if (t->children[i]) { \
                name ## _destroy_with(t->children[i], destroyer); \
                myfree(t->children[i]); \
            } \
        } \
    } \
    inlinePerhaps datatype * name ## _get_or_insert(name * t, const char * key, int * newValue) { \
        assert(t); \
        assert(key); \
        name ** next; \
        for (;; (t = *next), key++) { \
            if (*key == '\0') { \
                if (newValue) \
                    *newValue = (t->hasData == 0u); \
                t->hasData = 1u; \
                return &t->data; \
            } \
            next = &t->children[*((const unsigned char *) key)]; \
            if (!*next) \
                break; \
        } \
        for (;; next = &(*next)->children[*((const unsigned char *) key)]) { \
            (*next) = (name *) mymalloc(sizeof(name)); \
            if (!*next) \
                return NULL; \
            name ## _init(*next); \
            key++; \
            if (*key == '\0') { \
                (*next)->hasData = 1u; \
                if (newValue) \
                    *newValue = 1; \
                return &(*next)->data; \
            } \
        } \
    } \
    inlinePerhaps datatype * name ## _find(name * t, const char * key) { \
        assert(t); \
        assert(key); \
        for (;; key++) { \
            if (*key == '\0') \
                return t->hasData ? &t->data : NULL; \
            t = t->children[*((const unsigned char *) key)]; \
            if (!t) \
                return NULL; \
        } \
    } \
    inlinePerhaps int name ## _foreach(name * const t, int (*f)(datatype *)) { \
        assert(t); \
        assert(f); \
        if (t->hasData) \
            if (!((*f)(&t->data))) \
                return 0; \
        for (size_t i = 0; i < 255; i++) \
            if (t->children[i]) \
                if (!name ## _foreach(t->children[i], f)) \
                    return 0; \
        return 1; \
    } \
    SHAREMIND_TRIE_EXTERN_C_END

#define SHAREMIND_TRIE_DEFINE_FOREACH_WITH(name,datatype,withname,types,params,args,inlinePerhaps) \
    SHAREMIND_TRIE_EXTERN_C_BEGIN \
    inlinePerhaps int name ## _foreach_with_ ## withname (name * t, int (*f)(datatype *, types), params) { \
        assert(t); \
        assert(f); \
        if (t->hasData) \
            if (!((*f)(&t->data, args))) \
                return 0; \
        for (size_t i = 0; i < 255; i++) \
            if (t->children[i]) \
                if (!name ## _foreach_with_ ## withname(t->children[i], f, args)) \
                    return 0; \
        return 1; \
    } \
    SHAREMIND_TRIE_EXTERN_C_END

#endif /* SHAREMIND_TRIE_H */
