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
    datatype * name ## _insert(struct name * const t, const char * key) __attribute__ ((nonnull(1, 2))); \
    const datatype * name ## _find(const struct name * const t, const char * key) __attribute__ ((nonnull(1, 2))); \
    SVM_TRIE_EXTERN_C_END

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
            name ## _destroy(t->children[i]); \
            myfree(t->children[i]); \
        } \
    } \
    void name ## _destroy_with(struct name * const t, void (*destroyer)(datatype *)) { \
        assert(t); \
        assert(destroyer); \
        (*destroyer)(&t->data); \
        for (size_t i = 0; i < 255; i++) { \
            name ## _destroy(t->children[i]); \
            myfree(t->children[i]); \
        } \
    } \
    datatype * name ## _insert(struct name * t, const char * key) { \
        assert(t); \
        assert(key); \
        struct name ** next; \
        for (;; (t = *next), key++) { \
            if (*key == '\0') \
                return &t->data; \
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
            if (*key == '\0') \
                return &(*next)->data; \
        } \
    } \
    const datatype * name ## _find(const struct name * t, const char * key) { \
        assert(t); \
        assert(key); \
        for (;; key++) { \
            if (*key == '\0') \
                return &t->data; \
            t = t->children[*((unsigned char *) key)]; \
            if (!t) \
                return NULL; \
        } \
    } \
    SVM_TRIE_EXTERN_C_END

#endif /* TRIE_H */
