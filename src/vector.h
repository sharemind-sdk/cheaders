#ifndef VECTOR_H
#define VECTOR_H

#include "likely.h"


/**
  \todo Allow for more fine-grained declarations and definitions (e.g. to
        specify linking constraints etc).
*/

#ifdef __cplusplus
#define SVM_VECTOR_EXTERN_C_BEGIN extern "C" {
#define SVM_VECTOR_EXTERN_C_END   }
#else
#define SVM_VECTOR_EXTERN_C_BEGIN
#define SVM_VECTOR_EXTERN_C_END
#endif

#define SVM_VECTOR_DECLARE(name,datatype,extradata) \
    SVM_VECTOR_EXTERN_C_BEGIN \
    struct name { \
        size_t size; \
        datatype * data; \
        extradata \
    }; \
    void name ## _init(struct name * const r); \
    void name ## _destroy(struct name * const r); \
    void name ## _destroy_with(struct name * const r, void (*destroyer)(datatype *)); \
    int name ## _resize(struct name * const r, const size_t newSize); \
    datatype * name ## _push(struct name * const r); \
    datatype * name ## _get_pointer(struct name * const r, size_t i) __attribute__ ((warn_unused_result)); \
    void name ## _foreach(struct name * const r, void (*f)(datatype *)); \
    SVM_VECTOR_EXTERN_C_END

#define SVM_VECTOR_DEFINE(name,datatype,mymalloc,myfree,myrealloc) \
    SVM_VECTOR_EXTERN_C_BEGIN \
    void name ## _init(struct name * const r) { \
        r->size = 0u; \
        r->data = NULL; \
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
    } \
    SVM_VECTOR_EXTERN_C_END

#endif /* VECTOR_H */
