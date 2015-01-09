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
