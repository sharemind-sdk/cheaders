/*
 * This file is a part of the Sharemind framework.
 * Copyright (C) Cybernetica AS
 *
 * All rights are reserved. Reproduction in whole or part is prohibited
 * without the written consent of the copyright owner. The usage of this
 * code is subject to the appropriate license agreement.
 */

#ifndef SHAREMIND_VECTOR_H
#define SHAREMIND_VECTOR_H

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "extern_c.h"
#include "likely.h"
#include "wrap.h"


#ifdef __cplusplus
#define SHAREMIND_VECTOR_ALLOC_CAST(type) (type)
#else
#define SHAREMIND_VECTOR_ALLOC_CAST(type)
#endif

#define SHAREMIND_VECTOR_DEFINE_BODY(name,datatype,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    typedef struct { \
        size_t size; \
        datatype * data; \
        __VA_ARGS__ \
    } name; \
    SHAREMIND_EXTERN_C_END

#define SHAREMIND_VECTOR_FOREACH__(r,datatype,decls,...) \
    decls \
    for (size_t i__ = 0u; i__ < r->size; i__++) { \
        datatype * const value = &r->data[i__]; \
        __VA_ARGS__ \
    }

#define SHAREMIND_VECTOR_REVERSE_FOREACH__(r,datatype,decls,...) \
    decls \
    if (r->size > 0u) { \
        size_t i__ = r->size; \
        do { \
            datatype * const value = &r->data[--i__]; \
            __VA_ARGS__ \
        } while (i__ > 0u); \
    }

#define SHAREMIND_VECTOR_DECLARE_INIT(name,inlinePerhaps,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps void name ## _init(name * const r) \
            __attribute__ ((nonnull(1) __VA_ARGS__)); \
    SHAREMIND_EXTERN_C_END
#define SHAREMIND_VECTOR_DEFINE_INIT(name,inlinePerhaps) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps void name ## _init(name * const r) { \
        assert(r); \
        r->size = 0u; \
        r->data = NULL; \
    } \
    SHAREMIND_EXTERN_C_END

#define SHAREMIND_VECTOR_DECLARE_DESTROY(name,inlinePerhaps,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps void name ## _destroy(name * const r) \
            __attribute__ ((nonnull(1) __VA_ARGS__)); \
    SHAREMIND_EXTERN_C_END
#define SHAREMIND_VECTOR_DEFINE_DESTROY(name,inlinePerhaps,myfree) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps void name ## _destroy(name * const r) { \
        assert(r); \
        myfree(r->data); \
    } \
    SHAREMIND_EXTERN_C_END
#define SHAREMIND_VECTOR_DEFINE_DESTROY_WITH(name,inlinePerhaps,datatype,decls,myfree,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps void name ## _destroy(name * r) { \
        assert(r); \
        SHAREMIND_VECTOR_FOREACH__(r, \
                                   datatype, \
                                   decls, \
                                   SHAREMIND_WRAP(__VA_ARGS__)) \
        myfree(r->data); \
    } \
    SHAREMIND_EXTERN_C_END
#define SHAREMIND_VECTOR_DEFINE_REVERSE_DESTROY_WITH(name,inlinePerhaps,datatype,decls,myfree,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps void name ## _destroy(name * r) { \
        assert(r); \
        SHAREMIND_VECTOR_REVERSE_FOREACH__(r, \
                                           datatype, \
                                           decls, \
                                           SHAREMIND_WRAP(__VA_ARGS__)) \
        myfree(r->data); \
    } \
    SHAREMIND_EXTERN_C_END

#define SHAREMIND_VECTOR_DECLARE_FORCE_RESIZE(name,inlinePerhaps,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps bool name ## _force_resize( \
            name * const r, \
            const size_t newSize) __attribute__ ((nonnull(1) __VA_ARGS__)); \
    SHAREMIND_EXTERN_C_END
#define SHAREMIND_VECTOR_DEFINE_FORCE_RESIZE(name,inlinePerhaps,datatype,myrealloc) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps bool name ## _force_resize(name * const r, \
                                             const size_t newSize) \
    { \
        assert(r); \
        datatype * const d = \
                SHAREMIND_VECTOR_ALLOC_CAST(datatype *) myrealloc( \
                        r->data, \
                        newSize * sizeof(*d)); \
        if (unlikely(!d && newSize != 0u)) \
            return false; \
        r->data = d; \
        r->size = newSize; \
        return true; \
    } \
    SHAREMIND_EXTERN_C_END

#define SHAREMIND_VECTOR_DECLARE_RESIZE_NO_OCHECK(name,inlinePerhaps,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps bool name ## _resize_no_overflow_check( \
            name * const r, \
            const size_t newSize) __attribute__ ((nonnull(1) __VA_ARGS__)); \
    SHAREMIND_EXTERN_C_END
#define SHAREMIND_VECTOR_DEFINE_RESIZE_NO_OCHECK(name,inlinePerhaps) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps bool name ## _resize_no_overflow_check(name * const r, \
                                                         const size_t newSize) \
    { \
        assert(r); \
        if (unlikely(r->size == newSize)) \
            return true; \
        return name ## _force_resize(r, newSize); \
    } \
    SHAREMIND_EXTERN_C_END

#define SHAREMIND_VECTOR_DECLARE_RESIZE(name,inlinePerhaps,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps bool name ## _resize(name * const r, const size_t newSize) \
            __attribute__ ((nonnull(1) __VA_ARGS__)); \
    SHAREMIND_EXTERN_C_END
#define SHAREMIND_VECTOR_DEFINE_RESIZE(name,inlinePerhaps) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps bool name ## _resize(name * const r, const size_t newSize) { \
        assert(r); \
        if (unlikely(newSize > SIZE_MAX / sizeof(*(r->data)))) \
            return false; \
        return name ## _resize_no_overflow_check(r, newSize); \
    } \
    SHAREMIND_EXTERN_C_END

#define SHAREMIND_VECTOR_DECLARE_PUSH(name,inlinePerhaps,datatype,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps datatype * name ## _push(name * const r) \
            __attribute__ ((nonnull(1) __VA_ARGS__)); \
    SHAREMIND_EXTERN_C_END
#define SHAREMIND_VECTOR_DEFINE_PUSH(name,inlinePerhaps,datatype) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps datatype * name ## _push(name * const r) { \
        assert(r); \
        const size_t oldSize = r->size; \
        if (unlikely(SIZE_MAX - sizeof(datatype) * oldSize < sizeof(datatype))) \
            return NULL; \
        if (unlikely(!name ## _force_resize(r, oldSize + 1u))) \
            return NULL; \
        return &r->data[oldSize]; \
    } \
    SHAREMIND_EXTERN_C_END

#define SHAREMIND_VECTOR_DECLARE_POP(name,inlinePerhaps,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps void name ## _pop(name * const r) \
            __attribute__ ((nonnull(1) __VA_ARGS__)); \
    SHAREMIND_EXTERN_C_END
#define SHAREMIND_VECTOR_DEFINE_POP(name,inlinePerhaps) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps void name ## _pop(name * const r) { \
        assert(r); \
        assert(r->size > 0u); \
        name ## _force_resize(r, r->size - 1u); \
    } \
    SHAREMIND_EXTERN_C_END

#define SHAREMIND_VECTOR_DECLARE_ERASE(name,inlinePerhaps,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps void name ## _erase(name * const r, size_t const i) \
            __attribute__ ((nonnull(1) __VA_ARGS__)); \
    SHAREMIND_EXTERN_C_END
#define SHAREMIND_VECTOR_DEFINE_ERASE(name,inlinePerhaps) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps void name ## _erase(name * const r, size_t const i) { \
        assert(r); \
        assert(r->size > 0u); \
        assert(i < r->size); \
        memmove(&r->data[i], \
                &r->data[i + 1u], \
                sizeof(*(r->data)) * (r->size - i - 1u)); \
        name ## _force_resize(r, r->size - 1u); \
    } \
    SHAREMIND_EXTERN_C_END

#define SHAREMIND_VECTOR_DECLARE_GET_POINTER_NOCHECK__(name,inlinePerhaps,datatype,c,cn,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps datatype c * name ## _get_ ## cn ## pointer_nocheck( \
            name c * const r, \
            size_t i) __attribute__ ((nonnull(1) __VA_ARGS__)); \
    SHAREMIND_EXTERN_C_END
#define SHAREMIND_VECTOR_DEFINE_GET_POINTER_NOCHECK__(name,inlinePerhaps,datatype,c,cn) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps datatype c * name ## _get_ ## cn ## pointer_nocheck( \
            name c * const r, \
            size_t i) \
    { \
        assert(r); \
        return &r->data[i]; \
    } \
    SHAREMIND_EXTERN_C_END

#define SHAREMIND_VECTOR_DECLARE_GET_POINTER_NOCHECK(name,inlinePerhaps,datatype,...) \
    SHAREMIND_VECTOR_DECLARE_GET_POINTER_NOCHECK__( \
            name, \
            SHAREMIND_WRAP(inlinePerhaps), \
            SHAREMIND_WRAP(datatype),,, \
            SHAREMIND_WRAP(__VA_ARGS__))
#define SHAREMIND_VECTOR_DEFINE_GET_POINTER_NOCHECK(name,inlinePerhaps,datatype) \
    SHAREMIND_VECTOR_DEFINE_GET_POINTER_NOCHECK__( \
            name, \
            SHAREMIND_WRAP(inlinePerhaps), \
            SHAREMIND_WRAP(datatype),,)

#define SHAREMIND_VECTOR_DECLARE_GET_CONST_POINTER_NOCHECK(name,inlinePerhaps,datatype,...) \
    SHAREMIND_VECTOR_DECLARE_GET_POINTER_NOCHECK__( \
            name, \
            SHAREMIND_WRAP(inlinePerhaps), \
            SHAREMIND_WRAP(datatype), \
            const, \
            const_, \
            SHAREMIND_WRAP(__VA_ARGS__))
#define SHAREMIND_VECTOR_DEFINE_GET_CONST_POINTER_NOCHECK(name,inlinePerhaps,datatype) \
    SHAREMIND_VECTOR_DEFINE_GET_POINTER_NOCHECK__( \
            name, \
            SHAREMIND_WRAP(inlinePerhaps), \
            SHAREMIND_WRAP(datatype), \
            const, \
            const_)

#define SHAREMIND_VECTOR_DECLARE_GET_POINTER__(name,inlinePerhaps,datatype,c,cn,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps datatype c * name ## _get_ ## cn ## pointer( \
            name c * const r, \
            size_t i) __attribute__ ((nonnull(1) __VA_ARGS__)); \
    SHAREMIND_EXTERN_C_END
#define SHAREMIND_VECTOR_DEFINE_GET_POINTER__(name,inlinePerhaps,datatype,c,cn) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps datatype c * name ## _get_ ## cn ## pointer( \
            name c * const r, \
            size_t i) \
    { \
        assert(r); \
        if (unlikely(i >= r->size)) \
            return NULL; \
        return &r->data[i]; \
    } \
    SHAREMIND_EXTERN_C_END

#define SHAREMIND_VECTOR_DECLARE_GET_POINTER(name,inlinePerhaps,datatype,...) \
    SHAREMIND_VECTOR_DECLARE_GET_POINTER__(name, \
                                           SHAREMIND_WRAP(inlinePerhaps), \
                                           SHAREMIND_WRAP(datatype),,, \
                                           SHAREMIND_WRAP(__VA_ARGS__))
#define SHAREMIND_VECTOR_DEFINE_GET_POINTER(name,inlinePerhaps,datatype) \
    SHAREMIND_VECTOR_DEFINE_GET_POINTER__(name, \
                                          SHAREMIND_WRAP(inlinePerhaps), \
                                          SHAREMIND_WRAP(datatype),,)

#define SHAREMIND_VECTOR_DECLARE_GET_CONST_POINTER(name,inlinePerhaps,datatype,...) \
    SHAREMIND_VECTOR_DECLARE_GET_POINTER__(name, \
                                           SHAREMIND_WRAP(inlinePerhaps), \
                                           SHAREMIND_WRAP(datatype), \
                                           const, \
                                           const_, \
                                           SHAREMIND_WRAP(__VA_ARGS__))
#define SHAREMIND_VECTOR_DEFINE_GET_CONST_POINTER(name,inlinePerhaps,datatype) \
    SHAREMIND_VECTOR_DEFINE_GET_POINTER__(name, \
                                          SHAREMIND_WRAP(inlinePerhaps), \
                                          SHAREMIND_WRAP(datatype), \
                                          const, \
                                          const_)

#define SHAREMIND_VECTOR_DECLARE_FOREACH(name,withname,prefix,c,params,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    prefix name ## _ ## withname(name c * r params) \
            __attribute__ ((nonnull(1) __VA_ARGS__)); \
    SHAREMIND_EXTERN_C_END
#define SHAREMIND_VECTOR_DEFINE_FOREACH(name,withname,prefix,c,datatype,args,decls,ret,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    prefix name ## _ ## withname(name c * r args) { \
        assert(r); \
        SHAREMIND_VECTOR_FOREACH__(r, \
                                   datatype, \
                                   decls, \
                                   SHAREMIND_WRAP(__VA_ARGS__)) \
        return ret; \
    } \
    SHAREMIND_EXTERN_C_END
#define SHAREMIND_VECTOR_DEFINE_REVERSE_FOREACH(name,withname,prefix,c,datatype,args,decls,ret,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    prefix name ## _ ## withname(name c * r args) { \
        assert(r); \
        SHAREMIND_VECTOR_REVERSE_FOREACH__(r, \
                                           datatype, \
                                           decls, \
                                           SHAREMIND_WRAP(__VA_ARGS__)) \
        return ret; \
    } \
    SHAREMIND_EXTERN_C_END

#endif /* SHAREMIND_VECTOR_H */
