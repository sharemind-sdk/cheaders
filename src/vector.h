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

#ifndef SHAREMIND_VECTOR_H
#define SHAREMIND_VECTOR_H

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "DebugOnly.h"
#include "extern_c.h"
#include "likely.h"
#include "null.h"
#include "wrap.h"


#ifdef __cplusplus
#define SHAREMIND_VECTOR_ALLOC_CAST(type) (type)
#else
#define SHAREMIND_VECTOR_ALLOC_CAST(type)
#endif

#define SHAREMIND_VECTOR_DECLARE_BODY(name,datatype) \
    SHAREMIND_EXTERN_C_BEGIN \
    typedef datatype name ## _value_type; \
    struct name ## _body; \
    typedef struct name ## _body name; \
    SHAREMIND_EXTERN_C_END

#define SHAREMIND_VECTOR_DEFINE_BODY(name,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    struct name ## _body { \
        size_t size; \
        name ## _value_type * data; \
        __VA_ARGS__ \
    }; \
    SHAREMIND_EXTERN_C_END

#define SHAREMIND_VECTOR_FOREACH_(name,r,decls,...) \
    decls \
    for (size_t i_ = 0u; i_ < r->size; i_++) { \
        name ## _value_type * const value = &r->data[i_]; \
        __VA_ARGS__ \
    }

#define SHAREMIND_VECTOR_REVERSE_FOREACH_(name,r,decls,...) \
    decls \
    if (r->size > 0u) { \
        size_t i_ = r->size; \
        do { \
            name ## _value_type * const value = &r->data[--i_]; \
            __VA_ARGS__ \
        } while (i_ > 0u); \
    }

#define SHAREMIND_VECTOR_DECLARE_INIT(name,inlinePerhaps,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps void name ## _init(name * const r) \
            __attribute__ ((SHAREMIND_NDEBUG_ONLY(nonnull(1),) __VA_ARGS__)); \
    SHAREMIND_EXTERN_C_END
#define SHAREMIND_VECTOR_DEFINE_INIT(name,inlinePerhaps) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps void name ## _init(name * const r) { \
        assert(r); \
        r->size = 0u; \
        r->data = SHAREMIND_NULL; \
    } \
    SHAREMIND_EXTERN_C_END

#define SHAREMIND_VECTOR_DECLARE_DESTROY(name,inlinePerhaps,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps void name ## _destroy(name * const r) \
            __attribute__ ((SHAREMIND_NDEBUG_ONLY(nonnull(1),) __VA_ARGS__)); \
    SHAREMIND_EXTERN_C_END
#define SHAREMIND_VECTOR_DEFINE_DESTROY(name,inlinePerhaps,myfree) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps void name ## _destroy(name * const r) { \
        assert(r); \
        myfree(r->data); \
    } \
    SHAREMIND_EXTERN_C_END
#define SHAREMIND_VECTOR_DEFINE_DESTROY_WITH(name,inlinePerhaps,decls,myfree,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps void name ## _destroy(name * r) { \
        assert(r); \
        SHAREMIND_VECTOR_FOREACH_(name, \
                                  r, \
                                  decls, \
                                  SHAREMIND_WRAP(__VA_ARGS__)) \
        myfree(r->data); \
    } \
    SHAREMIND_EXTERN_C_END
#define SHAREMIND_VECTOR_DEFINE_REVERSE_DESTROY_WITH(name,inlinePerhaps,decls,myfree,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps void name ## _destroy(name * r) { \
        assert(r); \
        SHAREMIND_VECTOR_REVERSE_FOREACH_(name, \
                                          r, \
                                          decls, \
                                          SHAREMIND_WRAP(__VA_ARGS__)) \
        myfree(r->data); \
    } \
    SHAREMIND_EXTERN_C_END

#define SHAREMIND_VECTOR_DECLARE_FORCE_RESIZE(name,inlinePerhaps,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps bool name ## _force_resize( \
            name * const r, \
            const size_t newSize) \
            __attribute__ ((SHAREMIND_NDEBUG_ONLY(nonnull(1),) __VA_ARGS__)); \
    SHAREMIND_EXTERN_C_END
#define SHAREMIND_VECTOR_DEFINE_FORCE_RESIZE(name,inlinePerhaps,myrealloc) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps bool name ## _force_resize(name * const r, \
                                             const size_t newSize) \
    { \
        assert(r); \
        name ## _value_type * const d = \
                SHAREMIND_VECTOR_ALLOC_CAST(name ## _value_type *) myrealloc( \
                        r->data, \
                        newSize * sizeof(*d)); \
        if (unlikely(!d && newSize != 0u)) \
            return false; \
        r->data = d; \
        r->size = newSize; \
        return true; \
    } \
    SHAREMIND_EXTERN_C_END

#define SHAREMIND_VECTOR_DECLARE_RESIZE_NO_OCHECK(name,inlinePerhaps,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps bool name ## _resize_no_overflow_check( \
            name * const r, \
            const size_t newSize) \
            __attribute__ ((SHAREMIND_NDEBUG_ONLY(nonnull(1),) __VA_ARGS__)); \
    SHAREMIND_EXTERN_C_END
#define SHAREMIND_VECTOR_DEFINE_RESIZE_NO_OCHECK(name,inlinePerhaps) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps bool name ## _resize_no_overflow_check(name * const r, \
                                                         const size_t newSize) \
    { \
        assert(r); \
        if (unlikely(r->size == newSize)) \
            return true; \
        return name ## _force_resize(r, newSize); \
    } \
    SHAREMIND_EXTERN_C_END

#define SHAREMIND_VECTOR_DECLARE_RESIZE(name,inlinePerhaps,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps bool name ## _resize(name * const r, const size_t newSize) \
            __attribute__ ((SHAREMIND_NDEBUG_ONLY(nonnull(1),) __VA_ARGS__)); \
    SHAREMIND_EXTERN_C_END
#define SHAREMIND_VECTOR_DEFINE_RESIZE(name,inlinePerhaps) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps bool name ## _resize(name * const r, const size_t newSize) { \
        assert(r); \
        if (unlikely(newSize > SIZE_MAX / sizeof(*(r->data)))) \
            return false; \
        return name ## _resize_no_overflow_check(r, newSize); \
    } \
    SHAREMIND_EXTERN_C_END

#define SHAREMIND_VECTOR_DECLARE_PUSH(name,inlinePerhaps,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps name ## _value_type * name ## _push(name * const r) \
            __attribute__ ((SHAREMIND_NDEBUG_ONLY(nonnull(1),) __VA_ARGS__)); \
    SHAREMIND_EXTERN_C_END
#define SHAREMIND_VECTOR_DEFINE_PUSH(name,inlinePerhaps) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps name ## _value_type * name ## _push(name * const r) { \
        assert(r); \
        const size_t oldSize = r->size; \
        if (unlikely(SIZE_MAX - sizeof(name ## _value_type) * oldSize \
                     < sizeof(name ## _value_type))) \
            return SHAREMIND_NULL; \
        if (unlikely(!name ## _force_resize(r, oldSize + 1u))) \
            return SHAREMIND_NULL; \
        return &r->data[oldSize]; \
    } \
    SHAREMIND_EXTERN_C_END

#define SHAREMIND_VECTOR_DECLARE_POP(name,inlinePerhaps,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps void name ## _pop(name * const r) \
            __attribute__ ((SHAREMIND_NDEBUG_ONLY(nonnull(1),) __VA_ARGS__)); \
    SHAREMIND_EXTERN_C_END
#define SHAREMIND_VECTOR_DEFINE_POP(name,inlinePerhaps) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps void name ## _pop(name * const r) { \
        assert(r); \
        assert(r->size > 0u); \
        name ## _force_resize(r, r->size - 1u); \
    } \
    SHAREMIND_EXTERN_C_END

#define SHAREMIND_VECTOR_DECLARE_ERASE(name,inlinePerhaps,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps void name ## _erase(name * const r, size_t const i) \
            __attribute__ ((SHAREMIND_NDEBUG_ONLY(nonnull(1),) __VA_ARGS__)); \
    SHAREMIND_EXTERN_C_END
#define SHAREMIND_VECTOR_DEFINE_ERASE(name,inlinePerhaps) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps void name ## _erase(name * const r, size_t const i) { \
        assert(r); \
        assert(r->size > 0u); \
        assert(i < r->size); \
        memmove(&r->data[i], \
                &r->data[i + 1u], \
                sizeof(*(r->data)) * (r->size - i - 1u)); \
        name ## _force_resize(r, r->size - 1u); \
    } \
    SHAREMIND_EXTERN_C_END

#define SHAREMIND_VECTOR_DECLARE_GET_POINTER_NOCHECK_(name,inlinePerhaps,c,cn,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps name ## _value_type c * \
    name ## _get_ ## cn ## pointer_nocheck( \
            name c * const r, \
            size_t i) \
            __attribute__ ((SHAREMIND_NDEBUG_ONLY(nonnull(1),) __VA_ARGS__)); \
    SHAREMIND_EXTERN_C_END
#define SHAREMIND_VECTOR_DEFINE_GET_POINTER_NOCHECK_(name,inlinePerhaps,c,cn) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps name ## _value_type c * \
    name ## _get_ ## cn ## pointer_nocheck(name c * const r, size_t i) { \
        assert(r); \
        return &r->data[i]; \
    } \
    SHAREMIND_EXTERN_C_END

#define SHAREMIND_VECTOR_DECLARE_GET_POINTER_NOCHECK(name,inlinePerhaps,...) \
    SHAREMIND_VECTOR_DECLARE_GET_POINTER_NOCHECK_( \
            name, \
            SHAREMIND_WRAP(inlinePerhaps),,, \
            SHAREMIND_WRAP(__VA_ARGS__))
#define SHAREMIND_VECTOR_DEFINE_GET_POINTER_NOCHECK(name,inlinePerhaps) \
    SHAREMIND_VECTOR_DEFINE_GET_POINTER_NOCHECK_( \
            name, \
            SHAREMIND_WRAP(inlinePerhaps),,)

#define SHAREMIND_VECTOR_DECLARE_GET_CONST_POINTER_NOCHECK(name,inlinePerhaps,...) \
    SHAREMIND_VECTOR_DECLARE_GET_POINTER_NOCHECK_( \
            name, \
            SHAREMIND_WRAP(inlinePerhaps), \
            const, \
            const_, \
            SHAREMIND_WRAP(__VA_ARGS__))
#define SHAREMIND_VECTOR_DEFINE_GET_CONST_POINTER_NOCHECK(name,inlinePerhaps) \
    SHAREMIND_VECTOR_DEFINE_GET_POINTER_NOCHECK_( \
            name, \
            SHAREMIND_WRAP(inlinePerhaps), \
            const, \
            const_)

#define SHAREMIND_VECTOR_DECLARE_GET_POINTER_(name,inlinePerhaps,c,cn,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps name ## _value_type c * name ## _get_ ## cn ## pointer( \
            name c * const r, \
            size_t i) \
            __attribute__ ((SHAREMIND_NDEBUG_ONLY(nonnull(1),) __VA_ARGS__)); \
    SHAREMIND_EXTERN_C_END
#define SHAREMIND_VECTOR_DEFINE_GET_POINTER_(name,inlinePerhaps,c,cn) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps name ## _value_type c * name ## _get_ ## cn ## pointer( \
            name c * const r, \
            size_t i) \
    { \
        assert(r); \
        if (unlikely(i >= r->size)) \
            return SHAREMIND_NULL; \
        return &r->data[i]; \
    } \
    SHAREMIND_EXTERN_C_END

#define SHAREMIND_VECTOR_DECLARE_GET_POINTER(name,inlinePerhaps,...) \
    SHAREMIND_VECTOR_DECLARE_GET_POINTER_(name, \
                                          SHAREMIND_WRAP(inlinePerhaps),,, \
                                          SHAREMIND_WRAP(__VA_ARGS__))
#define SHAREMIND_VECTOR_DEFINE_GET_POINTER(name,inlinePerhaps) \
    SHAREMIND_VECTOR_DEFINE_GET_POINTER_(name, \
                                         SHAREMIND_WRAP(inlinePerhaps),,)

#define SHAREMIND_VECTOR_DECLARE_GET_CONST_POINTER(name,inlinePerhaps,...) \
    SHAREMIND_VECTOR_DECLARE_GET_POINTER_(name, \
                                          SHAREMIND_WRAP(inlinePerhaps), \
                                          const, \
                                          const_, \
                                          SHAREMIND_WRAP(__VA_ARGS__))
#define SHAREMIND_VECTOR_DEFINE_GET_CONST_POINTER(name,inlinePerhaps) \
    SHAREMIND_VECTOR_DEFINE_GET_POINTER_(name, \
                                         SHAREMIND_WRAP(inlinePerhaps), \
                                         const, \
                                         const_)

#define SHAREMIND_VECTOR_DECLARE_FOREACH(name,withname,prefix,c,params,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    prefix name ## _ ## withname(name c * r params) \
            __attribute__ ((SHAREMIND_NDEBUG_ONLY(nonnull(1),) __VA_ARGS__)); \
    SHAREMIND_EXTERN_C_END
#define SHAREMIND_VECTOR_DEFINE_FOREACH(name,withname,prefix,c,args,decls,ret,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    prefix name ## _ ## withname(name c * r args) { \
        assert(r); \
        SHAREMIND_VECTOR_FOREACH_(name, \
                                  r, \
                                  decls, \
                                  SHAREMIND_WRAP(__VA_ARGS__)) \
        return ret; \
    } \
    SHAREMIND_EXTERN_C_END
#define SHAREMIND_VECTOR_DEFINE_REVERSE_FOREACH(name,withname,prefix,c,args,decls,ret,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    prefix name ## _ ## withname(name c * r args) { \
        assert(r); \
        SHAREMIND_VECTOR_REVERSE_FOREACH_(name, \
                                          r, \
                                          decls, \
                                          SHAREMIND_WRAP(__VA_ARGS__)) \
        return ret; \
    } \
    SHAREMIND_EXTERN_C_END

#endif /* SHAREMIND_VECTOR_H */
