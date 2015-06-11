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

#ifndef SHAREMIND_LASTERROR_H
#define SHAREMIND_LASTERROR_H

#include <assert.h>
#include "extern_c.h"
#include "likely.h"
#include "wrap.h"


#define SHAREMIND_LASTERROR_DECLARE_FIELDS(codeType) \
    codeType lastError; \
    const char * lastErrorStaticString

#define SHAREMIND_LASTERROR_INIT(className,okCode) \
    do { \
        (className)->lastError = (okCode); \
        (className)->lastErrorStaticString = NULL; \
    } while((0))

#define SHAREMIND_LASTERROR_PUBLIC_FUNCTIONS_DECLARE(ClassName,inlinePerhaps,codeType,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps codeType ClassName ## _lastError(const ClassName * c) \
            __attribute__ ((nonnull(1) __VA_ARGS__)); \
    inlinePerhaps const char * ClassName ## _lastErrorString( \
            const ClassName * c) __attribute__ ((nonnull(1) __VA_ARGS__)); \
    inlinePerhaps void ClassName ## _clearError(ClassName * c) \
            __attribute__ ((nonnull(1) __VA_ARGS__)); \
    SHAREMIND_EXTERN_C_END

#define SHAREMIND_LASTERROR_PUBLIC_FUNCTIONS_DEFINE(ClassName,inlinePerhaps,codeType,okCode) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps codeType ClassName ## _lastError(const ClassName * c) { \
        assert(c); \
        ClassName ## _lockConst(c); \
        const codeType r = c->lastError; \
        ClassName ## _unlockConst(c); \
        return r; \
    } \
    inlinePerhaps const char * ClassName ## _lastErrorString( \
            const ClassName * c) \
    { \
        assert(c); \
        const char * r; \
        ClassName ## _lockConst(c); \
        if (unlikely(c->lastError == (okCode))) { \
            r = NULL; \
        } else { \
            assert(c->lastErrorStaticString); \
            r = c->lastErrorStaticString; \
        } \
        ClassName ## _unlockConst(c); \
        return r; \
    } \
    inlinePerhaps void ClassName ## _clearError(ClassName * c) { \
        assert(c); \
        ClassName ## _lock(c); \
        c->lastError = (okCode); \
        ClassName ## _unlock(c); \
    } \
    SHAREMIND_EXTERN_C_END

#define SHAREMIND_LASTERROR_PUBLIC_FUNCTIONS_DECLARE_DEFINE(ClassName,inlinePerhaps,codeType,okCode,...) \
    SHAREMIND_LASTERROR_PUBLIC_FUNCTIONS_DECLARE(ClassName, \
                                                 inlinePerhaps, \
                                                 codeType, \
                                                 SHAREMIND_WRAP(__VA_ARGS__)) \
    SHAREMIND_LASTERROR_PUBLIC_FUNCTIONS_DEFINE(ClassName, \
                                                inlinePerhaps, \
                                                codeType, \
                                                okCode)

#define SHAREMIND_LASTERROR_PRIVATE_FUNCTIONS_DECLARE(ClassName,inlinePerhaps,codeType,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps void ClassName ## _setError( \
            ClassName * c, \
            codeType error, \
            const char * errorString) \
            __attribute__ ((nonnull(1) __VA_ARGS__)); \
    SHAREMIND_EXTERN_C_END

#define SHAREMIND_LASTERROR_PRIVATE_FUNCTIONS_DEFINE(ClassName,inlinePerhaps,codeType,okCode) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps void ClassName ## _setError(ClassName * c, \
                                              codeType error, \
                                              const char * errorString) \
    { \
        assert(c); \
        assert(error != (okCode)); \
        if (unlikely(!errorString || !errorString[0])) \
            errorString = codeType ## _toString(error); \
        assert(errorString); \
        assert(errorString[0]); \
        ClassName ## _lock(c); \
        c->lastError = error; \
        c->lastErrorStaticString = errorString; \
        ClassName ## _unlock(c); \
    } \
    SHAREMIND_EXTERN_C_END

#define SHAREMIND_LASTERROR_PRIVATE_FUNCTIONS_DECLARE_DEFINE(ClassName,inlinePerhaps,codeType,okCode,...) \
    SHAREMIND_LASTERROR_PRIVATE_FUNCTIONS_DECLARE(ClassName, \
                                                  inlinePerhaps, \
                                                  codeType, \
                                                  SHAREMIND_WRAP(__VA_ARGS__)) \
    SHAREMIND_LASTERROR_PRIVATE_FUNCTIONS_DEFINE(ClassName, \
                                                 inlinePerhaps, \
                                                 codeType, \
                                                 okCode)

#define SHAREMIND_LASTERROR_PRIVATE_SHORTCUT_DECLARE(ClassName,Name,inlinePerhaps,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps void ClassName ## _setError ## Name(ClassName * c) \
            __attribute__ ((nonnull(1) __VA_ARGS__)); \
    SHAREMIND_EXTERN_C_END

#define SHAREMIND_LASTERROR_PRIVATE_SHORTCUT_DEFINE(ClassName,Name,inlinePerhaps,code,msg) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps void ClassName ## _setError ## Name(ClassName * c) \
    { ClassName ## _setError(c, (code), (msg)); } \
    SHAREMIND_EXTERN_C_END

#define SHAREMIND_LASTERROR_PRIVATE_SHORTCUT_DECLARE_DEFINE(ClassName,Name,inlinePerhaps,code,msg,...) \
    SHAREMIND_LASTERROR_PRIVATE_SHORTCUT_DECLARE(ClassName, \
                                                 Name, \
                                                 inlinePerhaps, \
                                                 SHAREMIND_WRAP(__VA_ARGS__)) \
    SHAREMIND_LASTERROR_PRIVATE_SHORTCUT_DEFINE(ClassName, \
                                                Name, \
                                                inlinePerhaps, \
                                                code, \
                                                msg) \

#endif /* SHAREMIND_LASTERROR_H */
