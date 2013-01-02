#
# This file is a part of the Sharemind framework.
# Copyright (C) Cybernetica AS
#
# All rights are reserved. Reproduction in whole or part is prohibited
# without the written consent of the copyright owner. The usage of this
# code is subject to the appropriate license agreement.
#

CMAKE_MINIMUM_REQUIRED(VERSION "2.8")
PROJECT(SHAREMIND_VM_GLOBALS)

FIND_PACKAGE(Boost REQUIRED)

SET(SHAREMIND_VM_GLOBALS_HEADERS
    "codeblock.h"
    "likely.h"
    "preprocessor.h"
    "static_assert.h"
)

SET(SHAREMIND_VM_GLOBALS_HEADERS_P
    "fnv.h"
    "instrset.h"
    "map.h"
    "refs.h"
    "stack.h"
    "stringmap.h"
    "trie.h"
    "vector.h")

INSTALL(FILES ${SHAREMIND_VM_GLOBALS_HEADERS}
        DESTINATION "include/sharemind")
