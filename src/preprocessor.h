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

#ifndef SHAREMIND_PREPROCESSOR_H
#define SHAREMIND_PREPROCESSOR_H

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/facilities/expand.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/seq/seq.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <stddef.h>
#include "null.h"
#include "static_assert.h"


#define  SHAREMIND_C(a, b) BOOST_PP_CAT(a, b)
#define SHAREMIND_C2(a, b) BOOST_PP_CAT(a, b)
#define SHAREMIND_C3(a, b, c) SHAREMIND_C(SHAREMIND_C(a, b), c)
#define SHAREMIND_C4(a, b, c, d) SHAREMIND_C3(SHAREMIND_C(a, b), c, d)
#define SHAREMIND_C5(a, b, c, d, e) SHAREMIND_C4(SHAREMIND_C(a, b), c, d, e)
#define SHAREMIND_C6(a, b, c, d, e, f) SHAREMIND_C5(SHAREMIND_C(a, b), c, d, e, f)
#define SHAREMIND_C7(a, b, c, d, e, f, g) SHAREMIND_C6(SHAREMIND_C(a, b), c, d, e, f, g)

#define SHAREMIND_T(c,i,t) BOOST_PP_TUPLE_ELEM(c,i,t)
#define SHAREMIND_S(i,s)   BOOST_PP_SEQ_ELEM(i, s)
#define SHAREMIND_2S(t)    BOOST_PP_STRINGIZE(t)


/*
 * Make little-endian representations of big-endian input.
 */
#define SHAREMIND_MAKE_UINT16_LE(b0,b1) \
     (((uint16_t)(b0) <<  8) | (uint16_t)(b1))
#define SHAREMIND_MAKE_UINT32_LE(b0,b1,b2,b3) \
    ((((uint32_t) SHAREMIND_MAKE_UINT16_LE(b0,b1)) << 16) | ((uint32_t) SHAREMIND_MAKE_UINT16_LE(b2,b3)))
#define SHAREMIND_MAKE_UINT64_LE(b0,b1,b2,b3,b4,b5,b6,b7) \
    ((((uint64_t) SHAREMIND_MAKE_UINT32_LE(b0,b1,b2,b3)) << 32) | ((uint64_t) SHAREMIND_MAKE_UINT32_LE(b4,b5,b6,b7)))

/*
 * Make big-endian representations of big-endian input.
 */
#define SHAREMIND_MAKE_UINT16_BE(b0,b1) \
     (((uint16_t)(b1) <<  8) | (uint16_t)(b0))
#define SHAREMIND_MAKE_UINT32_BE(b0,b1,b2,b3) \
    ((((uint32_t) SHAREMIND_MAKE_UINT16_BE(b3,b2)) << 16) | ((uint32_t) SHAREMIND_MAKE_UINT16_BE(b1,b0)))
#define SHAREMIND_MAKE_UINT64_BE(b0,b1,b2,b3,b4,b5,b6,b7) \
    ((((uint64_t) SHAREMIND_MAKE_UINT32_BE(b5,b4,b7,b6)) << 32) | ((uint64_t) SHAREMIND_MAKE_UINT32_BE(b1,b0,b3,b2)))

/**
 * \brief Defines a simple enum.
 * \param[in] name name of enum.
 * \param[in] elems (a)(sequence)(of)(enum)(keys)
 */
#define SHAREMIND_ENUM_DEFINE(name,elems) typedef enum { BOOST_PP_SEQ_FOR_EACH_I(SHAREMIND_ENUM_DEFINE_ELEM,_,elems) } name
#define SHAREMIND_ENUM_DEFINE_ELEM(unused,unused2,i,e) BOOST_PP_COMMA_IF(i) e

/**
 * \brief Defines an advanced enum.
 * \param[in] name name of enum.
 * \param[in] elems ((a sequence of tuples with,))((keys and, = optional values))
 */
#define SHAREMIND_ENUM_CUSTOM_DEFINE(name,elems) typedef enum { BOOST_PP_SEQ_FOR_EACH_I(SHAREMIND_ENUM_CUSTOM_DEFINE_ELEM,_,elems) } name
#define SHAREMIND_ENUM_CUSTOM_DEFINE_ELEM(unused,unused2,i,e) BOOST_PP_COMMA_IF(i) SHAREMIND_T(2,0,e) SHAREMIND_T(2,1,e)

/**
 * \brief Declares a _toString method for an enum.
 * \param[in] name The name of the enum. The name is also used as a prefix to
 *                 the function name.
 */
#define SHAREMIND_ENUM_DECLARE_TOSTRING(name) SHAREMIND_ENUM_DECLARE_TOSTRING_CUSTOMNAME(name ## _toString, name)

/**
 * \brief Declares a _toString method for an enum with a custom function name.
 * \param[in] customName The custom name for the function.
 * \param[in] name The name of the enum. The name is also used as a prefix to
 *                 the function name.
 */
#define SHAREMIND_ENUM_DECLARE_TOSTRING_CUSTOMNAME(customName,enumName) const char * customName(enumName v) __attribute__ ((warn_unused_result))

/**
 * \brief Defines a _toString method for an enum with an optional prefix and
 *        suffix.
 * \param[in] enumName The name of the enum. The name is also used as a prefix to
 *                     the function name.
 * \param[in] elems (a)(sequence)(of)(enum)(keys)
 * \param[in] prefix a string prefix
 * \param[in] suffix a string suffix
 */
#define SHAREMIND_ENUM_DEFINE_CUSTOM_TOSTRING(enumName,elems,prefix,suffix) \
    SHAREMIND_ENUM_DEFINE_CUSTOM_TOSTRING_CUSTOMNAME(enumName ## _toString,enumName,elems,prefix,suffix)

/**
 * \brief Defines a _toString method for an enum with an optional prefix, an
 *        optional suffix and a custom name.
 * \param[in] customName The custom name for the function.
 * \param[in] enumName The name of the enum. The name is also used as a prefix to
 *                     the function name.
 * \param[in] elems (a)(sequence)(of)(enum)(keys)
 * \param[in] prefix a string prefix
 * \param[in] suffix a string suffix
 */
#define SHAREMIND_ENUM_DEFINE_CUSTOM_TOSTRING_CUSTOMNAME(customName,enumName,elems,prefix,suffix) \
    const char * customName(enumName v) { \
        SHAREMIND_STATIC_ASSERT(sizeof(enumName) <= sizeof(int)); \
        switch ((int) v) { \
            BOOST_PP_SEQ_FOR_EACH(SHAREMIND_ENUM_DEFINE_CUSTOM_TOSTRING_ELEM,(prefix)(suffix),elems) \
            default: \
                return SHAREMIND_NULL; \
        } \
    }
#define SHAREMIND_ENUM_DEFINE_CUSTOM_TOSTRING_ELEM(unused,ps,e) \
    case e: \
        return SHAREMIND_S(0,ps) SHAREMIND_2S(e) SHAREMIND_S(1,ps);

/**
 * \brief Defines a _toString method for an enum.
 * \param[in] enumName The name of the enum. The name is also used as a prefix to
 *                     the function name.
 * \param[in] elems (a)(sequence)(of)(enum)(keys)
 */
#define SHAREMIND_ENUM_DEFINE_TOSTRING(enumName,elems) \
    SHAREMIND_ENUM_DEFINE_CUSTOM_TOSTRING(enumName,elems,"","")

/**
 * \brief Defines a _toString method for an enum with a custom name.
 * \param[in] customName The custom name for the function.
 * \param[in] enumName The name of the enum. The name is also used as a prefix to
 *                     the function name.
 * \param[in] elems (a)(sequence)(of)(enum)(keys)
 */
#define SHAREMIND_ENUM_DEFINE_TOSTRING_CUSTOMNAME(customName,enumName,elems) \
    SHAREMIND_ENUM_DEFINE_CUSTOM_TOSTRING_CUSTOMNAME(costomName,enumName,elems,"","")

/**
 * \brief Defines a _toString method for an enum.
 * \param[in] name The name of the enum. The name is also used as a prefix to
 *                 the function name.
 * \param[in] elems ((a sequence of tuples with,))((keys and, = optional values))
 * \param[in] prefix a string prefix
 * \param[in] suffix a string suffix
 */
#define SHAREMIND_ENUM_CUSTOM_DEFINE_CUSTOM_TOSTRING(enumName,elems,prefix,suffix) \
    SHAREMIND_ENUM_CUSTOM_DEFINE_CUSTOM_TOSTRING_CUSTOMNAME(enumName ## _toString,enumName,elems,prefix,suffix)

/**
 * \brief Defines a _toString method for an enum using a custom function name.
 * \param[in] customName The custom name for the function.
 * \param[in] name The name of the enum. The name is also used as a prefix to
 *                 the function name.
 * \param[in] elems ((a sequence of tuples with,))((keys and, = optional values))
 * \param[in] prefix a string prefix
 * \param[in] suffix a string suffix
 */
#define SHAREMIND_ENUM_CUSTOM_DEFINE_CUSTOM_TOSTRING_CUSTOMNAME(customName,enumName,elems,prefix,suffix) \
    const char * customName(enumName v) { \
        SHAREMIND_STATIC_ASSERT(sizeof(enumName) <= sizeof(int)); \
        switch ((int) v) { \
            BOOST_PP_SEQ_FOR_EACH(SHAREMIND_ENUM_CUSTOM_DEFINE_CUSTOM_TOSTRING_ELEM,(prefix)(suffix),elems) \
            default: \
                return SHAREMIND_NULL; \
        } \
    }
#define SHAREMIND_ENUM_CUSTOM_DEFINE_CUSTOM_TOSTRING_ELEM(unused,ps,e) \
    case SHAREMIND_T(2,0,e): \
        return SHAREMIND_S(0,ps) SHAREMIND_2S(SHAREMIND_T(2,0,e)) SHAREMIND_S(1,ps);

/**
 * \brief Defines a _toString method for an enum.
 * \param[in] name The name of the enum. The name is also used as a prefix to
 *                 the function name.
 * \param[in] elems ((a sequence of tuples with,))((keys and, = optional values))
 */
#define SHAREMIND_ENUM_CUSTOM_DEFINE_TOSTRING(name,elems) \
    SHAREMIND_ENUM_CUSTOM_DEFINE_CUSTOM_TOSTRING(name,elems,"","")

#endif /* SHAREMIND_PREPROCESSOR_H */
