#ifndef VECTOR_H
#define VECTOR_H

/**
  \todo Allow for more fine-grained declarations and definitions (e.g. to
        specify linking constraints etc).
*/

#define SVM_VECTOR_DECLARE(name,datatype,sizetype) \
    struct name { \
        sizetype size; \
        datatype * data; \
    }; \
    struct name * name ## _new (); \
    struct name * name ## _new2 (sizetype size); \
    void name ## _free(struct name * const r); \
    int name ## _resize(struct name * const r, const sizetype newSize);

#define SVM_VECTOR_DEFINE(name,datatype,sizetype) \
    void name ## _init(struct name * const r) { \
        r->size = 0; \
        r->data = NULL; \
    } \
    struct name * name ## _name () { \
        struct name * const r = malloc(sizeof(struct name)); \
        if (r) { \
            r->size = 0; \
            r->data = NULL; \
        } \
        return r; \
    } \
    struct name * name ## _new2(sizetype size) { \
        struct name * const r = malloc(sizeof(struct name)); \
        if (!r) \
            goto name ## _new2_fail_1; \
        if (size > 0) { \
            r->data = calloc(size, sizeof(datatype)); \
            if (!r->data) \
                goto name ## _new2_fail_2; \
            r->size = size; \
        } else { \
            r->data = NULL; \
            r->size = 0; \
        } \
    /* SUCCESS: */ \
        return r; \
    name ## _new2_fail_2: \
        free(r); \
    name ## _new2_fail_1: \
        return 0; \
    } \
    void name ## _free(struct name * const r) { \
        assert(r); \
        free(r->data); \
        free(r); \
    } \
    int name ## _resize(struct name * const r, const sizetype newSize) { \
        assert(r); \
        if (r->size == newSize) \
            return 1; \
        /** \todo check size_t overflow. */ \
        datatype * const d = realloc(r->data, sizeof(datatype) * newSize); \
        if (!d) \
            return 0; \
        r->data = d; \
        r->size = newSize; \
        return 1; \
    }

#endif /* VECTOR_H */
