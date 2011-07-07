#ifndef COMMON_STATIC_ASSERTS_H
#define COMMON_STATIC_ASSERTS_H

#include <endian.h>
#include "static_assert.h"


SVM_STATIC_ASSERT(sizeof(union SVM_IBlock) == sizeof(uint64_t));
SVM_STATIC_ASSERT(sizeof(size_t) <= sizeof(uint64_t));
SVM_STATIC_ASSERT(sizeof(size_t) >= sizeof(uint16_t));
SVM_STATIC_ASSERT(sizeof(ptrdiff_t) <= sizeof(uint64_t));
SVM_STATIC_ASSERT(sizeof(float) == sizeof(uint32_t));
SVM_STATIC_ASSERT(sizeof(char) == sizeof(uint8_t));
SVM_STATIC_ASSERT(__BYTE_ORDER == __LITTLE_ENDIAN);
SVM_STATIC_ASSERT(sizeof(off_t) <= sizeof(size_t));

#endif /* COMMON_STATIC_ASSERTS_H */
