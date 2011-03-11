#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <iostream>
#include <stdint.h>
#include <string>
#include "Register.h"


typedef void* Inst;

#define VM_1T0(tuple) BOOST_PP_TUPLE_ELEM(1, 0, tuple)
#define VM_2T0(tuple) BOOST_PP_TUPLE_ELEM(2, 0, tuple)
#define VM_2T1(tuple) BOOST_PP_TUPLE_ELEM(2, 1, tuple)

#define VM_BINARY_UINT32_IMOP_DECLARE(unused,unused2,imop) \
    ((BOOST_PP_CAT(BOOST_PP_CAT(__,        imop),__uint32__uint32))) \
    ((BOOST_PP_CAT(BOOST_PP_CAT(__,        imop),__uint32__r_uint32))) \
    ((BOOST_PP_CAT(BOOST_PP_CAT(__,        imop),__uint32__cr_uint32))) \
    ((BOOST_PP_CAT(BOOST_PP_CAT(__,        imop),__r_uint32__uint32))) \
    ((BOOST_PP_CAT(BOOST_PP_CAT(__,        imop),__r_uint32__r_uint32))) \
    ((BOOST_PP_CAT(BOOST_PP_CAT(__,        imop),__r_uint32__cr_uint32))) \
    ((BOOST_PP_CAT(BOOST_PP_CAT(uint32__,  imop),__uint32__uint32))) \
    ((BOOST_PP_CAT(BOOST_PP_CAT(uint32__,  imop),__uint32__r_uint32))) \
    ((BOOST_PP_CAT(BOOST_PP_CAT(uint32__,  imop),__uint32__cr_uint32))) \
    ((BOOST_PP_CAT(BOOST_PP_CAT(uint32__,  imop),__r_uint32__uint32))) \
    ((BOOST_PP_CAT(BOOST_PP_CAT(uint32__,  imop),__r_uint32__r_uint32))) \
    ((BOOST_PP_CAT(BOOST_PP_CAT(uint32__,  imop),__r_uint32__cr_uint32))) \
    ((BOOST_PP_CAT(BOOST_PP_CAT(uint32__,  imop),__cr_uint32__uint32))) \
    ((BOOST_PP_CAT(BOOST_PP_CAT(uint32__,  imop),__cr_uint32__r_uint32))) \
    ((BOOST_PP_CAT(BOOST_PP_CAT(uint32__,  imop),__cr_uint32__cr_uint32))) \
    ((BOOST_PP_CAT(BOOST_PP_CAT(r_uint32__,imop),__uint32__uint32))) \
    ((BOOST_PP_CAT(BOOST_PP_CAT(r_uint32__,imop),__uint32__r_uint32))) \
    ((BOOST_PP_CAT(BOOST_PP_CAT(r_uint32__,imop),__uint32__cr_uint32))) \
    ((BOOST_PP_CAT(BOOST_PP_CAT(r_uint32__,imop),__r_uint32__uint32))) \
    ((BOOST_PP_CAT(BOOST_PP_CAT(r_uint32__,imop),__r_uint32__r_uint32))) \
    ((BOOST_PP_CAT(BOOST_PP_CAT(r_uint32__,imop),__r_uint32__cr_uint32))) \
    ((BOOST_PP_CAT(BOOST_PP_CAT(r_uint32__,imop),__cr_uint32__uint32))) \
    ((BOOST_PP_CAT(BOOST_PP_CAT(r_uint32__,imop),__cr_uint32__r_uint32))) \
    ((BOOST_PP_CAT(BOOST_PP_CAT(r_uint32__,imop),__cr_uint32__cr_uint32)))

#define VM_BINARY_UINT32_IMOPS
/*
#define VM_BINARY_UINT32_IMOPS \
    (add) \
    (sub) \
    (mul) \
    (div) \
    (mod)
*/

#define VM_IMOPS \
    BOOST_PP_SEQ_FOR_EACH(VM_BINARY_UINT32_IMOP_DECLARE, _, VM_BINARY_UINT32_IMOPS)

#define VM_FOR_EACH_IMOP(macro) BOOST_PP_SEQ_FOR_EACH(macro, _, VM_IMOPS)

#define VM_IMOP_DECL(unused,unused2,imop) \
    && BOOST_PP_CAT(label__,VM_1T0(imop)),

#define VM_IMOP_IMPL(unused,unused2,imop) \
    BOOST_PP_CAT(label__,VM_1T0(imop)): \
        BOOST_PP_CAT(VM_IMOP_IMPL_,VM_1T0(imop)); \
        goto *ip++;


class VirtualMachine {

public: /* Methods: */

    VirtualMachine();

    int run();

    const std::string &errorString() const;
    inline ptrdiff_t errorOffset() const { return m_ip - m_codeStart; }

private: /* Fields: */

    const uint8_t *m_codeStart;
    const uint8_t *m_codeEnd;
    const uint8_t *m_ip;

};

namespace {
    const std::string VM_ERROR_NONE = "No error";
}

VirtualMachine::VirtualMachine() {
    // Intentionally empty
}

int VirtualMachine::run() {
    /*
      static const int array[] = {
        &&doStuff - &&startProgram,
        &&endProgram - &&startProgram,
      };
    */
    static Inst imops[] = { VM_FOR_EACH_IMOP(VM_IMOP_DECL) 0 };

    //static void *code = 

    // Translate the instructions in the code:
    Inst programm[] = { &&endProgram };

    Inst *ip = programm;
    startProgram:
      goto **ip++;

    VM_FOR_EACH_IMOP(VM_IMOP_IMPL)

    endProgram:
      return 0;
}

const std::string &VirtualMachine::errorString() const {
    return VM_ERROR_NONE;
}

#include <cstdlib>

using namespace std;

int main() {
    VirtualMachine vm;

    int r = vm.run();
    if (r != 0) {
        cout << "Exception at " << vm.errorOffset()
             << ": " << vm.errorString() << endl;
        return EXIT_FAILURE;
    }
    return EXIT_FAILURE;
}
