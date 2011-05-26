#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "preprocessor.h"
#include "vm.h"


int main() {
    const uint64_t nopHalt[] = {
        SVM_MAKE_UINT64(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00), // NOP
        SVM_MAKE_UINT64(0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00), // HALT
        SVM_MAKE_UINT64(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff)  // return code (255)
    };
    struct SVM_Program * p = SVM_Program_new(1);
    if (!p) {
        printf("Failed to allocate program!\n");
        goto fail;
    }
    if (SVM_Program_addCodeSection(p, nopHalt, 3) != SVM_OK) {
        printf("Failed to add code section!\n");
        goto failAndFreeProgram;
    }
    if (SVM_Program_endPrepare(p) != SVM_OK) {
        printf("Failed to prepare program!\n");
        goto failAndFreeProgram;
    }
    if (SVM_Program_run(p) != SVM_OK) {
        printf("Failed to run program!\n");
        goto failAndFreeProgram;
    }
    assert(sizeof(long long int) == sizeof(int64_t));
    printf("Program returned status: %lld\n", p->returnValue);
    SVM_Program_free(p);
    return 0;

failAndFreeProgram:
    SVM_Program_free(p);
fail:
    return EXIT_FAILURE;
}
