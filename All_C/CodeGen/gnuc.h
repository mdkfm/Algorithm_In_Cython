//
// Created by skf on 23-12-11.
//

#ifndef ALL_C_GNUC_H
#define ALL_C_GNUC_H
#undef inline
#define inline __inline__ __attribute__((always_inline))
#define __noinline __attribute__((noinline))
#define __pure __attribute__((pure))
#define __const __attribute__((const))
#define __noreturn __attribute__((noreturn))
#define __malloc __attribute__((malloc))
#define __receive __attribute__((warn_unused_result))
#define __deprecated __attribute__((deprecated))
#define __used __attribute__((used))
#define __unused __attribute__((unused))
#define __packed __attribute__((packed))
#define __align(x) __attribute__((aligned(x)))
#define __align_max __attribute__((aligned))
#define likely(x) (__builtin_expect(!!(x), 1))
#define unlikely(x) (__builtin_expect(!!(x), 0))

#define RAII(func) __attribute__((cleanup(func)))
#define auto_ptr(class) RAII(class##_raii) class##_class_ptr
#define DPtr(class) typedef class * const CCAT(class, class_ptr)

typedef void (*FPtr)(void);

#endif //ALL_C_GNUC_H
