/*
 * This file is a part of the Sharemind framework.
 * Copyright (C) Cybernetica AS
 *
 * All rights are reserved. Reproduction in whole or part is prohibited
 * without the written consent of the copyright owner. The usage of this
 * code is subject to the appropriate license agreement.
 */

#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/facilities/expand.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/seq/seq.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/tuple/elem.hpp>


#define  SM_C(a, b) BOOST_PP_CAT(a, b)
#define SM_C2(a, b) BOOST_PP_CAT(a, b)
#define SM_C3(a, b, c) SM_C(SM_C(a, b), c)
#define SM_C4(a, b, c, d) SM_C3(SM_C(a, b), c, d)
#define SM_C5(a, b, c, d, e) SM_C4(SM_C(a, b), c, d, e)
#define SM_C6(a, b, c, d, e, f) SM_C5(SM_C(a, b), c, d, e, f)
#define SM_C7(a, b, c, d, e, f, g) SM_C6(SM_C(a, b), c, d, e, f, g)

#define SM_T(c,i,t) BOOST_PP_TUPLE_ELEM(c,i,t)
#define SM_S(i,s)   BOOST_PP_SEQ_ELEM(i, s)
#define SM_2S(t)    BOOST_PP_STRINGIZE(t) 


/*
 * Make little-endian representations of big-endian input.
 */
#define SM_MAKE_UINT16_LE(b0,b1) \
     (((uint16_t)(b0) <<  8) | (uint16_t)(b1))
#define SM_MAKE_UINT32_LE(b0,b1,b2,b3) \
    ((((uint32_t) SM_MAKE_UINT16_LE(b0,b1)) << 16) | ((uint32_t) SM_MAKE_UINT16_LE(b2,b3)))
#define SM_MAKE_UINT64_LE(b0,b1,b2,b3,b4,b5,b6,b7) \
    ((((uint64_t) SM_MAKE_UINT32_LE(b0,b1,b2,b3)) << 32) | ((uint64_t) SM_MAKE_UINT32_LE(b4,b5,b6,b7)))

/*
 * Make big-endian representations of big-endian input.
 */
#define SM_MAKE_UINT16_BE(b0,b1) \
     (((uint16_t)(b1) <<  8) | (uint16_t)(b0))
#define SM_MAKE_UINT32_BE(b0,b1,b2,b3) \
    ((((uint32_t) SM_MAKE_UINT16_BE(b3,b2)) << 16) | ((uint32_t) SM_MAKE_UINT16_BE(b1,b0)))
#define SM_MAKE_UINT64_BE(b0,b1,b2,b3,b4,b5,b6,b7) \
    ((((uint64_t) SM_MAKE_UINT32_BE(b5,b4,b7,b6)) << 32) | ((uint64_t) SM_MAKE_UINT32_BE(b1,b0,b3,b2)))

/**
 * \brief Defines a simple enum.
 * \param[in] name name of enum.
 * \param[in] elems (a)(sequence)(of)(enum)(keys)
 */
#define SM_ENUM_DEFINE(name,elems) enum name { BOOST_PP_SEQ_FOR_EACH_I(SM_ENUM_DEFINE_ELEM,_,elems) }
#define SM_ENUM_DEFINE_ELEM(unused,unused2,i,e) BOOST_PP_COMMA_IF(i) e

/**
 * \brief Defines an advanced enum.
 * \param[in] name name of enum.
 * \param[in] elems ((a sequence of tuples with,))((keys and, = optional values))
 */
#define SM_ENUM_CUSTOM_DEFINE(name,elems) enum name { BOOST_PP_SEQ_FOR_EACH_I(SM_ENUM_CUSTOM_DEFINE_ELEM,_,elems) }
#define SM_ENUM_CUSTOM_DEFINE_ELEM(unused,unused2,i,e) BOOST_PP_COMMA_IF(i) SM_T(2,0,e) SM_T(2,1,e)

/**
 * \brief Declares a _toString method for an enum.
 * \param[in] name The name of the enum. The name is also used as a prefix to
 *                 the function name.
 */
#define SM_ENUM_DECLARE_TOSTRING(name) const char * name ## _toString(enum name v)

/**
 * \brief Defines a _toString method for an enum.
 * \param[in] name The name of the enum. The name is also used as a prefix to
 *                 the function name.
 * \param[in] elems (a)(sequence)(of)(enum)(keys)
 */
#define SM_ENUM_DEFINE_TOSTRING(name,elems) \
    const char * name ## _toString(enum name v) { \
        switch (v) { \
            BOOST_PP_SEQ_FOR_EACH(SM_ENUM_DEFINE_TOSTRING_ELEM,_,elems) \
            default: \
                return "UNKNOWN"; \
        } \
    }
#define SM_ENUM_DEFINE_TOSTRING_ELEM(unused,unused2,e) \
    case e: \
        return SM_2S(e);

/**
 * \brief Defines a _toString method for an enum.
 * \param[in] name The name of the enum. The name is also used as a prefix to
 *                 the function name.
 * \param[in] elems ((a sequence of tuples with,))((keys and, = optional values))
 */
#define SM_ENUM_CUSTOM_DEFINE_TOSTRING(name,elems) \
    const char * name ## _toString(enum name v) { \
        switch (v) { \
            BOOST_PP_SEQ_FOR_EACH(SM_ENUM_CUSTOM_DEFINE_TOSTRING_ELEM,_,elems) \
            default: \
                return "UNKNOWN"; \
        } \
    }
#define SM_ENUM_CUSTOM_DEFINE_TOSTRING_ELEM(unused,unused2,e) \
    case SM_T(2,0,e): \
        return SM_2S(SM_T(2,0,e));


#endif /* PREPROCESSOR_H */
