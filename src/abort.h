/*
 * This file is a part of the Sharemind framework.
 * Copyright (C) Cybernetica AS
 *
 * All rights are reserved. Reproduction in whole or part is prohibited
 * without the written consent of the copyright owner. The usage of this
 * code is subject to the appropriate license agreement.
 */

#ifndef SHAREMIND_ABORT_H
#define SHAREMIND_ABORT_H

#include <stdio.h>
#include <stdlib.h>

#ifndef NDEBUG
#define SHAREMIND_ABORT__ \
    do { \
        fprintf(stderr, " in %s:%d\n", __FILE__, __LINE__); \
        abort(); \
    } while (false)
#else
#define SHAREMIND_ABORT__ \
    do { \
        abort(); \
    } while (false)
#endif

#define SHAREMIND_ABORT(...) \
    do { \
        fprintf(stderr, __VA_ARGS__); \
        SHAREMIND_ABORT__; \
    } while (false)

#endif /* SHAREMIND_ABORT_H */
