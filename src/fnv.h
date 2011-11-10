/*
 * This file is a part of the Sharemind framework.
 * Copyright (C) Cybernetica AS
 *
 * All rights are reserved. Reproduction in whole or part is prohibited
 * without the written consent of the copyright owner. The usage of this
 * code is subject to the appropriate license agreement.
 */

/*
  Based on Fowler/Noll/Vo FNV-1a hash code in public domain taken from:
    http://www.isthe.com/chongo/src/fnv/fnv.h
    http://www.isthe.com/chongo/src/fnv/hash_32a.c
    http://www.isthe.com/chongo/src/fnv/hash_64a.c
*/

#ifndef SHAREMIND_FNV_H
#define SHAREMIND_FNV_H

#include <assert.h>
#include <stddef.h>
#include <stdint.h>


/**
  \brief Generates a 64 bit Fowler/Noll/Vo FNV-1a hash for the given buffer.
  \param[in] buf start of buffer to hash
  \param[in] len length of buffer in octets
  \returns 64 bit hash value
*/
inline uint64_t fnv_64a_buf(register const void * buf, register size_t len) {
    assert(buf);
    register uint64_t hval = UINT64_C(0xcbf29ce484222325); /* Initial hash recommended value */
    for (size_t i = 0u; i < len; i++) {
        hval ^= (uint64_t) ((const uint8_t *) buf)[i];
        hval *= UINT64_C(0x100000001b3);
    }
    return hval;
}

/**
  \brief Generates a 64 bit Fowler/Noll/Vo FNV-1a hash for the given NULL-terminated string.
  \param[in] str string to hash
  \returns 64 bit hash value
*/
inline uint64_t fnv_64a_str(register const char * str) {
    assert(str);
    register uint64_t hval = UINT64_C(0xcbf29ce484222325); /* Initial hash recommended value */
    while (*str) {
        hval ^= (uint64_t) *((const uint8_t *) str++);
        hval *= UINT64_C(0x100000001b3);
    }
    return hval;
}

/**
  \brief Generates a 32 bit Fowler/Noll/Vo FNV-1a hash for the given buffer.
  \param[in] buf start of buffer to hash
  \param[in] len length of buffer in octets
  \returns 32 bit hash value
*/
inline uint32_t fnv_32a_buf(register const void * buf, register size_t len) {
    assert(buf);
    register uint32_t hval = UINT32_C(0x811c9dc5); /* Initial hash recommended value */
    for (register size_t i = 0u; i < len; i++) {
        hval ^= (uint32_t) ((const uint8_t *) buf)[i];
        hval *= UINT32_C(0x01000193);
    }
    return hval;
}

/**
  \brief Generates a 32 bit Fowler/Noll/Vo FNV-1a hash for the given NULL-terminated string.
  \param[in] str string to hash
  \returns 32 bit hash value
*/
inline uint32_t fnv_32a_str(register const char * str) {
    assert(str);
    register uint32_t hval = UINT32_C(0x811c9dc5); /* Initial hash recommended value */
    while (*str) {
        hval ^= (uint32_t) *((const uint8_t *) str++);
        hval *= UINT32_C(0x01000193);
    }
    return hval;
}

/**
  \brief Generates a 16-bit hash based on the 32 bit Fowler/Noll/Vo FNV-1a hash for the given buffer.
  \param[in] str string to hash
  \returns 16 bit hash value
*/
inline uint16_t fnv_16a_buf(register const void * buf, register size_t len) {
    assert(buf);
    uint32_t hval = fnv_32a_buf(buf, len);
    return (uint16_t) (hval ^ (hval >> 16));
}

/**
  \brief Generates a 16-bit hash based on the 32 bit Fowler/Noll/Vo FNV-1a hash for the given NULL-terminated string.
  \param[in] str string to hash
  \returns 16 bit hash value
*/
inline uint16_t fnv_16a_str(register const char * str) {
    assert(str);
    uint32_t hval = fnv_32a_str(str);
    return (uint16_t) (hval ^ (hval >> 16));
}

#endif /* SHAREMIND_FNV_H */
