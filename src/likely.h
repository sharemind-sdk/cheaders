/*
 * This file is a part of the Sharemind framework.
 * Copyright (C) Cybernetica AS
 *
 * All rights are reserved. Reproduction in whole or part is prohibited
 * without the written consent of the copyright owner. The usage of this
 * code is subject to the appropriate license agreement.
 */

#ifndef SHAREMIND_LIKELY_H
#define SHAREMIND_LIKELY_H

#ifdef __GNUC__
#define likely(c)   __builtin_expect(!!(c), 1)
#define unlikely(c) __builtin_expect(!!(c), 0)
#else
#define likely(c)   !!(c)
#define unlikely(c) !!(c)
#endif

#endif /* SHAREMIND_LIKELY_H */

