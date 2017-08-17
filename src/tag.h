/*
 * Copyright (C) 2015 Cybernetica
 *
 * Research/Commercial License Usage
 * Licensees holding a valid Research License or Commercial License
 * for the Software may use this file according to the written
 * agreement between you and Cybernetica.
 *
 * GNU General Public License Usage
 * Alternatively, this file may be used under the terms of the GNU
 * General Public License version 3.0 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.  Please review the following information to
 * ensure the GNU General Public License version 3.0 requirements will be
 * met: http://www.gnu.org/copyleft/gpl-3.0.html.
 *
 * For further information, please contact us at sharemind@cyber.ee.
 */

#ifndef SHAREMIND_LIBMODAPI_TAG_H
#define SHAREMIND_LIBMODAPI_TAG_H

#include "DebugOnly.h"
#include "extern_c.h"
#include "null.h"


typedef void (* SharemindTagDestructor)(void *);

#define SHAREMIND_TAG_DECLARE_FIELDS \
    void * tag; \
    SharemindTagDestructor tagDestructor

#define SHAREMIND_TAG_INIT(c) \
    do { \
        (c)->tag = SHAREMIND_NULL; \
        (c)->tagDestructor = SHAREMIND_NULL; \
    } while ((0))

#define SHAREMIND_TAG_DESTROY(c) \
    do { \
        if ((c)->tagDestructor && (c)->tag) \
            (c)->tagDestructor((c)->tag); \
    } while ((0))

#define SHAREMIND_TAG_FUNCTIONS_DECLARE(ClassName,inlinePerhaps,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps void * ClassName ## _tag(const ClassName * c) \
            __attribute__ ((SHAREMIND_NDEBUG_ONLY(nonnull(1),) __VA_ARGS__)); \
    inlinePerhaps void * ClassName ## _releaseTag(ClassName * c) \
            __attribute__ ((SHAREMIND_NDEBUG_ONLY(nonnull(1),) __VA_ARGS__)); \
    inlinePerhaps void ClassName ## _destroyTag(ClassName * c) \
            __attribute__ ((SHAREMIND_NDEBUG_ONLY(nonnull(1),) __VA_ARGS__)); \
    inlinePerhaps SharemindTagDestructor ClassName ## _tagDestructor( \
            const ClassName * c) \
            __attribute__ ((SHAREMIND_NDEBUG_ONLY(nonnull(1),) __VA_ARGS__)); \
    inlinePerhaps void ClassName ## _setTagWithDestructor( \
            ClassName * c, \
            void * tag, \
            SharemindTagDestructor tagDestructor) \
            __attribute__ ((SHAREMIND_NDEBUG_ONLY(nonnull(1),) __VA_ARGS__)); \
    inlinePerhaps void ClassName ## _setTag(ClassName * c, void * tag) \
            __attribute__ ((SHAREMIND_NDEBUG_ONLY(nonnull(1),) __VA_ARGS__)); \
    inlinePerhaps void ClassName ## _setTagDestructor( \
            ClassName * c, \
            SharemindTagDestructor tagDestructor) \
            __attribute__ ((SHAREMIND_NDEBUG_ONLY(nonnull(1),) __VA_ARGS__)); \
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
        c->tag = SHAREMIND_NULL; \
        ClassName ## _unlock(c); \
        return tag; \
    } \
    inlinePerhaps void ClassName ## _destroyTag(ClassName * c) { \
        assert(c); \
        ClassName ## _lock(c); \
        SHAREMIND_TAG_DESTROY(c); \
        c->tag = SHAREMIND_NULL; \
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

