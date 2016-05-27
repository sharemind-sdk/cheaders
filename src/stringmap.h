/*
 * Copyright (C) 2015 Cybernetica
 *
 * Research/Commercial License Usage
 * Licensees holding a valid Research License or Commercial License
 * for the Software may use this file according to the written
 * agreement between you and Cybernetica.
 *
 * GNU General Public License Usage
 * Alternatively, this file may be used under the terms of the GNU
 * General Public License version 3.0 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.  Please review the following information to
 * ensure the GNU General Public License version 3.0 requirements will be
 * met: http://www.gnu.org/copyleft/gpl-3.0.html.
 *
 * For further information, please contact us at sharemind@cyber.ee.
 */

#ifndef SHAREMIND_STRINGMAP_H
#define SHAREMIND_STRINGMAP_H

#include "map.h"

#include <stdbool.h>
#include <string.h>
#include "extern_c.h"
#include "fnv.h"
#include "wrap.h"


#define SHAREMIND_STRINGMAP_DECLARE_BODY(name,valuetype) \
    SHAREMIND_MAP_DECLARE_BODY(name,char *,valuetype)

#define SHAREMIND_STRINGMAP_DECLARE_init(name,inlinePerhaps,...) \
    SHAREMIND_MAP_DECLARE_init(name,inlinePerhaps,__VA_ARGS__)
#define SHAREMIND_STRINGMAP_DEFINE_init(name,inlinePerhaps) \
    SHAREMIND_MAP_DEFINE_init(name,inlinePerhaps)

#define SHAREMIND_STRINGMAP_DECLARE_destroy(name,inlinePerhaps,params,...) \
    SHAREMIND_MAP_DECLARE_destroy(name, \
                                  inlinePerhaps, \
                                  SHAREMIND_WRAP(params), \
                                  __VA_ARGS__)
#define SHAREMIND_STRINGMAP_DEFINE_destroy(name,inlinePerhaps,valuetype,params,myfree,...) \
    SHAREMIND_MAP_DEFINE_destroy(name, \
                                 inlinePerhaps, \
                                 SHAREMIND_WRAP(params), \
                                 myfree, \
                                 { \
                                    valuetype * const value = &v->value; \
                                    __VA_ARGS__ \
                                    (void) value; \
                                 } \
                                 myfree(v->key);)

#define SHAREMIND_STRINGMAP_DECLARE_get(name,inlinePerhaps,...) \
    SHAREMIND_MAP_DECLARE_get(name,inlinePerhaps,const char *,__VA_ARGS__)
#define SHAREMIND_STRINGMAP_DEFINE_get(name,inlinePerhaps) \
    SHAREMIND_MAP_DEFINE_get(name, \
                             inlinePerhaps, \
                             const char *, \
                             fnv_16a_str(key), \
                             0 == strcmp, \
                             0 > strcmp)

#define SHAREMIND_STRINGMAP_DECLARE_at(name,inlinePerhaps,...) \
    SHAREMIND_MAP_DECLARE_at(name,inlinePerhaps,__VA_ARGS__)
#define SHAREMIND_STRINGMAP_DEFINE_at(name,inlinePerhaps) \
    SHAREMIND_MAP_DEFINE_at(name,inlinePerhaps)

#define SHAREMIND_STRINGMAP_DECLARE_foreach_detail(prefix,name,params,...) \
    SHAREMIND_MAP_DECLARE_foreach_detail(prefix, \
                                         name, \
                                         SHAREMIND_WRAP(params), \
                                         __VA_ARGS__)
#define SHAREMIND_STRINGMAP_DEFINE_foreach_detail(prefix,name,params,decls,doneResult,...) \
    SHAREMIND_MAP_DEFINE_foreach_detail(prefix, \
                                        name, \
                                        SHAREMIND_WRAP(params), \
                                        decls, \
                                        doneResult, \
                                        __VA_ARGS__)

#define SHAREMIND_STRINGMAP_DECLARE_foreach(name,inlinePerhaps,...) \
    SHAREMIND_MAP_DECLARE_foreach(name,inlinePerhaps,__VA_ARGS__)
#define SHAREMIND_STRINGMAP_DEFINE_foreach(name,inlinePerhaps) \
    SHAREMIND_MAP_DEFINE_foreach(name,inlinePerhaps)

#define SHAREMIND_STRINGMAP_DECLARE_foreachVoid(name,inlinePerhaps,...) \
    SHAREMIND_MAP_DECLARE_foreachVoid(name,inlinePerhaps,__VA_ARGS__)
#define SHAREMIND_STRINGMAP_DEFINE_foreachVoid(name,inlinePerhaps) \
    SHAREMIND_MAP_DEFINE_foreachVoid(name,inlinePerhaps)

#define SHAREMIND_STRINGMAP_DECLARE_foreachWith(name,inlinePerhaps,WithName,params,...) \
    SHAREMIND_MAP_DECLARE_foreachWith(name, \
                                      inlinePerhaps, \
                                      WithName, \
                                      SHAREMIND_WRAP(params), \
                                      __VA_ARGS__)
#define SHAREMIND_STRINGMAP_DEFINE_foreachWith(name,inlinePerhaps,WithName,params,...) \
    SHAREMIND_MAP_DEFINE_foreachWith(name, \
                                     inlinePerhaps, \
                                     WithName, \
                                     SHAREMIND_WRAP(params), \
                                     __VA_ARGS__)

#define SHAREMIND_STRINGMAP_DECLARE_foreachVoidWith(name,inlinePerhaps,WithName,params,...) \
    SHAREMIND_MAP_DECLARE_foreachVoidWith(name, \
                                          inlinePerhaps, \
                                          WithName, \
                                          SHAREMIND_WRAP(params), \
                                          __VA_ARGS__)
#define SHAREMIND_STRINGMAP_DEFINE_foreachVoidWith(name,inlinePerhaps,WithName,params,...) \
    SHAREMIND_MAP_DEFINE_foreachVoidWith(name, \
                                         inlinePerhaps, \
                                         WithName, \
                                         SHAREMIND_WRAP(params), \
                                         __VA_ARGS__)

#define SHAREMIND_STRINGMAP_DECLARE_insertHint(name,inlinePerhaps,...) \
    SHAREMIND_MAP_DECLARE_insertHint(name, \
                                     inlinePerhaps, \
                                     const char *, \
                                     __VA_ARGS__)
#define SHAREMIND_STRINGMAP_DEFINE_insertHint(name,inlinePerhaps) \
    SHAREMIND_MAP_DEFINE_insertHint(name, \
                                    inlinePerhaps, \
                                    const char *, \
                                    fnv_16a_str(key), \
                                    0 == strcmp, \
                                    0 > strcmp)


#define SHAREMIND_STRINGMAP_DECLARE_emplaceAtHint(name,inlinePerhaps,...) \
    SHAREMIND_MAP_DECLARE_emplaceAtHint(name, inlinePerhaps, __VA_ARGS__)
#define SHAREMIND_STRINGMAP_DEFINE_emplaceAtHint(name,inlinePerhaps) \
    SHAREMIND_MAP_DEFINE_emplaceAtHint(name, inlinePerhaps)


#define SHAREMIND_STRINGMAP_DECLARE_insertAtHint(name,inlinePerhaps,...) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps bool name ## _keyCopy(char ** dest, const char * src) \
        __attribute__ ((nonnull(1, 2), __VA_ARGS__)); \
    SHAREMIND_EXTERN_C_END \
    SHAREMIND_MAP_DECLARE_insertAtHint(name, \
                                       inlinePerhaps, \
                                       const char *, \
                                       __VA_ARGS__)
#define SHAREMIND_STRINGMAP_DEFINE_insertAtHint(name,inlinePerhaps,mystrdup,mymalloc,myfree) \
    SHAREMIND_EXTERN_C_BEGIN \
    inlinePerhaps bool name ## _keyCopy(char ** dest, const char * src) \
    { return ((*dest) = mystrdup(src)); } \
    SHAREMIND_EXTERN_C_END \
    SHAREMIND_MAP_DEFINE_insertAtHint(name, \
                                      inlinePerhaps, \
                                      const char *, \
                                      name ## _keyCopy, \
                                      mymalloc, \
                                      myfree)


#define SHAREMIND_STRINGMAP_DECLARE_insertNew(name,inlinePerhaps,...) \
    SHAREMIND_MAP_DECLARE_insertNew(name,inlinePerhaps,const char *,__VA_ARGS__)
#define SHAREMIND_STRINGMAP_DEFINE_insertNew(name,inlinePerhaps) \
    SHAREMIND_MAP_DEFINE_insertNew(name,inlinePerhaps,const char *)

#define SHAREMIND_STRINGMAP_DECLARE_remove(name,inlinePerhaps,...) \
    SHAREMIND_MAP_DECLARE_remove(name,inlinePerhaps,const char *,__VA_ARGS__)
#define SHAREMIND_STRINGMAP_DEFINE_remove(name,inlinePerhaps,valuetype,myfree,...) \
    SHAREMIND_MAP_DEFINE_remove(name, \
                                inlinePerhaps, \
                                const char *, \
                                fnv_16a_str(key), \
                                0 == strcmp, \
                                0 > strcmp, \
                                myfree, \
                                { \
                                   valuetype * const value = &v->value; \
                                   __VA_ARGS__ \
                                   (void) value; \
                                } \
                                myfree(v->key);)

#endif /* SHAREMIND_STRINGMAP_H */
