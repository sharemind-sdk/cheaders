#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/for_each_product.hpp>
#include <iostream>
#include <stdint.h>
#include <string>
#include "Register.h"


typedef void* Inst;

#define  VM_CAT(a, b) BOOST_PP_CAT(a, b)
#define VM_CAT2(a, b) BOOST_PP_CAT(a, b)
#define VM_CAT3(a, b, c) VM_CAT(VM_CAT(a, b), c)
#define VM_CAT4(a, b, c, d) VM_CAT3(VM_CAT(a, b), c, d)
#define VM_CAT5(a, b, c, d, e) VM_CAT4(VM_CAT(a, b), c, d, e)
#define VM_CAT6(a, b, c, d, e, f) VM_CAT5(VM_CAT(a, b), c, d, e, f)
#define VM_CAT7(a, b, c, d, e, f, g) VM_CAT6(VM_CAT(a, b), c, d, e, f, g)

#define VM_1T0(tuple) BOOST_PP_TUPLE_ELEM(1, 0, tuple)
#define VM_2T0(tuple) BOOST_PP_TUPLE_ELEM(2, 0, tuple)
#define VM_2T1(tuple) BOOST_PP_TUPLE_ELEM(2, 1, tuple)
#define VM_3T0(tuple) BOOST_PP_TUPLE_ELEM(3, 0, tuple)
#define VM_3T1(tuple) BOOST_PP_TUPLE_ELEM(3, 1, tuple)
#define VM_3T2(tuple) BOOST_PP_TUPLE_ELEM(3, 2, tuple)
#define VM_S0(seq) BOOST_PP_SEQ_ELEM(0, seq)
#define VM_S1(seq) BOOST_PP_SEQ_ELEM(1, seq)
#define VM_S2(seq) BOOST_PP_SEQ_ELEM(2, seq)
#define VM_S3(seq) BOOST_PP_SEQ_ELEM(3, seq)


#define VM_SEQ_RGSI (r)(g)(s)(i)
#define VM_SEQ_RGS  (r)(g)(s)

#define VM_P_i(i) (&(i))
#define VM_P_r(i) (m_register[(i)])
#define VM_P_g(i) (m_global[(i)])
#define VM_P_s(i) (m_stack[(i)])

#define VM_R_uintValue(r) (r)->uintData

#define VM_UINT32_IMOP_DECLARE_BINARY(unused,product) \
    (( \
      VM_CAT5(VM_2T0(VM_S0(product)), _, VM_S1(product), _, VM_S2(product)), \
      VM_R_uintValue(VM_CAT(VM_P_,VM_S1(product))(*((uint32_t *) ip))) \
        VM_CAT(VM_2T1(VM_S0(product)), =) VM_R_uintValue(VM_CAT(VM_P_,VM_S2(product))(*(((uint32_t *) ip) + 1))); \
      ip = (Inst*) (((uint32_t *) ip) + 2);, \
      VM_2T0(VM_S0(product)) \
    ))

#define VM_UINT32_IMOP_DECLARE_TRINARY(unused,product) \
    (( \
      VM_CAT7(VM_S0(product), _, VM_2T0(VM_S1(product)), _, VM_S2(product), _, VM_S3(product)), \
      VM_R_uintValue(VM_CAT(VM_P_,VM_S0(product))(*((uint32_t *) ip))) \
        = VM_R_uintValue(VM_CAT(VM_P_,VM_S2(product))(*(((uint32_t *) ip) + 1))) \
        VM_2T1(VM_S1(product)) VM_R_uintValue(VM_CAT(VM_P_,VM_S3(product))(*(((uint32_t *) ip) + 2))); \
      ip = (Inst*) (((uint32_t *) ip) + 3);, \
      VM_2T0(VM_S0(product)) \
    ))

#define VM_UINT32_IMOPS \
    ((add,+)) \
    ((sub,-)) \
    ((mul,*)) \
    ((div,/)) \
    ((mod,%))

#define VM_BINARY_UINT32_IMOPS  BOOST_PP_SEQ_FOR_EACH_PRODUCT(VM_UINT32_IMOP_DECLARE_BINARY,               (VM_UINT32_IMOPS)(VM_SEQ_RGS) (VM_SEQ_RGSI))
#define VM_TRINARY_UINT32_IMOPS BOOST_PP_SEQ_FOR_EACH_PRODUCT(VM_UINT32_IMOP_DECLARE_TRINARY,  (VM_SEQ_RGS)(VM_UINT32_IMOPS)(VM_SEQ_RGSI)(VM_SEQ_RGSI))

#define VM_FOR_EACH_IMOP(macro) \
    BOOST_PP_SEQ_FOR_EACH(macro, _, VM_BINARY_UINT32_IMOPS) \
    BOOST_PP_SEQ_FOR_EACH(macro, _, VM_TRINARY_UINT32_IMOPS) \

#define VM_IMOP_DECL(unused,unused2,tuple) \
    && VM_CAT(label__,VM_3T0(tuple)),

#define VM_IMOP_IMPL(unused,unused2,tuple) \
    VM_CAT(label__,VM_3T0(tuple)): \
        VM_3T1(tuple) \
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
