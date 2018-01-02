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

#ifndef SHAREMIND_ENDIAN_H
#define SHAREMIND_ENDIAN_H

#ifdef __MACH__

#include <libkern/OSByteOrder.h>
#define htobe16(x) (OSSwapHostToBigInt16((x)))
#define htole16(x) (OSSwapHostToLittleInt16((x)))
#define be16toh(x) (OSSwapBigToHostInt16((x)))
#define le16toh(x) (OSSwapLittleToHostInt16((x)))
#define htobe32(x) (OSSwapHostToBigInt32((x)))
#define htole32(x) (OSSwapHostToLittleInt32((x)))
#define be32toh(x) (OSSwapBigToHostInt32((x)))
#define le32toh(x) (OSSwapLittleToHostInt32((x)))
#define htobe64(x) (OSSwapHostToBigInt64((x)))
#define htole64(x) (OSSwapHostToLittleInt64((x)))
#define be64toh(x) (OSSwapBigToHostInt64((x)))
#define le64toh(x) (OSSwapLittleToHostInt64((x)))

#elif defined(__FreeBSD__) && __FreeBSD__

#include <sys/endian.h>

#else

#include <endian.h>

#endif

#endif /* SHAREMIND_ENDIAN_MACROS_H */
