#ifndef INSTRSET_H
#define INSTRSET_H

#include "likely.h"


/**
  \todo Allow for more fine-grained declarations and definitions (e.g. to
        specify linking constraints etc).
*/

#ifdef __cplusplus
#define SVM_INSTRSET_EXTERN_C_BEGIN extern "C" {
#define SVM_INSTRSET_EXTERN_C_END   }
#else
#define SVM_INSTRSET_EXTERN_C_BEGIN
#define SVM_INSTRSET_EXTERN_C_END
#endif

#define SVM_INSTRSET_DECLARE(name) \
    SVM_INSTRSET_EXTERN_C_BEGIN \
    struct name ## _item; \
    struct name { \
        struct name ## _item * d[65536]; \
    }; \
    void name ## _init (struct name * s); \
    void name ## _destroy (struct name * s); \
    int name ## _insert (struct name * s, size_t value); \
    int name ## _contains (const struct name * s, size_t value) __attribute__ ((warn_unused_result)); \
    SVM_INSTRSET_EXTERN_C_END

#define SVM_INSTRSET_DEFINE(name,mymalloc,myfree) \
    SVM_INSTRSET_EXTERN_C_BEGIN \
    struct name ## _item { \
        size_t value; \
        struct name ## _item * next; \
    }; \
    void name ## _init (struct name * s) { \
        assert(s); \
        for (size_t i = 0; i < 65536; i++) \
            s->d[i] = NULL; \
    } \
    void name ## _destroy (struct name * s) { \
        assert(s); \
        for (size_t i = 0; i < 65536; i++) { \
            while (s->d[i]) { \
                struct name ## _item * next = s->d[i]->next; \
                myfree(s->d[i]); \
                s->d[i] = next; \
            } \
        } \
    } \
    int name ## _insert (struct name * s, size_t v) { \
        assert(s); \
        uint16_t hash = (uint16_t) v; \
        struct name ## _item ** l = &s->d[hash]; \
        struct name ## _item * p; \
        if (*l) { \
            do { \
                if ((*l)->value > v) \
                    break; \
                if ((*l)->value == v) \
                    return 1; \
                l = &(*l)->next; \
            } while (*l); \
            p = *l; \
        } else { \
            p = NULL; \
        } \
        *l = mymalloc(sizeof(struct name ## _item)); \
        if (!(*l)) { \
            *l = p; \
            return 0; \
        } \
        (*l)->value = v; \
        (*l)->next = p; \
        return 1; \
    } \
    int name ## _contains (const struct name * s, size_t v) { \
        assert(s); \
        uint16_t hash = (uint16_t) v; \
        struct name ## _item * l = s->d[hash]; \
        while (l) { \
            if (l->value == v) \
                return 1; \
            if (l->value > v) \
                return 0; \
            l = l->next; \
        } \
        return 0; \
    } \
    SVM_INSTRSET_EXTERN_C_END

#endif /* INSTRSET_H */
