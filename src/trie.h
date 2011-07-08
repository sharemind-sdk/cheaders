/*
 * This file is a part of the Sharemind framework.
 * Copyright (C) Cybernetica AS
 *
 * All rights are reserved. Reproduction in whole or part is prohibited
 * without the written consent of the copyright owner. The usage of this
 * code is subject to the appropriate license agreement.
 */

#ifndef TRIE_H
#define TRIE_H

#include <assert.h>
#include "likely.h"


/**
  \todo Allow for more fine-grained declarations and definitions (e.g. to
        specify linking constraints etc).
*/

#ifdef __cplusplus
#define SVM_TRIE_EXTERN_C_BEGIN extern "C" {
#define SVM_TRIE_EXTERN_C_END   }
#else
#define SVM_TRIE_EXTERN_C_BEGIN
#define SVM_TRIE_EXTERN_C_END
#endif

#define SVM_TRIE_DECLARE(name,datatype) \
    SVM_TRIE_EXTERN_C_BEGIN \
    struct name { \
        struct name * children[255]; \
        unsigned char hasData; \
        datatype data; \
    }; \
    void name ## _init(struct name * const t) __attribute__ ((nonnull(1))); \
    void name ## _destroy(struct name * const t) __attribute__ ((nonnull(1))); \
    void name ## _destroy_with(struct name * const t, void (*destroyer)(datatype *)) __attribute__ ((nonnull(1, 2))); \
    datatype * name ## _get_or_insert(struct name * t, const char * key, int * newValue) __attribute__ ((nonnull(1, 2))); \
    datatype * name ## _find(struct name * t, const char * key) __attribute__ ((nonnull(1, 2))); \
    int name ## _foreach(struct name * const t, int (*f)(datatype *)) __attribute__ ((nonnull(1, 2))); \
    SVM_TRIE_EXTERN_C_END

#define SVM_TRIE_DECLARE_FOREACH_WITH(name,datatype,withname,types,params) \
    SVM_VECTOR_EXTERN_C_BEGIN \
    int name ## _foreach_with_ ## withname (struct name * t, int (*f)(datatype *, types), params) __attribute__ ((nonnull(1, 2))); \
    SVM_VECTOR_EXTERN_C_END

#define SVM_TRIE_DEFINE(name,datatype,mymalloc,myfree) \
    SVM_TRIE_EXTERN_C_BEGIN \
    void name ## _init(struct name * const t) { \
        assert(t); \
        for (size_t i = 0u; i < 255u; i++) \
            t->children[i] = NULL; \
        t->hasData = 0u; \
    } \
    void name ## _destroy(struct name * const t) { \
        assert(t); \
        for (size_t i = 0; i < 255; i++) { \
            if (t->children[i]) { \
                name ## _destroy(t->children[i]); \
                myfree(t->children[i]); \
            } \
        } \
    } \
    void name ## _destroy_with(struct name * const t, void (*destroyer)(datatype *)) { \
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
    datatype * name ## _get_or_insert(struct name * t, const char * key, int * newValue) { \
        assert(t); \
        assert(key); \
        struct name ** next; \
        for (;; (t = *next), key++) { \
            if (*key == '\0') { \
                if (newValue) \
                    *newValue = (t->hasData == 0u); \
                t->hasData = 1u; \
                return &t->data; \
            } \
            next = &t->children[*((unsigned char *) key)]; \
            if (!*next) \
                break; \
        } \
        for (;; next = &(*next)->children[*((unsigned char *) key)]) { \
            (*next) = mymalloc(sizeof(struct name)); \
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
    datatype * name ## _find(struct name * t, const char * key) { \
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
    int name ## _foreach(struct name * const t, int (*f)(datatype *)) { \
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
    SVM_TRIE_EXTERN_C_END

#define SVM_TRIE_DEFINE_FOREACH_WITH(name,datatype,withname,types,params,args) \
    SVM_TRIE_EXTERN_C_BEGIN \
    int name ## _foreach_with_ ## withname (struct name * t, int (*f)(datatype *, types), params) { \
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
    SVM_TRIE_EXTERN_C_END

#endif /* TRIE_H */
