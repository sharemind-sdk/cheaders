#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "instr.h"
#include "likely.h"
#include "preprocessor.h"
#include "vm.h"

void printCodeSection(const uint64_t * code, size_t size, const char * linePrefix) {
    size_t skip = 0;
    for (size_t i = 0u; i < size; i++) {
        printf("%s", linePrefix);
        uint8_t * b = (uint8_t *) &code[i];
        printf("%02x%02x %02x%02x %02x%02x %02x%02x",
               b[0], b[1], b[2], b[3], b[4], b[5], b[6], b[7]);

        if (!skip) {
            const char * name = SVM_Instruction_name(code[i]);
            printf("  %s", name ? name : "!!! UNKNOWN INSTRUCTION OR DATA !!!");

            if (name)
                skip = SVM_Instruction_args(code[i]);
        } else {
            skip--;
        }

        printf("\n");
    }
}

int main() {

    const uint64_t program[] = {
            SVM_MAKE_INSTR(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00), // NOP
            SVM_MAKE_INSTR(0x00,0x02,0x08,0x00,0x00,0x00,0x00,0x00), // COMMON.PROC.RESIZESTACK
        SVM_MAKE_UINT64_LE(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0a), //   10 slots
            SVM_MAKE_INSTR(0x00,0x01,0x01,0x02,0xff,0x00,0x00,0x00), // COMMON.MOV imm reg allbytes toOffsetZero
        SVM_MAKE_UINT64_LE(0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00), //   256
        SVM_MAKE_UINT64_LE(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x09), //   9
            SVM_MAKE_INSTR(0x00,0x01,0x01,0x03,0xff,0x00,0x00,0x00), // COMMON.MOV imm stack allbytes toOffsetZero
        SVM_MAKE_UINT64_LE(0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01), //   257
        SVM_MAKE_UINT64_LE(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x09), //   8
            SVM_MAKE_INSTR(0x00,0x02,0x04,0x01,0x00,0x00,0x00,0x00), // COMMON.PROC.PUSH imm
        SVM_MAKE_UINT64_LE(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff), //   255
            SVM_MAKE_INSTR(0x00,0x02,0x04,0x02,0x00,0x00,0x00,0x00), // COMMON.PROC.PUSH reg
        SVM_MAKE_UINT64_LE(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x09), //   9
            SVM_MAKE_INSTR(0x00,0x02,0x04,0x03,0x00,0x00,0x00,0x00), // COMMON.PROC.PUSH stack
        SVM_MAKE_UINT64_LE(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x09), //   8
        //    SVM_MAKE_INSTR(0x00,0x02,0x04,0x02,0x00,0x00,0x00,0x00), // COMMON.PROC.PUSH reg
        //SVM_MAKE_UINT64_LE(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10), //   10
            SVM_MAKE_INSTR(0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00), // HALT
        SVM_MAKE_UINT64_LE(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff), //   255
    };

    /* Print code section: */
    printf("Code section 0:\n");
    printCodeSection(program, sizeof(program) / sizeof(uint64_t), "  ");
    printf("\n");

    struct SVM_Program * p = SVM_Program_new();
    if (unlikely(!p)) {
        fputs("Failed to allocate program!\n", stderr);
        goto main_fail_1;
    }

    enum SVM_Error e = SVM_Program_addCodeSection(p, program, sizeof(program) / sizeof(uint64_t));
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
    printf("Program returned status: %ld\n", p->returnValue);
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
