#
# Copyright (C) 2015 Cybernetica
#
# Research/Commercial License Usage
# Licensees holding a valid Research License or Commercial License
# for the Software may use this file according to the written
# agreement between you and Cybernetica.
#
# GNU General Public License Usage
# Alternatively, this file may be used under the terms of the GNU
# General Public License version 3.0 as published by the Free Software
# Foundation and appearing in the file LICENSE.GPL included in the
# packaging of this file.  Please review the following information to
# ensure the GNU General Public License version 3.0 requirements will be
# met: http://www.gnu.org/copyleft/gpl-3.0.html.
#
# For further information, please contact us at sharemind@cyber.ee.
#

CMAKE_MINIMUM_REQUIRED(VERSION "2.8.12")
PROJECT(SHAREMIND_CHEADERS "C")
SET(CHEADERS_VERSION "0.1.0.0")
SET(CHEADERS_COMPAT_VERSION "0.1.0.0")

INCLUDE("${CMAKE_CURRENT_SOURCE_DIR}/config.local" OPTIONAL)
INCLUDE("${CMAKE_CURRENT_BINARY_DIR}/config.local" OPTIONAL)

FIND_PACKAGE(Boost REQUIRED)

FILE(GLOB_RECURSE SHAREMIND_CHEADERS_HEADERS
     "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")
ADD_CUSTOM_TARGET("include_SharemindCHeaders_headers_in_IDE"
                  SOURCES ${SHAREMIND_CHEADERS_HEADERS})

INSTALL(FILES ${SHAREMIND_CHEADERS_HEADERS}
        DESTINATION "include/sharemind")

# Install cmake files:
FILE(GLOB_RECURSE sharemind_cheaders_in_files
     "${CMAKE_CURRENT_SOURCE_DIR}/*.in")
ADD_CUSTOM_TARGET("include_sharemind_cheaders_in_files_in_IDE"
                  SOURCES ${sharemind_cheaders_in_files})
SET(CHEADERS_INSTALL_DEFINITIONS "")
SET(CHEADERS_INSTALL_LINK_LIBRARIES "")
SET(CHEADERS_INSTALL_INCLUDE_DIRS "${CMAKE_INSTALL_PREFIX}/include")
CONFIGURE_FILE(
    "${CMAKE_CURRENT_SOURCE_DIR}/SharemindCHeadersConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/SharemindCHeadersConfig.cmake" @ONLY)
CONFIGURE_FILE(
    "${CMAKE_CURRENT_SOURCE_DIR}/SharemindCHeadersConfigVersion.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/SharemindCHeadersConfigVersion.cmake" @ONLY)
INSTALL(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/SharemindCHeadersConfig.cmake"
          "${CMAKE_CURRENT_BINARY_DIR}/SharemindCHeadersConfigVersion.cmake"
    DESTINATION "lib/SharemindCHeaders")
