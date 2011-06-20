#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#ifdef __GNUC__
#define likely(c)   __builtin_expect(!!(c), 1)
#define unlikely(c) __builtin_expect(!!(c), 0)
#else
#define likely(c)   !!(c)
#define unlikely(c) !!(c)
#endif

#endif /* __GLOBAL_H__ */

