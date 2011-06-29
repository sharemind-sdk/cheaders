#ifndef CODEBLOCK_H
#define CODEBLOCK_H

#include <stddef.h>
#include <stdint.h>


union SVM_IBlock {
    uint64_t uint64[1];
    uint32_t uint32[2];
    uint16_t uint16[4];
    uint8_t  uint8[8];
    int64_t int64[1];
    int32_t int32[2];
    int16_t int16[4];
    int8_t  int8[8];
    char chr[8];
    float float32[2];
    size_t sizet[1];
    void * p[1];
};

#endif /* CODEBLOCK_H */
