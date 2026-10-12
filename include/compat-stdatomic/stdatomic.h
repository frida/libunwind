// A minimal stdatomic.h for GCC versions that have the __atomic
// builtins but predate C11's <stdatomic.h> and _Atomic.

#ifndef COMPAT_STDATOMIC_H
#define COMPAT_STDATOMIC_H

#include <stdbool.h>

#define _Atomic volatile
#define ATOMIC_FLAG_INIT 0

typedef volatile bool atomic_bool;
typedef volatile bool atomic_flag;

#define atomic_load(obj) __atomic_load_n (obj, __ATOMIC_SEQ_CST)
#define atomic_store(obj, desired) \
    __atomic_store_n (obj, desired, __ATOMIC_SEQ_CST)
#define atomic_fetch_add(obj, arg) \
    __atomic_fetch_add (obj, arg, __ATOMIC_SEQ_CST)
#define atomic_compare_exchange_strong(obj, expected, desired) \
    __atomic_compare_exchange_n (obj, expected, desired, false, \
        __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define atomic_flag_test_and_set(obj) \
    __atomic_test_and_set (obj, __ATOMIC_SEQ_CST)
#define atomic_flag_clear(obj) __atomic_clear (obj, __ATOMIC_SEQ_CST)

#endif
