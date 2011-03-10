#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#ifdef __GNUC__
#define likely(c)   (__builtin_constant_p(c) ? !!(c) : __branch_check__(c, 1))
#define unlikely(c) (__builtin_constant_p(c) ? !!(c) : __branch_check__(c, 0))
#else
#define likely(c)   !!(c)
#define unlikely(c) !!(c)
#endif

#endif /* __GLOBAL_H__ */

