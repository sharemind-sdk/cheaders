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

#ifndef SHAREMIND_MAP_H
#define SHAREMIND_MAP_H

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "apocalyptic_safety.h"
#include "DebugOnly.h"
#include "extern_c.h"
#include "likely.h"


/**
  \todo Allow for more fine-grained declarations and definitions (e.g. to
        specify linking constraints etc).
*/

#ifdef __cplusplus
#define SHAREMIND_MAP_ALLOC_CAST(type) ((type))
#else
#define SHAREMIND_MAP_ALLOC_CAST(type)
#endif

#define SHAREMIND_MAP_KEY_INIT_DECLARE(name,keytype) \
    inline bool name(keytype * const dest)
#define SHAREMIND_MAP_KEY_INIT_DEFINE(name,keytype) \
    inline bool name(keytype * const dest) { return ((void) dest, true); }

#define SHAREMIND_MAP_KEY_FREE_DECLARE(name,keytype) \
    inline void name(keytype * const dest)
#define SHAREMIND_MAP_KEY_FREE_DEFINE(name,keytype) \
    inline void name(keytype * const dest) { (void) dest; }

#define SHAREMIND_MAP_KEY_FREE_REGULAR(unused)

#define SHAREMIND_MAP_KEY_COPY_DECLARE(name,keytype) \
    inline bool name(keytype * const dest, keytype const src)
#define SHAREMIND_MAP_KEY_COPY_DEFINE(name,keytype) \
    inline bool name(keytype * const dest, keytype const src) \
    { return (((*dest) = src), true); }

#define SHAREMIND_MAP_KEY_EQUALS_DECLARE(name,keytype) \
    inline bool name(keytype const k1, keytype const k2)
#define SHAREMIND_MAP_KEY_EQUALS_DEFINE(name,keytype) \
    inline bool name(keytype const k1, keytype const k2) { return k1 == k2; }

#define SHAREMIND_MAP_KEY_LESS_DECLARE(name,keytype) \
    inline bool name(keytype const k1, keytype const k2)
#define SHAREMIND_MAP_KEY_LESS_DEFINE(name,keytype) \
    inline bool name(keytype const k1, keytype const k2) { return k1 < k2; }

#define SHAREMIND_MAP_KEYOPS_DECLARE_DEFINE_(keytype_str,keytype) \
    SHAREMIND_MAP_KEY_INIT_DECLARE(SHAREMIND_MAP_KEY_INIT_ ## keytype_str, \
                                   keytype) \
            __attribute__((visibility("internal"))); \
    SHAREMIND_MAP_KEY_INIT_DEFINE(SHAREMIND_MAP_KEY_INIT_ ## keytype_str, \
                                  keytype) \
    SHAREMIND_MAP_KEY_FREE_DECLARE(SHAREMIND_MAP_KEY_FREE_ ## keytype_str, \
                                   keytype) \
            __attribute__((visibility("internal"))); \
    SHAREMIND_MAP_KEY_FREE_DEFINE(SHAREMIND_MAP_KEY_FREE_ ## keytype_str, \
                                  keytype) \
    SHAREMIND_MAP_KEY_COPY_DECLARE(SHAREMIND_MAP_KEY_COPY_ ## keytype_str, \
                                   keytype) \
            __attribute__((visibility("internal"))); \
    SHAREMIND_MAP_KEY_COPY_DEFINE(SHAREMIND_MAP_KEY_COPY_ ## keytype_str, \
                                  keytype) \
    SHAREMIND_MAP_KEY_EQUALS_DECLARE(SHAREMIND_MAP_KEY_EQUALS_ ## keytype_str, \
                                     keytype) \
            __attribute__((visibility("internal"))); \
    SHAREMIND_MAP_KEY_EQUALS_DEFINE(SHAREMIND_MAP_KEY_EQUALS_ ## keytype_str, \
                                    keytype) \
    SHAREMIND_MAP_KEY_LESS_DECLARE(SHAREMIND_MAP_KEY_LESS_ ## keytype_str,\
                                   keytype) \
            __attribute__((visibility("internal"))); \
    SHAREMIND_MAP_KEY_LESS_DEFINE(SHAREMIND_MAP_KEY_LESS_ ## keytype_str, \
                                  keytype)

#define SHAREMIND_MAP_KEYOPS_DECLARE_DEFINE(keytype) \
    SHAREMIND_MAP_KEYOPS_DECLARE_DEFINE_(keytype,keytype)

SHAREMIND_MAP_KEYOPS_DECLARE_DEFINE(char)
SHAREMIND_MAP_KEYOPS_DECLARE_DEFINE_(signed_char,signed char)
SHAREMIND_MAP_KEYOPS_DECLARE_DEFINE_(unsigned_char,unsigned char)
SHAREMIND_MAP_KEYOPS_DECLARE_DEFINE(short)
SHAREMIND_MAP_KEYOPS_DECLARE_DEFINE_(unsigned_short,unsigned short)
SHAREMIND_MAP_KEYOPS_DECLARE_DEFINE(int)
SHAREMIND_MAP_KEYOPS_DECLARE_DEFINE(unsigned)
SHAREMIND_MAP_KEYOPS_DECLARE_DEFINE_(unsigned_int,unsigned int)
SHAREMIND_MAP_KEYOPS_DECLARE_DEFINE(long)
SHAREMIND_MAP_KEYOPS_DECLARE_DEFINE_(unsigned_long,unsigned long)
SHAREMIND_MAP_KEYOPS_DECLARE_DEFINE(size_t)
SHAREMIND_MAP_KEYOPS_DECLARE_DEFINE(int8_t)
SHAREMIND_MAP_KEYOPS_DECLARE_DEFINE(int16_t)
SHAREMIND_MAP_KEYOPS_DECLARE_DEFINE(int32_t)
SHAREMIND_MAP_KEYOPS_DECLARE_DEFINE(int64_t)
SHAREMIND_MAP_KEYOPS_DECLARE_DEFINE(uint8_t)
SHAREMIND_MAP_KEYOPS_DECLARE_DEFINE(uint16_t)
SHAREMIND_MAP_KEYOPS_DECLARE_DEFINE(uint32_t)
SHAREMIND_MAP_KEYOPS_DECLARE_DEFINE(uint64_t)
SHAREMIND_MAP_KEYOPS_DECLARE_DEFINE(int_fast8_t)
SHAREMIND_MAP_KEYOPS_DECLARE_DEFINE(int_fast16_t)
SHAREMIND_MAP_KEYOPS_DECLARE_DEFINE(int_fast32_t)
SHAREMIND_MAP_KEYOPS_DECLARE_DEFINE(int_fast64_t)
SHAREMIND_MAP_KEYOPS_DECLARE_DEFINE(uint_fast8_t)
SHAREMIND_MAP_KEYOPS_DECLARE_DEFINE(uint_fast16_t)
SHAREMIND_MAP_KEYOPS_DECLARE_DEFINE(uint_fast32_t)
SHAREMIND_MAP_KEYOPS_DECLARE_DEFINE(uint_fast64_t)
SHAREMIND_MAP_KEYOPS_DECLARE_DEFINE(int_least8_t)
SHAREMIND_MAP_KEYOPS_DECLARE_DEFINE(int_least16_t)
SHAREMIND_MAP_KEYOPS_DECLARE_DEFINE(int_least32_t)
SHAREMIND_MAP_KEYOPS_DECLARE_DEFINE(int_least64_t)
SHAREMIND_MAP_KEYOPS_DECLARE_DEFINE(uint_least8_t)
SHAREMIND_MAP_KEYOPS_DECLARE_DEFINE(uint_least16_t)
SHAREMIND_MAP_KEYOPS_DECLARE_DEFINE(uint_least32_t)
SHAREMIND_MAP_KEYOPS_DECLARE_DEFINE(uint_least64_t)
SHAREMIND_MAP_KEYOPS_DECLARE_DEFINE_(voidptr,void *)

#define SHAREMIND_MAP_DECLARE_BODY(name,keytype,valuetype) \
    SHAREMIND_EXTERN_C_BEGIN \
    typedef struct { \
        keytype key; \
        valuetype value; \
    } name ## _value; \
    struct name ## _detail_ { \
        name ## _value v; \
        struct name ## _detail_ * next; \
    }; \
    typedef struct name ## _detail_ name ## _detail; \
    typedef struct { \
        size_t size; \
        name ## _detail * d[65536u]; \
    } name; \
    SHAREMIND_EXTERN_C_END

#define SHAREMIND_MAP_DECLARE_init(name,inlinePerhaps,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps void name ## _init(name * s) \
            __attribute__ ((SHAREMIND_NDEBUG_ONLY(nonnull(1),) __VA_ARGS__)); \
    SHAREMIND_EXTERN_C_END
#define SHAREMIND_MAP_DEFINE_init(name,inlinePerhaps) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps void name ## _init(name * s) { \
        assert(s); \
        s->size = 0u; \
        for (size_t i = 0u; i < 65536u; ++i) \
            s->d[i] = NULL; \
    } \
    SHAREMIND_EXTERN_C_END

#define SHAREMIND_MAP_DECLARE_destroy(name,inlinePerhaps,params,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps void name ## _destroy(name * s params) \
            __attribute__ ((SHAREMIND_NDEBUG_ONLY(nonnull(1),) __VA_ARGS__)); \
    SHAREMIND_EXTERN_C_END
#define SHAREMIND_MAP_DEFINE_destroy(name,inlinePerhaps,params,myfree,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps void name ## _destroy(name * s params) { \
        assert(s); \
        for (size_t i = 0u; i < 65536u; ++i) { \
            while (s->d[i]) { \
                name ## _detail * next = s->d[i]->next; \
                { \
                    name ## _value * const v = &s->d[i]->v; \
                    __VA_ARGS__ \
                    (void) v; \
                } \
                myfree(s->d[i]); \
                s->d[i] = next; \
            } \
        } \
    } \
    SHAREMIND_EXTERN_C_END

#define SHAREMIND_MAP_DECLARE_get(name,inlinePerhaps,constkeytype,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps name ## _value * name ## _get(name const * s, \
                                                constkeytype key) \
            __attribute__ ((SHAREMIND_NDEBUG_ONLY(nonnull(1),) __VA_ARGS__)); \
    SHAREMIND_EXTERN_C_END
#define SHAREMIND_MAP_DEFINE_get(name,inlinePerhaps,constkeytype,keyhash,keyequals,keyless) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps name ## _value * name ## _get(name const * s, \
                                                constkeytype key) \
    { \
        assert(s); \
        uint16_t hash = (uint16_t) (keyhash); \
        name ## _detail * l = s->d[hash]; \
        while (l) { \
            if (keyequals(key, l->v.key)) \
                return &l->v; \
            if (keyless(key, l->v.key)) \
                return NULL; \
            l = l->next; \
        } \
        return NULL; \
    } \
    SHAREMIND_EXTERN_C_END

#define SHAREMIND_MAP_DECLARE_at(name,inlinePerhaps,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps name ## _value * name ## _at(name const * s, size_t index) \
            __attribute__ ((SHAREMIND_NDEBUG_ONLY(nonnull(1),) __VA_ARGS__)); \
    SHAREMIND_EXTERN_C_END
#define SHAREMIND_MAP_DEFINE_at(name,inlinePerhaps) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps name ## _value * name ## _at(name const * s, size_t index) { \
        assert(s); \
        if (index < s->size) { \
            for (size_t i = 0u; i < 65536u; ++i) { \
                name ## _detail * detail = s->d[i]; \
                while (detail) { \
                    if (!index) \
                        return &detail->v; \
                    --index; \
                    detail = detail->next; \
                } \
            } \
        } \
        return NULL; \
    } \
    SHAREMIND_EXTERN_C_END

#define SHAREMIND_MAP_DECLARE_foreach_detail(prefix,name,params,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    prefix(name * s params) \
            __attribute__ ((SHAREMIND_NDEBUG_ONLY(nonnull(1),) __VA_ARGS__)); \
    SHAREMIND_EXTERN_C_END
#define SHAREMIND_MAP_DEFINE_foreach_detail(prefix,name,params,decls,doneResult,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    prefix(name * s params) { \
        assert(s); \
        decls \
        for (size_t i = 0u; i < 65536u; ++i) { \
            name ## _detail * detail = s->d[i]; \
            while (detail) { \
                { \
                    name ## _value * const v = &detail->v; \
                    __VA_ARGS__ \
                    (void) v; \
                } \
                detail = detail->next; \
            } \
        } \
        return doneResult; \
    } \
    SHAREMIND_EXTERN_C_END

#define SHAREMIND_MAP_DECLARE_foreach(name,inlinePerhaps,...) \
    SHAREMIND_MAP_DECLARE_foreach_detail( \
        inlinePerhaps bool name ## _foreach, \
        name, \
        SHAREMIND_COMMA bool (*f)(name ## _value *), \
        SHAREMIND_COMMA SHAREMIND_NDEBUG_ONLY(nonnull(2),) __VA_ARGS__)
#define SHAREMIND_MAP_DEFINE_foreach(name,inlinePerhaps) \
    SHAREMIND_MAP_DEFINE_foreach_detail( \
        inlinePerhaps bool name ## _foreach, \
        name, \
        SHAREMIND_COMMA bool (*f)(name ## _value *),, \
        true, \
        if (!((*f)(v))) \
            return false;)

#define SHAREMIND_MAP_DECLARE_foreachVoid(name,inlinePerhaps,...) \
    SHAREMIND_MAP_DECLARE_foreach_detail( \
        inlinePerhaps void name ## _foreachVoid, \
        name, \
        SHAREMIND_COMMA void (*f)(name ## _value *), \
        SHAREMIND_COMMA SHAREMIND_NDEBUG_ONLY(nonnull(2),) __VA_ARGS__)
#define SHAREMIND_MAP_DEFINE_foreachVoid(name,inlinePerhaps) \
    SHAREMIND_MAP_DEFINE_foreach_detail( \
        inlinePerhaps void name ## _foreachVoid, \
        name, \
        SHAREMIND_COMMA void (*f)(name ## _value *),,, \
        (*f)(v);)

#define SHAREMIND_MAP_DECLARE_foreachWith(name,inlinePerhaps,WithName,params,...) \
    SHAREMIND_MAP_DECLARE_foreach_detail( \
        inlinePerhaps bool name ## _foreachWith ## WithName, \
        name, \
        SHAREMIND_COMMA bool (*f)(name ## _value *) SHAREMIND_COMMA params, \
        SHAREMIND_COMMA SHAREMIND_NDEBUG_ONLY(nonnull(2),) __VA_ARGS__)
#define SHAREMIND_MAP_DEFINE_foreachWith(name,inlinePerhaps,WithName,params,...) \
    SHAREMIND_MAP_DEFINE_foreach_detail( \
        inlinePerhaps bool name ## _foreachWith ## WithName, \
        name, \
        SHAREMIND_COMMA bool (*f)(name ## _value *) SHAREMIND_COMMA params,, \
        true, \
        if (!((*f)(v SHAREMIND_COMMA __VA_ARGS__))) \
            return false;)

#define SHAREMIND_MAP_DECLARE_foreachVoidWith(name,inlinePerhaps,WithName,params,...) \
    SHAREMIND_MAP_DECLARE_foreach_detail( \
        inlinePerhaps void name ## _foreachVoidWith ## WithName, \
        name, \
        SHAREMIND_COMMA void (*f)(name ## _value *) SHAREMIND_COMMA params, \
        SHAREMIND_COMMA SHAREMIND_NDEBUG_ONLY(nonnull(2),) __VA_ARGS__)
#define SHAREMIND_MAP_DEFINE_foreachVoidWith(name,inlinePerhaps,WithName,params,...) \
    SHAREMIND_MAP_DEFINE_foreach_detail( \
        inlinePerhaps void name ## _foreachVoidWith ## WithName, \
        name, \
        SHAREMIND_COMMA void (*f)(name ## _value *) SHAREMIND_COMMA params,,, \
        (*f)(v SHAREMIND_COMMA __VA_ARGS__);)

#define SHAREMIND_MAP_DECLARE_insertHint(name,inlinePerhaps,constkeytype,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps void * name ## _insertHint(name * s, constkeytype key) \
            __attribute__ ((SHAREMIND_NDEBUG_ONLY(nonnull(1),) __VA_ARGS__)); \
    SHAREMIND_EXTERN_C_END
#define SHAREMIND_MAP_DEFINE_insertHint(name,inlinePerhaps,constkeytype,keyhash,keyequals,keyless) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps void * name ## _insertHint(name * s, constkeytype key) { \
        assert(s); \
        SHAREMIND_SIZET_NUM_OBJECTS_GUARD(assert(s->size < SIZE_MAX);) \
        name ## _detail ** l = &s->d[(uint16_t) (keyhash)]; \
        while ((*l) && !(keyless(key, (*l)->v.key))) { \
            if (keyequals(key, (*l)->v.key)) \
                return NULL; \
            l = &(*l)->next; \
        } \
        return l; \
    } \
    SHAREMIND_EXTERN_C_END

#define SHAREMIND_MAP_DECLARE_emplaceAtHint(name,inlinePerhaps,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps void name ## _emplaceAtHint(name * s, \
                                              name ## _detail * detail, \
                                              void * const hint) \
            __attribute__ ((SHAREMIND_NDEBUG_ONLY(nonnull(1,2,3),) \
                            __VA_ARGS__)); \
    SHAREMIND_EXTERN_C_END
#define SHAREMIND_MAP_DEFINE_emplaceAtHint(name,inlinePerhaps) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps void name ## _emplaceAtHint(name * s, \
                                              name ## _detail * detail, \
                                              void * const hint) \
    { \
        assert(s); \
        assert(detail); \
        assert(hint); \
        name ## _detail ** l = (name ## _detail **) hint; \
        detail->next = (*l); \
        (*l) = detail; \
        ++(s->size); \
    } \
    SHAREMIND_EXTERN_C_END

#define SHAREMIND_MAP_DECLARE_insertAtHint(name,inlinePerhaps,constkeytype,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps name ## _value * name ## _insertAtHint(name * s, \
                                                         constkeytype key, \
                                                         void * const hint) \
            __attribute__ ((SHAREMIND_NDEBUG_ONLY(nonnull(1,3),) __VA_ARGS__));\
    SHAREMIND_EXTERN_C_END
#define SHAREMIND_MAP_DEFINE_insertAtHint(name,inlinePerhaps,constkeytype,keycopy,mymalloc,myfree) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps name ## _value * name ## _insertAtHint(name * s, \
                                                         constkeytype key, \
                                                         void * const hint) \
    { \
        assert(s); \
        assert(hint); \
        SHAREMIND_SIZET_NUM_OBJECTS_GUARD(assert(s->size < SIZE_MAX);) \
        name ## _detail * newDetail = \
                SHAREMIND_MAP_ALLOC_CAST(name ## _detail *) \
                        mymalloc(sizeof(name ## _detail)); \
        if (!newDetail) \
            return NULL; \
        if (!keycopy(&newDetail->v.key, key)) { \
            myfree(newDetail); \
            return NULL; \
        } \
        name ## _emplaceAtHint(s, newDetail, hint); \
        return &newDetail->v; \
    } \
    SHAREMIND_EXTERN_C_END

#define SHAREMIND_MAP_DECLARE_insertNew(name,inlinePerhaps,constkeytype,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps name ## _value * name ## _insertNew(name * s, \
                                                      constkeytype key) \
            __attribute__ ((SHAREMIND_NDEBUG_ONLY(nonnull(1),) __VA_ARGS__)); \
    SHAREMIND_EXTERN_C_END
#define SHAREMIND_MAP_DEFINE_insertNew(name,inlinePerhaps,constkeytype) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps name ## _value * name ## _insertNew(name * s, \
                                                      constkeytype key) \
    { \
        assert(s); \
        SHAREMIND_SIZET_NUM_OBJECTS_GUARD(assert(s->size < SIZE_MAX);) \
        void * const hint = name ## _insertHint(s, key); \
        assert(hint); \
        return name ## _insertAtHint(s, key, hint);\
    } \
    SHAREMIND_EXTERN_C_END

#define SHAREMIND_MAP_DECLARE_take(name,inlinePerhaps,constkeytype,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps name ## _detail * name ## _take(name * s, constkeytype key) \
            __attribute__ ((SHAREMIND_NDEBUG_ONLY(nonnull(1),) __VA_ARGS__)); \
    SHAREMIND_EXTERN_C_END
#define SHAREMIND_MAP_DEFINE_take(name,inlinePerhaps,constkeytype,keyhash,keyequals,keyless) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps name ## _detail * name ## _take(name * s, constkeytype key) { \
        assert(s); \
        uint16_t hash = (uint16_t) (keyhash); \
        name ## _detail ** prevPtr = &s->d[hash]; \
        name ## _detail * l = *prevPtr; \
        while (l) { \
            if (keyequals(key, l->v.key)) { \
                *prevPtr = l->next; \
                --(s->size); \
                return l; \
            } \
            if (keyless(key, l->v.key)) \
                return NULL; \
            prevPtr = &l->next; \
            l = *prevPtr; \
        } \
        return NULL; \
    } \
    SHAREMIND_EXTERN_C_END

#define SHAREMIND_MAP_DECLARE_remove(name,inlinePerhaps,constkeytype,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps bool name ## _remove(name * s, constkeytype key) \
            __attribute__ ((SHAREMIND_NDEBUG_ONLY(nonnull(1),) __VA_ARGS__)); \
    SHAREMIND_EXTERN_C_END
#define SHAREMIND_MAP_DEFINE_remove(name,inlinePerhaps,constkeytype,myfree,...)\
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps bool name ## _remove(name * s, constkeytype key) { \
        assert(s); \
        name ## _detail * const d = name ## _take(s, key); \
        if (!d) \
            return false;  \
        { \
            name ## _value * const v = &d->v; \
            __VA_ARGS__ \
            (void) v; \
        } \
        myfree(d); \
        return true; \
    } \
    SHAREMIND_EXTERN_C_END

#endif /* SHAREMIND_MAP_H */
