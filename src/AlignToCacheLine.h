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

#ifndef SHAREMIND_ALIGNTOCACHELINE_H
#define SHAREMIND_ALIGNTOCACHELINE_H

#include "CacheLineSize.h"


#if defined(__cplusplus) && (__cplusplus >= 201103L)
    #define SHAREMIND_ALIGN_TO_CACHE_SIZE alignas(SHAREMIND_CACHE_LINE_SIZE)
#elif !defined(__cplusplus) && defined(__STDC_VERSION__) \
      && (__STDC_VERSION__ >= 201112L)
    #define SHAREMIND_ALIGN_TO_CACHE_SIZE _Alignas(SHAREMIND_CACHE_LINE_SIZE)
#else
    #define SHAREMIND_ALIGN_TO_CACHE_SIZE \
        __attribute__((aligned(SHAREMIND_CACHE_LINE_SIZE)))
#endif

#endif /* SHAREMIND_ALIGNTOCACHELINE_H */
