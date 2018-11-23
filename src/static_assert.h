/*
 * Copyright (C) 2015 Cybernetica
 *
 * Research/Commercial License Usage
 * Licensees holding a valid Research License or Commercial License
 * for the Software may use this file according to the written
 * agreement between you and Cybernetica.
 *
 * GNU General Public License Usage
 * Alternatively, this file may be used under the terms of the GNU
 * General Public License version 3.0 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.  Please review the following information to
 * ensure the GNU General Public License version 3.0 requirements will be
 * met: http://www.gnu.org/copyleft/gpl-3.0.html.
 *
 * For further information, please contact us at sharemind@cyber.ee.
 */

#ifndef SHAREMIND_STATIC_ASSERT_H
#define SHAREMIND_STATIC_ASSERT_H

#ifdef __cplusplus

#if __cplusplus >= 201103L

#define SHAREMIND_STATIC_ASSERT(...) static_assert(__VA_ARGS__, #__VA_ARGS__)

#else

#include <boost/static_assert.hpp>
#define SHAREMIND_STATIC_ASSERT(...) BOOST_STATIC_ASSERT(__VA_ARGS__)

#endif

#else

#if __STDC_VERSION__ >= 201112L

#define SHAREMIND_STATIC_ASSERT(...) _Static_assert(__VA_ARGS__, #__VA_ARGS__)

#else

#define SHAREMIND_STATIC_ASSERT_CAT2(a,b) a ## b
#define SHAREMIND_STATIC_ASSERT_CAT(a,b) SHAREMIND_STATIC_ASSERT_CAT2(a,b)
#define SHAREMIND_STATIC_ASSERT(cond) \
    typedef char SHAREMIND_STATIC_ASSERT_CAT(\
            static_assertion_,\
            __COUNTER__)[(cond) ? 1 : -1] __attribute__((unused))

#endif

#endif

#endif /* SHAREMIND_STATIC_ASSERT */
