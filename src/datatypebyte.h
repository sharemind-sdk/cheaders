#ifndef DATATYPEBYTE_H
#define DATATYPEBYTE_H

#include "preprocessor.h"

/* (name, code, type) */
#define SVM_DTB_uint8   (uint8,   0x01, uint8_t)
#define SVM_DTB_uint16  (uint16,  0x02, uint16_t)
#define SVM_DTB_uint32  (uint32,  0x03, uint32_t)
#define SVM_DTB_uint64  (uint64,  0x04, uint64_t)
#define SVM_DTB_int8    (int8,    0x11, int8_t)
#define SVM_DTB_int16   (int16,   0x12, int16_t)
#define SVM_DTB_int32   (int32,   0x13, int32_t)
#define SVM_DTB_int64   (int64,   0x14, int64_t)
#define SVM_DTB_float32 (float32, 0x23, float)

#define SVM_DTB(name) SVM_C(SVM_DTB_,name)

#define SVM_DTB_name(t) SVM_T(3,0,t)
#define SVM_DTB_code(t) SVM_T(3,1,t)
#define SVM_DTB_type(t) SVM_T(3,2,t)

#define SVM_DTB_FOREACH_MACRO(_,m,i) m(SVM_DTB(i))
#define SVM_DTB_FOREACH(m,s) BOOST_PP_SEQ_FOR_EACH(SVM_DTB_FOREACH_MACRO,m,s)

#endif /* DATATYPEBYTE_H */
