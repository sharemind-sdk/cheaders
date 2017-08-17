/*
 * Copyright (C) 2017 Cybernetica
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

#ifndef SHAREMIND_NULL_H
#define SHAREMIND_NULL_H

#if !defined(__cplusplus)

#include <stddef.h>
#define SHAREMIND_NULL NULL

#else

#if __cplusplus >= 201103L
#define SHAREMIND_NULL nullptr
#else
#include <cstddef>
#define SHAREMIND_NULL NULL
#endif

#endif

#endif /* SHAREMIND_NULL_H */
