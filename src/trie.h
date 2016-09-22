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

#ifndef SHAREMIND_TRIE_H
#define SHAREMIND_TRIE_H

#include <assert.h>
#include "DebugOnly.h"
#include "extern_c.h"
#include "likely.h"


/**
  \todo Allow for more fine-grained declarations and definitions (e.g. to
        specify linking constraints etc).
*/

#ifdef __cplusplus
#define SHAREMIND_TRIE_ALLOC_CAST(type) ((type))
#else
#define SHAREMIND_TRIE_ALLOC_CAST(type)
#endif

#define SHAREMIND_TRIE_DECLARE(name,datatype,inlinePerhaps,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    struct name ## _{ \
        struct name ## _ * children[255]; \
        unsigned char hasData; \
        datatype data; \
    }; \
    typedef struct name ## _ name; \
    inlinePerhaps void name ## _init(name * const t) \
            __attribute__ ((SHAREMIND_NDEBUG_ONLY(nonnull(1)), __VA_ARGS__)); \
    inlinePerhaps void name ## _destroy(name * const t) \
            __attribute__ ((SHAREMIND_NDEBUG_ONLY(nonnull(1)), __VA_ARGS__)); \
    inlinePerhaps void name ## _destroy_with(name * const t, \
                                             void (*destroyer)(datatype *)) \
            __attribute__ ((SHAREMIND_NDEBUG_ONLY(nonnull(1, 2)), \
                            __VA_ARGS__)); \
    inlinePerhaps datatype * name ## _get_or_insert(name * t, \
                                                    const char * key, \
                                                    bool * newValue) \
            __attribute__ ((SHAREMIND_NDEBUG_ONLY(nonnull(1, 2)), \
                            __VA_ARGS__)); \
    inlinePerhaps datatype * name ## _find(name * t, const char * key) \
            __attribute__ ((SHAREMIND_NDEBUG_ONLY(nonnull(1, 2)), \
                            __VA_ARGS__)); \
    inlinePerhaps bool name ## _foreach(name * const t, bool (*f)(datatype *)) \
            __attribute__ ((SHAREMIND_NDEBUG_ONLY(nonnull(1, 2)), \
                            __VA_ARGS__)); \
    SHAREMIND_EXTERN_C_END

#define SHAREMIND_TRIE_DECLARE_FOREACH_WITH(name,datatype,withname,types,params,inlinePerhaps,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps bool name ## _foreach_with_ ## withname ( \
            name * t, \
            bool (*f)(datatype *, types), \
            params) \
            __attribute__ ((SHAREMIND_NDEBUG_ONLY(nonnull(1, 2)), \
                            __VA_ARGS__)); \
    SHAREMIND_EXTERN_C_END

#define SHAREMIND_TRIE_DEFINE(name,datatype,mymalloc,myfree,inlinePerhaps) \
    SHAREMIND_EXTERN_C_BEGIN \
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
    inlinePerhaps datatype * name ## _get_or_insert(name * t, const char * key, bool * newValue) { \
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
            (*next) = SHAREMIND_TRIE_ALLOC_CAST(name *) mymalloc(sizeof(**next)); \
            if (!*next) \
                return NULL; \
            name ## _init(*next); \
            key++; \
            if (*key == '\0') { \
                (*next)->hasData = 1u; \
                if (newValue) \
                    *newValue = true; \
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
    inlinePerhaps bool name ## _foreach(name * const t, bool (*f)(datatype *)) { \
        assert(t); \
        assert(f); \
        if (t->hasData) \
            if (!((*f)(&t->data))) \
                return false; \
        for (size_t i = 0; i < 255; i++) \
            if (t->children[i]) \
                if (!name ## _foreach(t->children[i], f)) \
                    return false; \
        return true; \
    } \
    SHAREMIND_EXTERN_C_END

#define SHAREMIND_TRIE_DEFINE_FOREACH_WITH(name,datatype,withname,types,params,args,inlinePerhaps) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps bool name ## _foreach_with_ ## withname (name * t, bool (*f)(datatype *, types), params) { \
        assert(t); \
        assert(f); \
        if (t->hasData) \
            if (!((*f)(&t->data, args))) \
                return false; \
        for (size_t i = 0; i < 255; i++) \
            if (t->children[i]) \
                if (!name ## _foreach_with_ ## withname(t->children[i], f, args)) \
                    return false; \
        return true; \
    } \
    SHAREMIND_EXTERN_C_END

#endif /* SHAREMIND_TRIE_H */
