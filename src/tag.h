/*
 * This file is a part of the Sharemind framework.
 * Copyright (C) Cybernetica AS
 *
 * All rights are reserved. Reproduction in whole or part is prohibited
 * without the written consent of the copyright owner. The usage of this
 * code is subject to the appropriate license agreement.
 */

#ifndef SHAREMIND_LIBMODAPI_TAG_H
#define SHAREMIND_LIBMODAPI_TAG_H

#include "extern_c.h"


typedef void (* SharemindTagDestructor)(void *);

#define SHAREMIND_TAG_DECLARE_FIELDS \
    void * tag; \
    SharemindTagDestructor tagDestructor

#define SHAREMIND_TAG_INIT(c) \
    do { \
        (c)->tag = NULL; \
        (c)->tagDestructor = NULL; \
    } while(0)

#define SHAREMIND_TAG_DESTROY(c) \
    if ((c)->tagDestructor && (c)->tag) { \
        (c)->tagDestructor((c)->tag); \
    } else (void) 0

#define SHAREMIND_TAG_FUNCTIONS_DECLARE(ClassName,inlinePerhaps,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps void * ClassName ## _tag(const ClassName * c) \
            __attribute__ ((nonnull(1) __VA_ARGS__)); \
    inlinePerhaps void * ClassName ## _releaseTag(ClassName * c) \
            __attribute__ ((nonnull(1) __VA_ARGS__)); \
    inlinePerhaps void ClassName ## _destroyTag(ClassName * c) \
            __attribute__ ((nonnull(1) __VA_ARGS__)); \
    inlinePerhaps SharemindTagDestructor ClassName ## _tagDestructor( \
            const ClassName * c) \
            __attribute__ ((nonnull(1) __VA_ARGS__)); \
    inlinePerhaps void ClassName ## _setTagWithDestructor( \
            ClassName * c, \
            void * tag, \
            SharemindTagDestructor tagDestructor) \
            __attribute__ ((nonnull(1) __VA_ARGS__)); \
    inlinePerhaps void ClassName ## _setTag(ClassName * c, void * tag) \
            __attribute__ ((nonnull(1) __VA_ARGS__)); \
    inlinePerhaps void ClassName ## _setTagDestructor( \
            ClassName * c, \
            SharemindTagDestructor tagDestructor) \
            __attribute__ ((nonnull(1) __VA_ARGS__)); \
    SHAREMIND_EXTERN_C_END

#define SHAREMIND_TAG_FUNCTIONS_DEFINE(ClassName,inlinePerhaps) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps void * ClassName ## _tag(const ClassName * c) { \
        assert(c); \
        ClassName ## _lockConst(c); \
        void * const tag = c->tag; \
        ClassName ## _unlockConst(c); \
        return tag; \
    } \
    inlinePerhaps void * ClassName ## _releaseTag(ClassName * c) { \
        assert(c); \
        ClassName ## _lock(c); \
        void * const tag = c->tag; \
        c->tag = NULL; \
        ClassName ## _unlock(c); \
        return tag; \
    } \
    inlinePerhaps void ClassName ## _destroyTag(ClassName * c) { \
        assert(c); \
        ClassName ## _lock(c); \
        SHAREMIND_TAG_DESTROY(c); \
        c->tag = NULL; \
        ClassName ## _unlock(c); \
    } \
    inlinePerhaps SharemindTagDestructor ClassName ## _tagDestructor( \
            const ClassName * c) \
    { \
        assert(c); \
        ClassName ## _lockConst(c); \
        SharemindTagDestructor const tagDestructor = c->tagDestructor; \
        ClassName ## _unlockConst(c); \
        return tagDestructor; \
    } \
    inlinePerhaps void ClassName ## _setTagWithDestructor( \
            ClassName * c, \
            void * tag, \
            SharemindTagDestructor tagDestructor) \
    { \
        assert(c); \
        ClassName ## _lock(c); \
        c->tag = tag; \
        c->tagDestructor = tagDestructor; \
        ClassName ## _unlock(c); \
    } \
    inlinePerhaps void ClassName ## _setTag(ClassName * c, void * tag) { \
        assert(c); \
        ClassName ## _lock(c); \
        c->tag = tag; \
        ClassName ## _unlock(c); \
    } \
    inlinePerhaps void ClassName ## _setTagDestructor( \
            ClassName * c, \
            SharemindTagDestructor tagDestructor) \
    { \
        assert(c); \
        ClassName ## _lock(c); \
        c->tagDestructor = tagDestructor; \
        ClassName ## _unlock(c); \
    } \
    SHAREMIND_EXTERN_C_END

#endif /* SHAREMIND_LIBMODAPI_TAG_H */

