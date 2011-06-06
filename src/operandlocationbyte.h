#ifndef OPERANDLOCATIONBYTE_H
#define OPERANDLOCATIONBYTE_H

#include "preprocessor.h"


/* (name, code, number of 64-bit blocks needed) */
#define SVM_OLB_imm     (imm,     0x01, 1)
#define SVM_OLB_reg     (reg,     0x02, 1)
#define SVM_OLB_stack   (stack,   0x03, 1)
#define SVM_OLB_mem_rr  (mem_rr,  0x04, 2)
#define SVM_OLB_mem_rs  (mem_rs,  0x05, 2)
#define SVM_OLB_mem_ri  (mem_ri,  0x06, 2)
#define SVM_OLB_mem_sr  (mem_sr,  0x07, 2)
#define SVM_OLB_mem_ss  (mem_ss,  0x08, 2)
#define SVM_OLB_mem_si  (mem_si,  0x09, 2)
#define SVM_OLB_cref_rr (cref_rr, 0x0a, 2)
#define SVM_OLB_cref_rs (cref_rs, 0x0b, 2)
#define SVM_OLB_cref_ri (cref_ri, 0x0c, 2)
#define SVM_OLB_cref_sr (cref_sr, 0x0d, 2)
#define SVM_OLB_cref_ss (cref_ss, 0x0e, 2)
#define SVM_OLB_cref_si (cref_si, 0x0f, 2)
#define SVM_OLB_ref_rr  (ref_rr,  0x10, 2)
#define SVM_OLB_ref_rs  (ref_rs,  0x11, 2)
#define SVM_OLB_ref_ri  (ref_ri,  0x12, 2)
#define SVM_OLB_ref_sr  (ref_sr,  0x13, 2)
#define SVM_OLB_ref_ss  (ref_ss,  0x14, 2)
#define SVM_OLB_ref_si  (ref_si,  0x15, 2)

#define SVM_OLB(n) SVM_C(SVM_OLB_,n)

#define SVM_OLB_name(t) SVM_T(3,0,t)
#define SVM_OLB_code(t) SVM_T(3,1,t)
#define SVM_OLB_args(t) SVM_T(3,2,t)

#define SVM_OLB_FOREACH_MACRO(_,m,i) m(SVM_OLB(i))
#define SVM_OLB_FOREACH(m,s) BOOST_PP_SEQ_FOR_EACH(SVM_OLB_FOREACH_MACRO,m,s)

#endif /* OPERANDLOCATIONBYTE_H */
