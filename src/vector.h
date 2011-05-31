#ifndef VECTOR_H
#define VECTOR_H

#include "likely.h"


/**
  \todo Allow for more fine-grained declarations and definitions (e.g. to
        specify linking constraints etc).
*/

#define SVM_VECTOR_DECLARE(name,datatype) \
    struct name { \
        size_t size; \
        datatype * data; \
    }; \
    struct name * name ## _new (); \
    struct name * name ## _new2 (size_t size); \
    void name ## _free(struct name * const r); \
    int name ## _resize(struct name * const r, const size_t newSize);

#define SVM_VECTOR_DEFINE(name,datatype) \
    void name ## _init(struct name * const r) { \
        r->size = 0u; \
        r->data = NULL; \
    } \
    struct name * name ## _name () { \
        struct name * const r = malloc(sizeof(struct name)); \
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
        struct name * const r = malloc(sizeof(struct name)); \
        if (unlikely(!r)) \
            goto name ## _new2_fail_1; \
        if (likely(size > 0u)) { \
            r->data = malloc(realSize); \
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
        free(r); \
    name ## _new2_fail_1: \
        return NULL; \
    } \
    void name ## _destroy(struct name * const r) { \
        assert(r); \
        free(r->data); \
    } \
    void name ## _destroy_with(struct name * const r, void (*destroyer)(datatype *)) { \
        assert(r); \
        for (size_t i = 0u; i < r->size; i++) \
            (*destroyer)(&r->data[i]); \
        free(r->data); \
    } \
    void name ## _free(struct name * const r) { \
        name ## _destroy (r); \
        free(r); \
    } \
    int name ## _resize(struct name * const r, const size_t newSize) { \
        assert(r); \
        size_t realSize = newSize * sizeof(datatype); \
        if (unlikely(realSize / sizeof(datatype) != newSize)) \
            return 0; \
        if (unlikely(r->size == newSize)) \
            return 1; \
        /** \todo check size_t overflow. */ \
        datatype * const d = realloc(r->data, realSize); \
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
    void name ## _foreach(struct name * const r, void (*f)(datatype *)) { \
        for (size_t i = 0u; i < r->size; i++) \
            (*f)(&r->data[i]); \
    }

#endif /* VECTOR_H */
