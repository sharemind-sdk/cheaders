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


#define  SVM_C(a, b) BOOST_PP_CAT(a, b)
#define SVM_C2(a, b) BOOST_PP_CAT(a, b)
#define SVM_C3(a, b, c) SVM_C(SVM_C(a, b), c)
#define SVM_C4(a, b, c, d) SVM_C3(SVM_C(a, b), c, d)
#define SVM_C5(a, b, c, d, e) SVM_C4(SVM_C(a, b), c, d, e)
#define SVM_C6(a, b, c, d, e, f) SVM_C5(SVM_C(a, b), c, d, e, f)
#define SVM_C7(a, b, c, d, e, f, g) SVM_C6(SVM_C(a, b), c, d, e, f, g)

#define SVM_T(c,i,t) BOOST_PP_TUPLE_ELEM(c,i,t)
#define SVM_S(i,s)   BOOST_PP_SEQ_ELEM(i, s)
#define SVM_2S(t)    BOOST_PP_STRINGIZE(t) 


/*
 * Make little-endian representations of big-endian input.
 */
#define SVM_MAKE_UINT16_LE(b0,b1) \
     (((uint16_t)(b0) <<  8) | (uint16_t)(b1))
#define SVM_MAKE_UINT32_LE(b0,b1,b2,b3) \
    ((((uint32_t) SVM_MAKE_UINT16_LE(b0,b1)) << 16) | ((uint32_t) SVM_MAKE_UINT16_LE(b2,b3)))
#define SVM_MAKE_UINT64_LE(b0,b1,b2,b3,b4,b5,b6,b7) \
    ((((uint64_t) SVM_MAKE_UINT32_LE(b0,b1,b2,b3)) << 32) | ((uint64_t) SVM_MAKE_UINT32_LE(b4,b5,b6,b7)))

/*
 * Make big-endian representations of big-endian input.
 */
#define SVM_MAKE_UINT16_BE(b0,b1) \
     (((uint16_t)(b1) <<  8) | (uint16_t)(b0))
#define SVM_MAKE_UINT32_BE(b0,b1,b2,b3) \
    ((((uint32_t) SVM_MAKE_UINT16_BE(b3,b2)) << 16) | ((uint32_t) SVM_MAKE_UINT16_BE(b1,b0)))
#define SVM_MAKE_UINT64_BE(b0,b1,b2,b3,b4,b5,b6,b7) \
    ((((uint64_t) SVM_MAKE_UINT32_BE(b5,b4,b7,b6)) << 32) | ((uint64_t) SVM_MAKE_UINT32_BE(b1,b0,b3,b2)))

/**
 * \brief Defines a simple enum.
 * \param[in] name name of enum.
 * \param[in] elems (a)(sequence)(of)(enum)(keys)
 */
#define SVM_ENUM_DEFINE(name,elems) enum name { BOOST_PP_SEQ_FOR_EACH_I(SVM_ENUM_DEFINE_ELEM,_,elems) }
#define SVM_ENUM_DEFINE_ELEM(unused,unused2,i,e) BOOST_PP_COMMA_IF(i) e

/**
 * \brief Defines an advanced enum.
 * \param[in] name name of enum.
 * \param[in] elems ((a sequence of tuples with,))((keys and, = optional values))
 */
#define SVM_ENUM_CUSTOM_DEFINE(name,elems) enum name { BOOST_PP_SEQ_FOR_EACH_I(SVM_ENUM_CUSTOM_DEFINE_ELEM,_,elems) }
#define SVM_ENUM_CUSTOM_DEFINE_ELEM(unused,unused2,i,e) BOOST_PP_COMMA_IF(i) SVM_T(2,0,e) SVM_T(2,1,e)

/**
 * \brief Declares a _toString method for an enum.
 * \param[in] name The name of the enum. The name is also used as a prefix to
 *                 the function name.
 */
#define SVM_ENUM_DECLARE_TOSTRING(name) const char * name ## _toString(enum name v)

/**
 * \brief Defines a _toString method for an enum.
 * \param[in] name The name of the enum. The name is also used as a prefix to
 *                 the function name.
 * \param[in] elems (a)(sequence)(of)(enum)(keys)
 */
#define SVM_ENUM_DEFINE_TOSTRING(name,elems) \
    const char * name ## _toString(enum name v) { \
        switch (v) { \
            BOOST_PP_SEQ_FOR_EACH(SVM_ENUM_DEFINE_TOSTRING_ELEM,_,elems) \
            default: \
                return "UNKNOWN"; \
        } \
    }
#define SVM_ENUM_DEFINE_TOSTRING_ELEM(unused,unused2,e) \
    case e: \
        return SVM_2S(e);

/**
 * \brief Defines a _toString method for an enum.
 * \param[in] name The name of the enum. The name is also used as a prefix to
 *                 the function name.
 * \param[in] elems ((a sequence of tuples with,))((keys and, = optional values))
 */
#define SVM_ENUM_CUSTOM_DEFINE_TOSTRING(name,elems) \
    const char * name ## _toString(enum name v) { \
        switch (v) { \
            BOOST_PP_SEQ_FOR_EACH(SVM_ENUM_CUSTOM_DEFINE_TOSTRING_ELEM,_,elems) \
            default: \
                return "UNKNOWN"; \
        } \
    }
#define SVM_ENUM_CUSTOM_DEFINE_TOSTRING_ELEM(unused,unused2,e) \
    case SVM_T(2,0,e): \
        return SVM_2S(SVM_T(2,0,e));


#endif /* PREPROCESSOR_H */
