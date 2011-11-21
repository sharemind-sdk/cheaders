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

#ifdef _SHAREMIND_INTERNAL
#define ICONST
#else
#define ICONST const
#endif


/*******************************************************************************
  OVERALL MODULE LEVEL
*******************************************************************************/

/** Possible return codes returned by the Sharemind module initializer */
typedef enum {
    SMVM_MODAPI_0x1_IC_OK = 0,
    SMVM_MODAPI_0x1_IC_OUT_OF_MEMORY,
    SMVM_MODAPI_0x1_IC_ERROR
} SMVM_MODAPI_0x1_Initializer_Code;

/** Environment passed to a Sharemind module initializer and deinitializer: */
typedef struct {

    /**
      A handle for module instance data. Inside SMVM_syscall_context and others,
      this handle is also passed to facilities provided by this module.
    */
    void * moduleHandle;

    /* OTHER STUFF, for example something like: */
    /* void (*log)(
        SMVM_MODAPI_0x1_Module_Context * context,
        const char * message); */

    /** Internal pointer, do not use! */
    ICONST void * ICONST internal;

} SMVM_MODAPI_0x1_Module_Context;

/** Module initializer function signature: */
typedef SMVM_MODAPI_0x1_Initializer_Code (*SMVM_MODAPI_0x1_Module_Initializer)(SMVM_MODAPI_0x1_Module_Context * c);

/** Module deinitializer function signature: */
typedef void (*SMVM_MODAPI_0x1_Module_Deinitializer)(SMVM_MODAPI_0x1_Module_Context * c);


/*******************************************************************************
  SYSTEM CALLS
*******************************************************************************/

/** Mutable references */
typedef struct {

    /** Pointer to referenced data. */
    void * ICONST pData;

    /** Size of referenced data. */
    ICONST size_t size;

    /** Internal pointer, do not use! */
    ICONST void * ICONST internal;

} SMVM_MODAPI_0x1_Reference;

/** Constant references */
typedef struct {

    /** Pointer to referenced data. */
    const void * ICONST pData;

    /** Size of referenced data. */
    ICONST size_t size;

    /** Internal pointer, do not use! */
    ICONST void * ICONST internal;

} SMVM_MODAPI_0x1_CReference;

/** Possible return codes returned by system calls */
typedef enum {
    SMVM_MODAPI_0x1_SC_OK = 0x00,
    SMVM_MODAPI_0x1_SC_OUT_OF_MEMORY = 0x01,
    SMVM_MODAPI_0x1_SC_INVALID_CALL = 0x02
} SMVM_MODAPI_0x1_Syscall_Code;

/** Additional context provided for system calls: */
struct _SMVM_MODAPI_0x1_Syscall_Context;
typedef struct _SMVM_MODAPI_0x1_Syscall_Context SMVM_MODAPI_0x1_Syscall_Context;
struct _SMVM_MODAPI_0x1_Syscall_Context {

    /**
      A handle to the private data of the module instance. This is the same
      handle as provided to SMVM_MODAPI_0x1_Module_Context on module
      initialization.
    */
    void * moduleHandle;

    /** Access to public dynamic memory inside the VM process: */
    uint64_t (* ICONST publicAlloc)(size_t nBytes, SMVM_MODAPI_0x1_Syscall_Context * c);
    int (* ICONST publicFree)(uint64_t ptr, SMVM_MODAPI_0x1_Syscall_Context * c);
    size_t (* ICONST publicMemPtrSize)(uint64_t ptr, SMVM_MODAPI_0x1_Syscall_Context * c);
    void * (* ICONST publicMemPtrData)(uint64_t ptr, SMVM_MODAPI_0x1_Syscall_Context * c);

    /** Access to dynamic memory not exposed to VM instructions: */
    void * (* ICONST allocPrivate)(size_t nBytes, SMVM_MODAPI_0x1_Syscall_Context * c);
    int (* ICONST freePrivate)(void * ptr, SMVM_MODAPI_0x1_Syscall_Context * c);

    /**
      Used to get access to internal data of protection domain per-process data
      (see below for pdProcessHandle):
    */
    void * (* ICONST get_pd_process_handle)(uint64_t pd_index, SMVM_MODAPI_0x1_Syscall_Context * p);

    /* OTHER STUFF */

    /** Internal pointer, do not use! */
    ICONST void * ICONST internal;

};

/** System call function signature: */
typedef SMVM_MODAPI_0x1_Syscall_Code (* SMVM_MODAPI_0x1_Syscall)(
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

    /** Additional context: */
    SMVM_MODAPI_0x1_Syscall_Context * c
);

/** System call list item:*/
typedef const struct {

    /** Unique name of the system call: */
    const char * const name;

    /** Pointer to the system call implementation: */
    const SMVM_MODAPI_0x1_Syscall syscall_f;

} SMVM_MODAPI_0x1_Syscall_Definition;

/** System call list: */
typedef SMVM_MODAPI_0x1_Syscall_Definition SMVM_MODAPI_0x1_Syscall_Definitions[];


/*******************************************************************************
  PROTECTION DOMAINS
*******************************************************************************/

/** Protection domain configuration */
typedef struct {

    /** The unique name of the protection domain. */
    const char * ICONST pd_name;

    /** The name of the protection domain kind. */
    const char * ICONST pd_kind;

    /** The protection domain configuration string. */
    const char * ICONST pd_conf_string;

} SMVM_MODAPI_0x1_PD_Conf;

/** Protection-domain instance specific data wrapper. */
typedef struct {

    /** A handle for protection domain data. */
    void * pdHandle;

    /**
      A handle to the private data of the module instance. This is the same
      handle as provided to SMVM_MODAPI_0x1_Module_Context on module
      initialization.
    */
    void * ICONST moduleHandle;

    /** A handle to the configuration of the protection domain. */
    const SMVM_MODAPI_0x1_PD_Conf * ICONST conf;

    /* OTHER STUFF */

    /** Internal pointer, do not use! */
    ICONST void * ICONST internal;

} SMVM_MODAPI_0x1_PD_Wrapper;

/** Protection-domain instance process instance specific data wrapper. */
typedef struct {

    /** A handle for protection domain per-process data. */
    void * pdProcessHandle;

    /**
      A handle for protection domain instance data. This is the same handle as
      provided to SMVM_MODAPI_0x1_PD_Wrapper on protection domain initialization.
    */
    void * ICONST pdHandle;

    /**
      A handle to the private data of the module instance. This is the same
      handle as provided to SMVM_MODAPI_0x1_Module_Context on module
      initialization.
    */
    void * ICONST moduleHandle;

    /** A handle to the configuration of the protection domain. */
    const SMVM_MODAPI_0x1_PD_Conf * ICONST conf;

    /* OTHER STUFF */

    /** Internal pointer, do not use! */
    ICONST void * ICONST internal;

} SMVM_MODAPI_0x1_PD_Process_Wrapper;

/** Protection domain initialization function signature */
typedef int (* SMVM_MODAPI_0x1_PD_Startup)(SMVM_MODAPI_0x1_PD_Wrapper *);

/** Protection domain deinitialization function signature */
typedef void (* SMVM_MODAPI_0x1_PD_Shutdown)(SMVM_MODAPI_0x1_PD_Wrapper *);

/** Protection domain process initialization function signature */
typedef int (* SMVM_MODAPI_0x1_PD_Process_Startup)(SMVM_MODAPI_0x1_PD_Process_Wrapper *);

/** Protection domain process deinitialization function signature */
typedef void (* SMVM_MODAPI_0x1_PD_Process_Shutdown)(SMVM_MODAPI_0x1_PD_Process_Wrapper *);

/** Protection domain kind list item: */
typedef const struct {

    /** Unique name of the protection domain kind: */
    const char * const name;

    /** Pointer to the protection domain initialization implementation: */
    const SMVM_MODAPI_0x1_PD_Startup pd_startup_f;

    /** Pointer to the protection domain deinitialization implementation: */
    const SMVM_MODAPI_0x1_PD_Shutdown pd_shutdown_f;

    /** Pointer to the protection domain process initialization implementation: */
    const SMVM_MODAPI_0x1_PD_Process_Startup pd_process_startup_f;

    /** Pointer to the protection domain process deinitialization implementation: */
    const SMVM_MODAPI_0x1_PD_Process_Shutdown pd_process_shutdown_f;

} SMVM_MODAPI_0x1_PDK_Definition;

/** Protection domain kind list: */
typedef SMVM_MODAPI_0x1_PDK_Definition SMVM_MODAPI_0x1_PDK_Definitions[];


#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* SHAREMIND_MODAPI_0x1_H */
