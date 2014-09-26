/*
 * This file is a part of the Sharemind framework.
 * Copyright (C) Cybernetica AS
 *
 * All rights are reserved. Reproduction in whole or part is prohibited
 * without the written consent of the copyright owner. The usage of this
 * code is subject to the appropriate license agreement.
 */

#ifndef SHAREMIND_APOCALYPTIC_SAFETY_H
#define SHAREMIND_APOCALYPTIC_SAFETY_H

#if defined(SHAREMIND_SIZET_NUM_OBJECTS_SAFETY) \
    && !!(SHAREMIND_SIZET_NUM_OBJECTS_SAFETY)
    #define SHAREMIND_SIZET_NUM_OBJECTS_GUARD(...) __VA_ARGS__
    #ifndef SHAREMIND_SIZET_MEMORY_SAFETY
        #define SHAREMIND_SIZET_MEMORY_SAFETY 1
    #elif !(SHAREMIND_SIZET_MEMORY_SAFETY)
        #error Eschatological absurdity
    #endif
#else
    #define SHAREMIND_SIZET_NUM_OBJECTS_GUARD(...)
#endif

#if defined(SHAREMIND_SIZET_MEMORY_SAFETY) \
    && !!(SHAREMIND_SIZET_MEMORY_SAFETY)
    #define SHAREMIND_SIZET_MEMORY_GUARD(...) __VA_ARGS__
#else
    #define SHAREMIND_SIZET_MEMORY_GUARD(...)
#endif

#endif /* SHAREMIND_APOCALYPTIC_SAFETY_H */
