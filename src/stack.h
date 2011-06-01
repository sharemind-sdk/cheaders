#ifndef STACK_H
#define STACK_H

#include "likely.h"


/**
  \todo Allow for more fine-grained declarations and definitions (e.g. to
        specify linking constraints etc).
*/

#define SVM_STACK_DECLARE(name,datatype) \
    struct name ## _item; \
    struct name { \
        struct name ## _item * d; \
    }; \
    struct name * name ## _new (); \
    void name ## _free (struct name * s); \
    datatype * name ## _push (struct name * s); \
    void name ## _pop (struct name * s);

#define SVM_STACK_DEFINE(name,datatype) \
    struct name ## _item { \
        datatype value; \
        struct name ## _item * prev; \
    }; \
    void name ## _init (struct name * s) { \
        s->d = NULL; \
    } \
    struct name * name ## _new () { \
        struct name * s = malloc(sizeof(struct name)); \
        if (likely(s)) \
            s->d = NULL; \
        return s; \
    } \
    void name ## _destroy (struct name * s) { \
        assert(s); \
        struct name ## _item * d = s->d; \
        if (d) { \
            struct name ## _item * prev = d->prev; \
            for (;;) { \
                free(d); \
                if (!prev) \
                    break; \
                d = prev; \
                prev = d->prev; \
            } \
        } \
    } \
    void name ## _destroy_with(struct name * const s, void (*destroyer)(datatype *)) { \
        assert(s); \
        struct name ## _item * d = s->d; \
        if (d) { \
            struct name ## _item * prev = d->prev; \
            for (;;) { \
                (*destroyer)(&d->value); \
                free(d); \
                if (!prev) \
                    break; \
                d = prev; \
                prev = d->prev; \
            } \
        } \
    } \
    void name ## _free (struct name * s) { \
        name ## _destroy (s); \
        free(s); \
    } \
    datatype * name ## _push (struct name * s) { \
        assert(s); \
        struct name ## _item * n = malloc(sizeof(struct name ## _item)); \
        if (unlikely(!n)) \
            return NULL; \
        n->prev = s->d; \
        s->d = n; \
        return &n->value; \
    } \
    void name ## _pop (struct name * s) { \
        assert(s); \
        struct name ## _item * d = s->d; \
        assert(d); \
        s->d = d->prev; \
        free(d); \
    } \
    datatype * name ## _top (struct name * s) { \
        assert(s); \
        struct name ## _item * d = s->d; \
        assert(d); \
        return &d->value; \
    } \
    int name ## _empty (struct name * s) { \
        assert(s); \
        return s->d == NULL; \
    } \
    void name ## _foreach (struct name * s, void (*f)(datatype *)) { \
        assert(s); \
        struct name ## _item * d = s->d; \
        while (d) { \
            (*f)(&d->value); \
            d = d->prev; \
        } \
    }

#endif /* STACK_H */
