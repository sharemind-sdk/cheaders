#
# This file is a part of the Sharemind framework.
# Copyright (C) Cybernetica AS
#
# All rights are reserved. Reproduction in whole or part is prohibited
# without the written consent of the copyright owner. The usage of this
# code is subject to the appropriate license agreement.
#

FIND_PACKAGE(Boost)
IF(NOT Boost_FOUND)
    MESSAGE(FATAL_ERROR "Required Boost library headers not found!")
ENDIF(NOT Boost_FOUND)

IF(NOT SHAREMIND_INSTALL_INCLUDE_DIR)
    MESSAGE(FATAL_ERROR "SHAREMIND_INSTALL_INCLUDE_DIR not defined!")
ENDIF(NOT SHAREMIND_INSTALL_INCLUDE_DIR)

SET(SHAREMIND_VM_GLOBALS_PUBLIC "codeblock.h")

SET(SHAREMIND_VM_GLOBALS_PRIVATE
    "fnv.h"
    "instrset.h"
    "likely.h"
    "map.h"
    "refs.h"
    "preprocessor.h"
    "stack.h"
    "static_assert.h"
    "stringmap.h"
    "trie.h"
    "vector.h")

SET(OTHER_FILES ${OTHER_FILES} ${SHAREMIND_VM_GLOBALS_PUBLIC} ${SHAREMIND_VM_GLOBALS_PRIVATE})

MESSAGE(STATUS "Installable: ${SHAREMIND_VM_GLOBALS_PUBLIC}")
INSTALL(FILES ${SHAREMIND_VM_GLOBALS_PUBLIC}
        DESTINATION "${SHAREMIND_INSTALL_INCLUDE_DIR}/")
