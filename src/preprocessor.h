#ifndef PP_H
#define PP_H

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/elem.hpp>
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


#define SVM_MAKE_UINT16(b0,b1) \
     (((uint16_t)(b0) <<  8) | (uint16_t)(b1))
#define SVM_MAKE_UINT32(b0,b1,b2,b3) \
    ((((uint32_t) SVM_MAKE_UINT16(b0,b1)) << 16) | ((uint32_t) SVM_MAKE_UINT16(b2,b3)))
#define SVM_MAKE_UINT64(b0,b1,b2,b3,b4,b5,b6,b7) \
    ((((uint64_t) SVM_MAKE_UINT32(b0,b1,b2,b3)) << 32) | ((uint64_t) SVM_MAKE_UINT32(b4,b5,b6,b7)))

#endif /* PP_H */
