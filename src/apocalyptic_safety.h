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
