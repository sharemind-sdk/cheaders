#ifndef VECTOR_H
#define VECTOR_H

#include "likely.h"


/**
  \todo Allow for more fine-grained declarations and definitions (e.g. to
        specify linking constraints etc).
*/

#define SVM_VECTOR_DECLARE(name,datatype,extradata) \
    struct name { \
        size_t size; \
        datatype * data; \
        extradata \
    }; \
    void name ## _init(struct name * const r); \
    struct name * name ## _new () __attribute__ ((warn_unused_result)); \
    struct name * name ## _new2 (size_t size) __attribute__ ((warn_unused_result)); \
    void name ## _destroy(struct name * const r); \
    void name ## _destroy_with(struct name * const r, void (*destroyer)(datatype *)); \
    void name ## _free(struct name * const r); \
    int name ## _resize(struct name * const r, const size_t newSize); \
    datatype * name ## _push(struct name * const r); \
    datatype * name ## _get_pointer(struct name * const r, size_t i) __attribute__ ((warn_unused_result)); \
    void name ## _foreach(struct name * const r, void (*f)(datatype *));

#define SVM_VECTOR_DEFINE(name,datatype,mymalloc,myfree,myrealloc) \
    void name ## _init(struct name * const r) { \
        r->size = 0u; \
        r->data = NULL; \
    } \
    struct name * name ## _new () { \
        struct name * const r = mymalloc(sizeof(struct name)); \
        if (likely(r)) { \
            r->size = 0u; \
            r->data = NULL; \
        } \
        return r; \
    } \
    struct name * name ## _new2(size_t size) { \
        size_t realSize = size * sizeof(datatype); \
        if (unlikely(realSize / sizeof(datatype) != size)) \
            return NULL; \
        struct name * const r = mymalloc(sizeof(struct name)); \
        if (unlikely(!r)) \
            goto name ## _new2_fail_1; \
        if (likely(size > 0u)) { \
            r->data = mymalloc(realSize); \
            if (unlikely(!r->data)) \
                goto name ## _new2_fail_2; \
            r->size = size; \
        } else { \
            r->data = NULL; \
            r->size = 0u; \
        } \
    /* SUCCESS: */ \
        return r; \
    name ## _new2_fail_2: \
        myfree(r); \
    name ## _new2_fail_1: \
        return NULL; \
    } \
    void name ## _destroy(struct name * const r) { \
        assert(r); \
        myfree(r->data); \
    } \
    void name ## _destroy_with(struct name * const r, void (*destroyer)(datatype *)) { \
        assert(r); \
        for (size_t i = 0u; i < r->size; i++) \
            (*destroyer)(&r->data[i]); \
        myfree(r->data); \
    } \
    void name ## _free(struct name * const r) { \
        name ## _destroy (r); \
        myfree(r); \
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
            return 0; \
        r->data = d; \
        r->size = newSize; \
        return 1; \
    } \
    datatype * name ## _push(struct name * const r) { \
        assert(r); \
        if (unlikely(!name ## _resize(r, r->size + 1))) \
            return NULL; \
        return &r->data[r->size - 1]; \
    } \
    datatype * name ## _get_pointer(struct name * const r, size_t i) { \
        assert(r); \
        if (unlikely(i >= r->size)) \
            return NULL; \
        return &r->data[i]; \
    } \
    void name ## _foreach(struct name * const r, void (*f)(datatype *)) { \
        for (size_t i = 0u; i < r->size; i++) \
            (*f)(&r->data[i]); \
    }

#endif /* VECTOR_H */
