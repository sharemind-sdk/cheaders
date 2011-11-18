/*
 * This file is a part of the Sharemind framework.
 * Copyright (C) Cybernetica AS
 *
 * All rights are reserved. Reproduction in whole or part is prohibited
 * without the written consent of the copyright owner. The usage of this
 * code is subject to the appropriate license agreement.
 */

#ifndef SHAREMIND_STATIC_ASSERT_H
#define SHAREMIND_STATIC_ASSERT_H

#define SM_STATIC_ASSERT_CAT2(a,b) a ## b
#define SM_STATIC_ASSERT_CAT(a,b) SM_STATIC_ASSERT_CAT2(a,b)
#define SM_STATIC_ASSERT(cond) typedef char SM_STATIC_ASSERT_CAT(static_assertion_,__COUNTER__)[(cond) ? 1 : -1]

#endif /* SHAREMIND_STATIC_ASSERT */
