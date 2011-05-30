#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "likely.h"
#include "preprocessor.h"
#include "vm.h"


int main() {
    const uint64_t program[] = {
        SVM_MAKE_UINT64(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00), // NOP
        //SVM_MAKE_UINT64(0x00,0x02,0x08,0x00,0x00,0x00,0x00,0x00), // COMMON.PROC.RESIZESTACK
        //SVM_MAKE_UINT64(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff), // too much stack
        SVM_MAKE_UINT64(0x00,0x02,0x04,0x01,0x00,0x00,0x00,0x00), // COMMON.PROC.PUSH imm
        SVM_MAKE_UINT64(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff), // 255
        SVM_MAKE_UINT64(0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00), // HALT
        SVM_MAKE_UINT64(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff)  // return code (255)
    };

    struct SVM_Program * p = SVM_Program_new();
    if (unlikely(!p)) {
        fputs("Failed to allocate program!\n", stderr);
        goto main_fail_1;
    }

    enum SVM_Error e = SVM_Program_addCodeSection(p, program, 5);
    if (unlikely(e != SVM_OK)) {
        fputs("Failed to add code section!\n", stderr);
        goto main_print_e_and_fail_2;
    }

    e = SVM_Program_endPrepare(p);
    if (unlikely(e != SVM_OK)) {
        fputs("Failed to prepare program!\n", stderr);
        goto main_print_e_and_fail_2;
    }

    e = SVM_Program_run(p);
    if (unlikely(e != SVM_OK)) {
        fputs("Failed to run program!\n", stderr);
        goto main_print_e_and_fail_2;
    }

    assert(sizeof(long long int) == sizeof(int64_t));
    printf("Program returned status: %lld\n", p->returnValue);
    SVM_Program_free(p);

/* SUCCESS: */
    return EXIT_SUCCESS;

main_print_e_and_fail_2:
    fprintf(stderr, "Error code: %s\n", SVM_Error_toString(e));
    if (e == SVM_RUNTIME_EXCEPTION) {
        fprintf(stderr, "Exception %s\n", SVM_Exception_toString(p->exceptionValue));
    }

/* main_fail_2: */
    SVM_Program_free(p);

main_fail_1:
    return EXIT_FAILURE;
}
