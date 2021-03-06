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

#ifndef SHAREMIND_CLANGVERSION_H
#define SHAREMIND_CLANGVERSION_H

#include "detail/CompilerVersionPrelude.h"


#if !defined(SHAREMIND_COMPILER_TYPE_) && defined(__clang__)
#define SHAREMIND_COMPILER_TYPE_ SHAREMIND_COMPILER_TYPE_CLANG_
#define SHAREMIND_CLANG_VERSION \
    (((__clang_major__ * 100) + __clang_minor__) * 100 + __clang_patchlevel__)
#endif

#endif /* SHAREMIND_CLANGVERSION_H */
