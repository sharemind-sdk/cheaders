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

CMAKE_MINIMUM_REQUIRED(VERSION "3.0.0")
PROJECT(SharemindCHeaders VERSION "1.3.0" LANGUAGES "C")

INCLUDE("${CMAKE_CURRENT_SOURCE_DIR}/config.local" OPTIONAL)
INCLUDE("${CMAKE_CURRENT_BINARY_DIR}/config.local" OPTIONAL)

FIND_PACKAGE(SharemindCMakeHelpers 1.6 REQUIRED)

FIND_PACKAGE(Boost 1.62 REQUIRED)
FIND_PACKAGE(Threads REQUIRED)


# Find header files:
FILE(GLOB_RECURSE SHAREMIND_CHEADERS_HEADERS
     "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")
ADD_CUSTOM_TARGET("include_SharemindCHeaders_headers_in_IDE"
                  SOURCES ${SHAREMIND_CHEADERS_HEADERS})


# CHeaders:
SharemindAddInterfaceLibrary(CHeaders)
TARGET_COMPILE_DEFINITIONS(CHeaders INTERFACE "_BSD_SOURCE" "_DEFAULT_SOURCE")
TARGET_INCLUDE_DIRECTORIES(CHeaders
    INTERFACE
        # $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src> # TODO
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>
    )
TARGET_LINK_LIBRARIES(CHeaders INTERFACE Boost::boost Threads::Threads)
INSTALL(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/"
        DESTINATION "include/sharemind"
        COMPONENT "dev")
SharemindCreateCMakeFindFilesForTarget(CHeaders DEPENDENCIES Boost Threads)


# Packaging:
SharemindSetupPackaging()
SharemindAddComponentPackage("dev"
    NAME "libsharemind-cheaders-dev"
    DESCRIPTION "C development headers for Sharemind"
    DEB_SECTION "libdevel"
    DEB_DEPENDS
        "libboost-dev (>= 1.62)"
        "libc6-dev (>= 2.19)"
)
SharemindPackagingFinalize()
