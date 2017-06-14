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

SET(CPACK_PACKAGE_VERSION_MAJOR "0")
SET(CPACK_PACKAGE_VERSION_MINOR "1")
SET(CPACK_PACKAGE_VERSION_PATCH "0")
SET(CHEADERS_VERSION
    "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}.0")
SET(CHEADERS_COMPAT_VERSION "0.1.0.0")

INCLUDE("${CMAKE_CURRENT_SOURCE_DIR}/config.local" OPTIONAL)
INCLUDE("${CMAKE_CURRENT_BINARY_DIR}/config.local" OPTIONAL)

FIND_PACKAGE(Boost REQUIRED)

FILE(GLOB_RECURSE SHAREMIND_CHEADERS_HEADERS
     "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")
ADD_CUSTOM_TARGET("include_SharemindCHeaders_headers_in_IDE"
                  SOURCES ${SHAREMIND_CHEADERS_HEADERS})

INSTALL(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/"
        DESTINATION "include/sharemind")

# Install cmake files:
FILE(GLOB_RECURSE sharemind_cheaders_in_files
     "${CMAKE_CURRENT_SOURCE_DIR}/*.in")
ADD_CUSTOM_TARGET("include_sharemind_cheaders_in_files_in_IDE"
                  SOURCES ${sharemind_cheaders_in_files})
SET(CHEADERS_INSTALL_DEFINITIONS "-pthread")
SET(CHEADERS_INSTALL_LINK_LIBRARIES "-lpthread")
SET(CHEADERS_INSTALL_INCLUDE_DIRS
    ${Boost_INCLUDE_DIRS}
    "${CMAKE_INSTALL_PREFIX}/include"
)
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


# Packaging:
SET(CPACK_PACKAGE_VENDOR "Cybernetica AS")
SET(CPACK_PACKAGE_CONTACT "Sharemind packaging <sharemind-packaging@cyber.ee>")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "C development headers for Sharemind")
SET(CPACK_GENERATOR "DEB")
SET(CPACK_DEBIAN_PACKAGE_NAME "libsharemind-cheaders-dev")
SET(CPACK_DEBIAN_PACKAGE_RELEASE "cyber1")
SET(CPACK_DEBIAN_COMPRESSION_TYPE "xz")
SET(CPACK_DEBIAN_PACKAGE_DEPENDS
    "libboost-dev (>= 1.5.5), libc6-dev (>= 2.19), libgcc-4.8-dev | libgcc-4.9-dev | libgcc-5-dev | libgcc-6-dev | libgcc-7-dev")
SET(CPACK_DEBIAN_PACKAGE_SECTION "libdevel")
SET(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "any")
SET(CPACK_DEBIAN_FILE_NAME "DEB-DEFAULT")
INCLUDE(CPack)
