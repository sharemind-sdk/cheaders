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

#include "libsmvm/syscall.h"
#include "modapi.h"


#ifdef __cplusplus
extern "C" {
#endif

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
    const SMVM_syscall_f function_handle;
} SMVM_MODAPI_0x1_Syscall;


#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* SHAREMIND_MODAPI_0x1_H */
