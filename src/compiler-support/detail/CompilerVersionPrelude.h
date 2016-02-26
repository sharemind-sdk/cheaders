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

#ifndef SHAREMIND_COMPILERSUPPORT_COMPILERVERSIONPRELUDE_H
#define SHAREMIND_COMPILERSUPPORT_COMPILERVERSIONPRELUDE_H

#define SHAREMIND_COMPILER_TYPE_GCC_     1
#define SHAREMIND_COMPILER_TYPE_CLANG_   2

#if defined(SHAREMIND_FORCE_GCC)
    #define SHAREMIND_COMPILER_TYPE_ SHAREMIND_COMPILER_TYPE_GCC_
    #define SHAREMIND_GCC_VERSION SHAREMIND_FORCE_GCC
#elif defined(SHAREMIND_FORCE_CLANG)
    #ifdef SHAREMIND_COMPILER_TYPE_
        #error Multiple SHAREMIND_FORCE_<COMPILER> options defined!
    #endif
    #define SHAREMIND_COMPILER_TYPE_ SHAREMIND_COMPILER_TYPE_CLANG_
    #define SHAREMIND_CLANG_VERSION SHAREMIND_FORCE_CLANG
#endif

#endif
