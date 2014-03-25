#
# This file is a part of the Sharemind framework.
# Copyright (C) Cybernetica AS
#
# All rights are reserved. Reproduction in whole or part is prohibited
# without the written consent of the copyright owner. The usage of this
# code is subject to the appropriate license agreement.
#

CMAKE_MINIMUM_REQUIRED(VERSION "2.8")
PROJECT(SHAREMIND_VM_GLOBALS "C")

FIND_PACKAGE(Boost REQUIRED)

SET(SHAREMIND_VM_GLOBALS_HEADERS
    "codeblock.h"
    "fnv.h"
    "likely.h"
    "map.h"
    "mutex.h"
    "preprocessor.h"
    "recursivemutex.h"
    "refs.h"
    "stack.h"
    "static_assert.h"
    "stringmap.h"
    "trie.h"
    "vector.h")

ADD_CUSTOM_TARGET("include_SharemindVmGlobals_headers_in_IDE"
                  SOURCES ${SHAREMIND_VM_GLOBALS_HEADERS})

INSTALL(FILES ${SHAREMIND_VM_GLOBALS_HEADERS}
        DESTINATION "include/sharemind")

# Install cmake files:
FILE(GLOB_RECURSE sharemind_vmglobals_in_files "${CMAKE_CURRENT_SOURCE_DIR}/*.in")
ADD_CUSTOM_TARGET("include_sharemind_vmglobals_in_files_in_IDE" SOURCES ${sharemind_vmglobals_in_files})
SET(VM_GLOBALS_VERSION "0.1.0.0")
SET(VM_GLOBALS_INSTALL_DEFINITIONS "")
SET(VM_GLOBALS_INSTALL_LINK_LIBRARIES "")
SET(VM_GLOBALS_INSTALL_INCLUDE_DIRS "${CMAKE_INSTALL_PREFIX}/include")
CONFIGURE_FILE("${CMAKE_CURRENT_SOURCE_DIR}/SharemindVmGlobalsConfig.cmake.in"
               "${CMAKE_CURRENT_BINARY_DIR}/SharemindVmGlobalsConfig.cmake" @ONLY)
CONFIGURE_FILE("${CMAKE_CURRENT_SOURCE_DIR}/SharemindVmGlobalsConfigVersion.cmake.in"
               "${CMAKE_CURRENT_BINARY_DIR}/SharemindVmGlobalsConfigVersion.cmake" @ONLY)
INSTALL(FILES "${CMAKE_CURRENT_BINARY_DIR}/SharemindVmGlobalsConfig.cmake"
              "${CMAKE_CURRENT_BINARY_DIR}/SharemindVmGlobalsConfigVersion.cmake"
        DESTINATION "lib/SharemindVmGlobals")
