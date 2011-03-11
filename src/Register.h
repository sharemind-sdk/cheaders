#ifndef __REGISTER_H__
#define __REGISTER_H__

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"

#ifdef __cplusplus
extern "C" {
#endif

enum RegisterType {
    RT_const           = 0x01,
    RT_ref             = 0x02,
      RT_constref      = RT_const | RT_ref,
      RT_attributemask = 0xff,

    RT_bool       = 0x00000100,
    RT_string     = 0x00000200,
    RT_uint32     = 0x00000400,
    RT_user       = 0x01000000, /* Minimum value for an user-defined type. */
      RT_typemask = 0xffffff00,
      RT_usermask = 0xff000000
};

/*******************************************************************************
  Register
*******************************************************************************/

struct Register {
    RegisterType type __attribute__ ((aligned (4)));
    union {
      uint32_t uintData;
      Register *ref;
      const Register *constref;
      void *pData;
    } __attribute__ ((aligned (4)));
    void *data[0] __attribute__ ((aligned (4)));
};


inline int Register_isConst(const Register *r)    { return (r->type & RT_const)    != 0x0; }
inline int Register_isRef(const Register *r)      { return (r->type & RT_ref)      != 0x0; }
inline int Register_isConstRef(const Register *r) { return (r->type & RT_constref) != 0x0; }

inline int Register_isBool(const Register *r)   { return (r->type & RT_bool)   != 0x0; }
inline int Register_isUint32(const Register *r) { return (r->type & RT_uint32) != 0x0; }
inline int Register_isString(const Register *r) { return (r->type & RT_string) != 0x0; }

inline uint32_t Register_uint32Value(const Register *r) {
    assert(Register_isUint32(r));
    if (Register_isRef(r)) {
        assert(r->constref->type == RT_uint32 || r->constref->type == (RT_uint32 | RT_const));
        return r->constref->uintData;
    }
    return r->uintData;
}

inline uint32_t Register_stringLength(const Register *r) {
    assert(Register_isString(r));
    if (Register_isRef(r)) {
        assert(r->constref->type == RT_string || r->constref->type == (RT_string | RT_const));
        return r->constref->uintData;
    }
    return r->uintData;
}

inline const char *Register_stringData(const Register *r) {
    assert(Register_isString(r));
    switch (r->type & (RT_ref | RT_const)) {
        case RT_constref:
            assert(r->constref->type == RT_string || r->constref->type == (RT_string | RT_const));
            if (Register_isConst(r->constref)) {
                return (const char *) &r->constref->data[0];
            } else {
                return (const char *) r->constref->data[0];
            }
        case RT_ref:
            assert(r->constref->type == RT_string);
            return (const char *) r->constref->data[0];
        case RT_const:
            return (const char *) &r->data[0];
        default:
            return (const char *) r->data[0];
    }
}

/**
  Allocates and initializes a new register which is a constant reference to the
  given register.
  \param[in] dr The register being referenced.
  \returns a pointer to the new constant reference register.
*/
inline Register *Register_init_constRef(const Register *dr) {
    assert(dr != 0);
    Register *r = (Register *) malloc(sizeof(Register));
    r->type = (RegisterType) ((dr->type & RT_typemask) | RT_ref | RT_const);
    r->constref = dr;
    return r;
}

/**
  Allocates and initializes a new register which is a reference to the given
  register.
  \param[in] dr The register being referenced.
  \returns a pointer to the new reference register.
*/
inline Register *Register_init_ref(const Register *dr) {
    Register *r = (Register *) malloc(sizeof(Register));
    r->type = (RegisterType) ((dr->type & RT_typemask) | RT_ref);
    r->ref = (Register *) dr;
    return r;
}

/**
  Allocates and initializes a new register which contains a constant string. The
  string data is memcpy-d to the register.
  \param[in] length The length of the constant string in bytes.
  \param[in] length The beginning of the constant string data.
  \returns a pointer to the new constant string register.
*/
inline Register *Register_init_constString(uint32_t length, const char *data) {
    Register *r = (Register *) malloc(sizeof(Register) + length);
    if (r != 0) {
        r->type = (RegisterType) (RT_const | RT_string);
        memcpy(&r->data[0], data, length);
    }
    return r;
}

/**
  Allocates and initializes a new register which contains a mutable string. The
  string data is memcpy-d to the register.
  \param[in] length The length of the initial string in bytes.
  \param[in] length The beginning of the initial string data.
  \returns a pointer to the new string register.
*/
inline Register *Register_init_string(uint32_t length, const char *data) {
    Register *r = (Register *) malloc(sizeof(Register) + sizeof(char*));
    if (r != 0) {
        r->type = RT_string;
        if (length > 0) {
            r->data[0] = (void *) malloc(length);
            memcpy(r->data[0], data, length);
        }
    }
    return r;
}

/**
  Deinitializes and deallocates the given const reference register.
  \param[in] r The const reference register to free.
*/
inline void Register_free_constRef(Register *r) {
    assert(Register_isRef(r));
    free(r);
}

/**
  Deinitializes and deallocates the given reference register.
  \param[in] r The reference register to free.
*/
inline void Register_free_ref(Register *r) {
    assert(Register_isRef(r));
    free(r);
}

/**
  Deinitializes and deallocates the given const string register.
  \param[in] r The const string register to free.
*/
inline void Register_free_constString(Register *r) {
    assert(r->type == (RT_const | RT_string));
    free(r);
}

/**
  Deinitializes and deallocates the given string register.
  \param[in] r The string register to free.
*/
inline void Register_free_string(Register *r) {
    assert(r->type == RT_string);
    free(r->data[0]);
    free(r);
}

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* __REGISTER_H__ */
