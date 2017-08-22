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
PROJECT(SharemindCHeaders VERSION "0.1.0" LANGUAGES "C")

INCLUDE("${CMAKE_CURRENT_SOURCE_DIR}/config.local" OPTIONAL)
INCLUDE("${CMAKE_CURRENT_BINARY_DIR}/config.local" OPTIONAL)

FIND_PACKAGE(SharemindCMakeHelpers REQUIRED)

SharemindSetProjectVersion()
SET(SharemindCHeaders_COMPAT_VERSION "${SharemindCHeaders_VERSION}")

FIND_PACKAGE(Boost REQUIRED)

FILE(GLOB_RECURSE SHAREMIND_CHEADERS_HEADERS
     "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")
ADD_CUSTOM_TARGET("include_SharemindCHeaders_headers_in_IDE"
                  SOURCES ${SHAREMIND_CHEADERS_HEADERS})

INSTALL(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/"
        DESTINATION "include/sharemind"
        COMPONENT "dev")


# Install cmake files:
SET(SharemindCHeaders_INSTALL_DEFINITIONS "-pthread")
SET(SharemindCHeaders_INSTALL_LINK_LIBRARIES "-lpthread")
SET(SharemindCHeaders_INSTALL_INCLUDE_DIRS
    ${Boost_INCLUDE_DIRS}
    "${CMAKE_INSTALL_PREFIX}/include"
)
SharemindUseCMakeFindFiles()


# Packaging:
SharemindSetupPackaging()
SharemindAddComponentPackage("dev"
    NAME "libsharemind-cheaders-dev"
    DESCRIPTION "C development headers for Sharemind"
    DEB_SECTION "libdevel"
    DEB_DEPENDS
        "libboost-dev (>= 1.5.5)"
        "libc6-dev (>= 2.19)"
        "libgcc-4.8-dev | libgcc-4.9-dev | libgcc-5-dev | libgcc-6-dev | libgcc-7-dev"
)
SharemindPackagingFinalize()
