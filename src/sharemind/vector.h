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
#include "likely.h"


/**
  \todo Allow for more fine-grained declarations and definitions (e.g. to
        specify linking constraints etc).
*/

#ifdef __cplusplus
#define SHAREMIND_VECTOR_EXTERN_C_BEGIN extern "C" {
#define SHAREMIND_VECTOR_EXTERN_C_END   }
#else
#define SHAREMIND_VECTOR_EXTERN_C_BEGIN
#define SHAREMIND_VECTOR_EXTERN_C_END
#endif

#define SHAREMIND_VECTOR_DECLARE(name,datatype,extradata,inlinePerhaps) \
    SHAREMIND_VECTOR_EXTERN_C_BEGIN \
    typedef struct { \
        size_t size; \
        datatype * data; \
        extradata \
    } name; \
    inlinePerhaps void name ## _init(name * const r) __attribute__ ((nonnull(1))); \
    inlinePerhaps void name ## _destroy(name * const r) __attribute__ ((nonnull(1))); \
    inlinePerhaps void name ## _destroy_with(name * const r, void (*destroyer)(datatype *)) __attribute__ ((nonnull(1, 2))); \
    inlinePerhaps bool name ## _resize(name * const r, const size_t newSize) __attribute__ ((nonnull(1))); \
    inlinePerhaps datatype * name ## _push(name * const r) __attribute__ ((nonnull(1))); \
    inlinePerhaps void name ## _pop(name * const r) __attribute__ ((nonnull(1))); \
    inlinePerhaps datatype * name ## _get_pointer(name * const r, size_t i) __attribute__ ((nonnull(1), warn_unused_result)); \
    inlinePerhaps datatype const * name ## _get_const_pointer(const name * const r, size_t i) __attribute__ ((nonnull(1), warn_unused_result)); \
    inlinePerhaps bool name ## _foreach(name * r, bool (*f)(datatype *)) __attribute__ ((nonnull(1, 2))); \
    inlinePerhaps void name ## _foreach_void(name * r, void (*f)(datatype *)) __attribute__ ((nonnull(1, 2))); \
    SHAREMIND_VECTOR_EXTERN_C_END

#define SHAREMIND_VECTOR_DECLARE_FOREACH_WITH(name,datatype,withname,types,inlinePerhaps) \
    SHAREMIND_VECTOR_EXTERN_C_BEGIN \
    inlinePerhaps bool name ## _foreach_with_ ## withname (name * r, bool (*f)(datatype *, types), types) __attribute__ ((nonnull(1, 2))); \
    SHAREMIND_VECTOR_EXTERN_C_END

#define SHAREMIND_VECTOR_DEFINE(name,datatype,mymalloc,myfree,myrealloc,inlinePerhaps) \
    SHAREMIND_VECTOR_EXTERN_C_BEGIN \
    inlinePerhaps void name ## _init(name * const r) { \
        assert(r); \
        r->size = 0u; \
        r->data = NULL; \
    } \
    inlinePerhaps void name ## _destroy(name * const r) { \
        assert(r); \
        myfree(r->data); \
    } \
    inlinePerhaps void name ## _destroy_with(name * const r, void (*destroyer)(datatype *)) { \
        assert(r); \
        assert(destroyer); \
        for (size_t i = 0u; i < r->size; i++) \
            (*destroyer)(&r->data[i]); \
        myfree(r->data); \
    } \
    inlinePerhaps bool name ## _resize(name * const r, const size_t newSize) { \
        assert(r); \
        if (unlikely(r->size == newSize)) \
            return true; \
        if (unlikely(newSize > SIZE_MAX / sizeof(datatype))) \
            return false; \
        datatype * const d = (datatype *) myrealloc(r->data, newSize * sizeof(datatype)); \
        if (unlikely(!d)) \
            if (unlikely(newSize != 0u)) \
                return false; \
        r->data = d; \
        r->size = newSize; \
        return true; \
    } \
    inlinePerhaps datatype * name ## _push(name * const r) { \
        assert(r); \
        size_t oldSize = r->size; \
        size_t newSize = oldSize + 1u; \
        if (unlikely(newSize == 0u)) \
            return NULL; \
        if (unlikely(!name ## _resize(r, newSize))) \
            return NULL; \
        return &r->data[oldSize]; \
    } \
    inlinePerhaps void name ## _pop(name * const r) { \
        assert(r); \
        assert(r->size > 0u); \
        name ## _resize(r, r->size - 1u); \
    } \
    inlinePerhaps datatype * name ## _get_pointer(name * const r, size_t i) { \
        assert(r); \
        if (unlikely(i >= r->size)) \
            return NULL; \
        return &r->data[i]; \
    } \
    inlinePerhaps datatype const * name ## _get_const_pointer(const name * const r, size_t i) { \
        assert(r); \
        if (unlikely(i >= r->size)) \
            return NULL; \
        return &r->data[i]; \
    } \
    inlinePerhaps bool name ## _foreach(name * r, bool (*f)(datatype *)) { \
        assert(r); \
        assert(f); \
        for (size_t i = 0u; i < r->size; i++) \
            if (!((*f)(&r->data[i]))) \
                return false; \
        return true; \
    } \
    inlinePerhaps void name ## _foreach_void(name * r, void (*f)(datatype *)) { \
        assert(r); \
        assert(f); \
        for (size_t i = 0u; i < r->size; i++) \
            (*f)(&r->data[i]); \
    } \
    SHAREMIND_VECTOR_EXTERN_C_END

#define SHAREMIND_VECTOR_DEFINE_FOREACH_WITH(name,datatype,withname,types,params,args,inlinePerhaps) \
    SHAREMIND_VECTOR_EXTERN_C_BEGIN \
    inlinePerhaps bool name ## _foreach_with_ ## withname (name * r, bool (*f)(datatype *, types), params) { \
        assert(r); \
        assert(f); \
        for (size_t i = 0u; i < r->size; i++) \
            if (!((*f)(&r->data[i], args))) \
                return false; \
        return true; \
    } \
    SHAREMIND_VECTOR_EXTERN_C_END

#endif /* SHAREMIND_VECTOR_H */
