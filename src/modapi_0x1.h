/*
 * This file is a part of the Sharemind framework.
 * Copyright (C) Cybernetica AS
 *
 * All rights are reserved. Reproduction in whole or part is prohibited
 * without the written consent of the copyright owner. The usage of this
 * code is subject to the appropriate license agreement.
 */
#ifndef SHAREMIND_MODAPI_0x1_H
#define SHAREMIND_MODAPI_0x1_H

#include <stddef.h>
#include <stdint.h>
#include "codeblock.h"
#include "modapi.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    void * pData;
    size_t size;
} SMVM_MODAPI_0x1_Reference;
typedef struct {
    const void * pData;
    size_t size;
} SMVM_MODAPI_0x1_CReference;

typedef enum {
    SMVM_MODAPI_0x1_E_NONE = 0x00,
    SMVM_MODAPI_0x1_E_OUT_OF_MEMORY = 0x01,
    SMVM_MODAPI_0x1_E_INVALID_CALL = 0x02
} SMVM_MODAPI_0x1_Syscall_Exception;

/** Additional context provided for system calls: */
struct _SMVM_MODAPI_0x1_Syscall_Context;
typedef struct _SMVM_MODAPI_0x1_Syscall_Context SMVM_MODAPI_0x1_Syscall_Context;
struct _SMVM_MODAPI_0x1_Syscall_Context {
    /**
      A handle to the private data of the module instance. This is the same
      handle as provided to SMVM_module_context on module initialization.
    */
    void * const moduleHandle;

    /** Access to public dynamic memory inside the VM process: */
    uint64_t (* const publicAlloc)(size_t nBytes, SMVM_MODAPI_0x1_Syscall_Context * c);
    int (* const publicFree)(uint64_t ptr, SMVM_MODAPI_0x1_Syscall_Context * c);
    size_t (* const publicMemPtrSize)(uint64_t ptr, SMVM_MODAPI_0x1_Syscall_Context * c);
    void * (* const publicMemPtrData)(uint64_t ptr, SMVM_MODAPI_0x1_Syscall_Context * c);

    /** Access to dynamic memory not exposed to VM instructions: */
    void * (* const allocPrivate)(size_t nBytes, SMVM_MODAPI_0x1_Syscall_Context * c);
    int (* const freePrivate)(void * ptr, SMVM_MODAPI_0x1_Syscall_Context * c);

    /**
      Used to get access to internal data of protection domain per-process data
      (see below for pdProcessHandle):
    */
    void * (* const get_pd_process_handle)(uint64_t pd_index,
                                           SMVM_MODAPI_0x1_Syscall_Context * p);

    /* OTHER STUFF */
};

typedef SMVM_MODAPI_0x1_Syscall_Exception (* SMVM_MODAPI_0x1_Syscall)(
    /** Arguments passed to syscall: */
    SMVM_CodeBlock * args,
    size_t num_args,

    /** Mutable references passed to syscall: */
    const SMVM_MODAPI_0x1_Reference * refs,
    size_t num_refs,

    /** Immutable references passed to syscall: */
    const SMVM_MODAPI_0x1_CReference * crefs,
    size_t num_crefs,

    /**
      The pointer to where the return value of the syscall resides, or NULL if
      no return value is expected:
    */
    SMVM_CodeBlock * returnValue,

    SMVM_MODAPI_0x1_Syscall_Context * c
);

typedef enum {
    SMVM_MODAPI_0x1_OK = 0,
    SMVM_MODAPI_0x1_OUT_OF_MEMORY,
    SMVM_MODAPI_0x1_ERROR
} SMVM_MODAPI_0x1_Code;

/** Environment passed to a Sharemind module: */
struct _SMVM_MODAPI_0x1_Module_Context;
typedef struct _SMVM_MODAPI_0x1_Module_Context SMVM_MODAPI_0x1_Module_Context;
struct _SMVM_MODAPI_0x1_Module_Context {

    /**
      A handle for module instance data. Inside SMVM_syscall_context and others,
      this handle is also passed to facilities provided by this module.
    */
    void * moduleHandle;

    /* OTHER STUFF, for example something like: */
    /* void (*log)(
        SMVM_MODAPI_0x1_Module_Context * context,
        const char * message); */

};

/** Module initializer signature: */
typedef SMVM_MODAPI_0x1_Code (*SMVM_MODAPI_0x1_Module_Initializer)(SMVM_MODAPI_0x1_Module_Context * c);

/** Module deinitializer signature: */
typedef void (*SMVM_MODAPI_0x1_Module_Deinitializer)(SMVM_MODAPI_0x1_Module_Context * c);

/** System call list item:*/
typedef const struct {
    const char * const name;
    const SMVM_MODAPI_0x1_Syscall function_handle;
} SMVM_MODAPI_0x1_Syscall_Definition;


#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* SHAREMIND_MODAPI_0x1_H */
