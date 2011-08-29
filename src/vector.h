/*
 * This file is a part of the Sharemind framework.
 * Copyright (C) Cybernetica AS
 *
 * All rights are reserved. Reproduction in whole or part is prohibited
 * without the written consent of the copyright owner. The usage of this
 * code is subject to the appropriate license agreement.
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <assert.h>
#include "likely.h"


/**
  \todo Allow for more fine-grained declarations and definitions (e.g. to
        specify linking constraints etc).
*/

#ifdef __cplusplus
#define SM_VECTOR_EXTERN_C_BEGIN extern "C" {
#define SM_VECTOR_EXTERN_C_END   }
#else
#define SM_VECTOR_EXTERN_C_BEGIN
#define SM_VECTOR_EXTERN_C_END
#endif

#define SM_VECTOR_DECLARE(name,datatype,extradata) \
    SM_VECTOR_EXTERN_C_BEGIN \
    struct name { \
        size_t size; \
        datatype * data; \
        extradata \
    }; \
    void name ## _init(struct name * const r) __attribute__ ((nonnull(1))); \
    void name ## _destroy(struct name * const r) __attribute__ ((nonnull(1))); \
    void name ## _destroy_with(struct name * const r, void (*destroyer)(datatype *)) __attribute__ ((nonnull(1, 2))); \
    int name ## _resize(struct name * const r, const size_t newSize) __attribute__ ((nonnull(1))); \
    datatype * name ## _push(struct name * const r) __attribute__ ((nonnull(1))); \
    datatype * name ## _get_pointer(struct name * const r, size_t i) __attribute__ ((nonnull(1), warn_unused_result)); \
    int name ## _foreach(struct name * r, int (*f)(datatype *)) __attribute__ ((nonnull(1, 2))); \
    SM_VECTOR_EXTERN_C_END

#define SM_VECTOR_DECLARE_FOREACH_WITH(name,datatype,withname,types,params) \
    SM_VECTOR_EXTERN_C_BEGIN \
    int name ## _foreach_with_ ## withname (struct name * r, int (*f)(datatype *, types), params) __attribute__ ((nonnull(1, 2))); \
    SM_VECTOR_EXTERN_C_END

#define SM_VECTOR_DEFINE(name,datatype,mymalloc,myfree,myrealloc) \
    SM_VECTOR_EXTERN_C_BEGIN \
    void name ## _init(struct name * const r) { \
        assert(r); \
        r->size = 0u; \
        r->data = NULL; \
    } \
    void name ## _destroy(struct name * const r) { \
        assert(r); \
        myfree(r->data); \
    } \
    void name ## _destroy_with(struct name * const r, void (*destroyer)(datatype *)) { \
        assert(r); \
        assert(destroyer); \
        for (size_t i = 0u; i < r->size; i++) \
            (*destroyer)(&r->data[i]); \
        myfree(r->data); \
    } \
    int name ## _resize(struct name * const r, const size_t newSize) { \
        assert(r); \
        size_t realSize = newSize * sizeof(datatype); \
        if (unlikely(realSize / sizeof(datatype) != newSize)) \
            return 0; \
        if (unlikely(r->size == newSize)) \
            return 1; \
        /** \todo check size_t overflow. */ \
        datatype * const d = myrealloc(r->data, realSize); \
        if (unlikely(!d)) \
            if (unlikely(realSize != 0u)) \
                return 0; \
        r->data = d; \
        r->size = newSize; \
        return 1; \
    } \
    datatype * name ## _push(struct name * const r) { \
        assert(r); \
        size_t oldSize = r->size; \
        size_t newSize = oldSize + 1u; \
        if (unlikely(newSize == 0u)) \
            return NULL; \
        if (unlikely(!name ## _resize(r, newSize))) \
            return NULL; \
        return &r->data[oldSize]; \
    } \
    datatype * name ## _get_pointer(struct name * const r, size_t i) { \
        assert(r); \
        if (unlikely(i >= r->size)) \
            return NULL; \
        return &r->data[i]; \
    } \
    int name ## _foreach(struct name * r, int (*f)(datatype *)) { \
        assert(r); \
        assert(f); \
        for (size_t i = 0u; i < r->size; i++) \
            if (!((*f)(&r->data[i]))) \
                return 0; \
        return 1; \
    } \
    SM_VECTOR_EXTERN_C_END

#define SM_VECTOR_DEFINE_FOREACH_WITH(name,datatype,withname,types,params,args) \
    SM_VECTOR_EXTERN_C_BEGIN \
    int name ## _foreach_with_ ## withname (struct name * r, int (*f)(datatype *, types), params) { \
        assert(r); \
        assert(f); \
        for (size_t i = 0u; i < r->size; i++) \
            if (!((*f)(&r->data[i], args))) \
                return 0; \
        return 1; \
    } \
    SM_VECTOR_EXTERN_C_END

#endif /* VECTOR_H */
