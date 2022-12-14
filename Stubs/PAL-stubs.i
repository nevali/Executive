# 1 "PAL-stubs.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 400 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "PAL-stubs.c" 2

# 1 "../PrivateHeaders/BuildConfiguration.h" 1
# 3 "PAL-stubs.c" 2


# 1 "../Headers/Executive/Linkage.h" 1
# 6 "PAL-stubs.c" 2




# 1 "../Headers/PAL/PAL.h" 1
# 23 "../Headers/PAL/PAL.h"
# 1 "../Headers/Executive/IPlatform.h" 1




typedef struct IPlatform IPlatform;
# 30 "../Headers/Executive/IPlatform.h"
# 1 "../Headers/Executive/IObject.h" 1




typedef struct IObject IObject;
# 30 "../Headers/Executive/IObject.h"
# 1 "../Headers/Executive/Types.h" 1
# 28 "../Headers/Executive/Types.h"
# 1 "/Library/Developer/CommandLineTools/usr/lib/clang/14.0.0/include/stdbool.h" 1 3
# 29 "../Headers/Executive/Types.h" 2

# 1 "/Library/Developer/CommandLineTools/usr/lib/clang/14.0.0/include/stddef.h" 1 3
# 35 "/Library/Developer/CommandLineTools/usr/lib/clang/14.0.0/include/stddef.h" 3
typedef long int ptrdiff_t;
# 46 "/Library/Developer/CommandLineTools/usr/lib/clang/14.0.0/include/stddef.h" 3
typedef long unsigned int size_t;
# 74 "/Library/Developer/CommandLineTools/usr/lib/clang/14.0.0/include/stddef.h" 3
typedef int wchar_t;
# 102 "/Library/Developer/CommandLineTools/usr/lib/clang/14.0.0/include/stddef.h" 3
# 1 "/Library/Developer/CommandLineTools/usr/lib/clang/14.0.0/include/__stddef_max_align_t.h" 1 3
# 16 "/Library/Developer/CommandLineTools/usr/lib/clang/14.0.0/include/__stddef_max_align_t.h" 3
typedef long double max_align_t;
# 103 "/Library/Developer/CommandLineTools/usr/lib/clang/14.0.0/include/stddef.h" 2 3
# 31 "../Headers/Executive/Types.h" 2
# 1 "/Library/Developer/CommandLineTools/usr/lib/clang/14.0.0/include/stdint.h" 1 3
# 52 "/Library/Developer/CommandLineTools/usr/lib/clang/14.0.0/include/stdint.h" 3
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdint.h" 1 3 4
# 18 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdint.h" 3 4
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_int8_t.h" 1 3 4
# 30 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_int8_t.h" 3 4
typedef signed char int8_t;
# 19 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdint.h" 2 3 4
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_int16_t.h" 1 3 4
# 30 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_int16_t.h" 3 4
typedef short int16_t;
# 20 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdint.h" 2 3 4
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_int32_t.h" 1 3 4
# 30 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_int32_t.h" 3 4
typedef int int32_t;
# 21 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdint.h" 2 3 4
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_int64_t.h" 1 3 4
# 30 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_int64_t.h" 3 4
typedef long long int64_t;
# 22 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdint.h" 2 3 4

# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/_types/_uint8_t.h" 1 3 4
# 31 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/_types/_uint8_t.h" 3 4
typedef unsigned char uint8_t;
# 24 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdint.h" 2 3 4
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/_types/_uint16_t.h" 1 3 4
# 31 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/_types/_uint16_t.h" 3 4
typedef unsigned short uint16_t;
# 25 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdint.h" 2 3 4
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/_types/_uint32_t.h" 1 3 4
# 31 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/_types/_uint32_t.h" 3 4
typedef unsigned int uint32_t;
# 26 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdint.h" 2 3 4
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/_types/_uint64_t.h" 1 3 4
# 31 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/_types/_uint64_t.h" 3 4
typedef unsigned long long uint64_t;
# 27 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdint.h" 2 3 4


typedef int8_t int_least8_t;
typedef int16_t int_least16_t;
typedef int32_t int_least32_t;
typedef int64_t int_least64_t;
typedef uint8_t uint_least8_t;
typedef uint16_t uint_least16_t;
typedef uint32_t uint_least32_t;
typedef uint64_t uint_least64_t;



typedef int8_t int_fast8_t;
typedef int16_t int_fast16_t;
typedef int32_t int_fast32_t;
typedef int64_t int_fast64_t;
typedef uint8_t uint_fast8_t;
typedef uint16_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
typedef uint64_t uint_fast64_t;




# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types.h" 1 3 4
# 32 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types.h" 3 4
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/cdefs.h" 1 3 4
# 666 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/cdefs.h" 3 4
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_symbol_aliasing.h" 1 3 4
# 667 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/cdefs.h" 2 3 4
# 732 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/cdefs.h" 3 4
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_posix_availability.h" 1 3 4
# 733 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/cdefs.h" 2 3 4
# 33 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types.h" 2 3 4
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/machine/_types.h" 1 3 4
# 34 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/machine/_types.h" 3 4
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/arm/_types.h" 1 3 4
# 15 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/arm/_types.h" 3 4
typedef signed char __int8_t;



typedef unsigned char __uint8_t;
typedef short __int16_t;
typedef unsigned short __uint16_t;
typedef int __int32_t;
typedef unsigned int __uint32_t;
typedef long long __int64_t;
typedef unsigned long long __uint64_t;

typedef long __darwin_intptr_t;
typedef unsigned int __darwin_natural_t;
# 48 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/arm/_types.h" 3 4
typedef int __darwin_ct_rune_t;





typedef union {
 char __mbstate8[128];
 long long _mbstateL;
} __mbstate_t;

typedef __mbstate_t __darwin_mbstate_t;


typedef long int __darwin_ptrdiff_t;







typedef long unsigned int __darwin_size_t;





typedef __builtin_va_list __darwin_va_list;





typedef int __darwin_wchar_t;




typedef __darwin_wchar_t __darwin_rune_t;


typedef int __darwin_wint_t;




typedef unsigned long __darwin_clock_t;
typedef __uint32_t __darwin_socklen_t;
typedef long __darwin_ssize_t;
typedef long __darwin_time_t;
# 35 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/machine/_types.h" 2 3 4
# 34 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types.h" 2 3 4
# 55 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types.h" 3 4
typedef __int64_t __darwin_blkcnt_t;
typedef __int32_t __darwin_blksize_t;
typedef __int32_t __darwin_dev_t;
typedef unsigned int __darwin_fsblkcnt_t;
typedef unsigned int __darwin_fsfilcnt_t;
typedef __uint32_t __darwin_gid_t;
typedef __uint32_t __darwin_id_t;
typedef __uint64_t __darwin_ino64_t;

typedef __darwin_ino64_t __darwin_ino_t;



typedef __darwin_natural_t __darwin_mach_port_name_t;
typedef __darwin_mach_port_name_t __darwin_mach_port_t;
typedef __uint16_t __darwin_mode_t;
typedef __int64_t __darwin_off_t;
typedef __int32_t __darwin_pid_t;
typedef __uint32_t __darwin_sigset_t;
typedef __int32_t __darwin_suseconds_t;
typedef __uint32_t __darwin_uid_t;
typedef __uint32_t __darwin_useconds_t;
typedef unsigned char __darwin_uuid_t[16];
typedef char __darwin_uuid_string_t[37];

# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_pthread/_pthread_types.h" 1 3 4
# 57 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_pthread/_pthread_types.h" 3 4
struct __darwin_pthread_handler_rec {
 void (*__routine)(void *);
 void *__arg;
 struct __darwin_pthread_handler_rec *__next;
};

struct _opaque_pthread_attr_t {
 long __sig;
 char __opaque[56];
};

struct _opaque_pthread_cond_t {
 long __sig;
 char __opaque[40];
};

struct _opaque_pthread_condattr_t {
 long __sig;
 char __opaque[8];
};

struct _opaque_pthread_mutex_t {
 long __sig;
 char __opaque[56];
};

struct _opaque_pthread_mutexattr_t {
 long __sig;
 char __opaque[8];
};

struct _opaque_pthread_once_t {
 long __sig;
 char __opaque[8];
};

struct _opaque_pthread_rwlock_t {
 long __sig;
 char __opaque[192];
};

struct _opaque_pthread_rwlockattr_t {
 long __sig;
 char __opaque[16];
};

struct _opaque_pthread_t {
 long __sig;
 struct __darwin_pthread_handler_rec *__cleanup_stack;
 char __opaque[8176];
};

typedef struct _opaque_pthread_attr_t __darwin_pthread_attr_t;
typedef struct _opaque_pthread_cond_t __darwin_pthread_cond_t;
typedef struct _opaque_pthread_condattr_t __darwin_pthread_condattr_t;
typedef unsigned long __darwin_pthread_key_t;
typedef struct _opaque_pthread_mutex_t __darwin_pthread_mutex_t;
typedef struct _opaque_pthread_mutexattr_t __darwin_pthread_mutexattr_t;
typedef struct _opaque_pthread_once_t __darwin_pthread_once_t;
typedef struct _opaque_pthread_rwlock_t __darwin_pthread_rwlock_t;
typedef struct _opaque_pthread_rwlockattr_t __darwin_pthread_rwlockattr_t;
typedef struct _opaque_pthread_t *__darwin_pthread_t;
# 81 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types.h" 2 3 4
# 53 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdint.h" 2 3 4
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_intptr_t.h" 1 3 4
# 30 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_intptr_t.h" 3 4
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/machine/types.h" 1 3 4
# 37 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/machine/types.h" 3 4
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/arm/types.h" 1 3 4
# 60 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/arm/types.h" 3 4
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_u_int8_t.h" 1 3 4
# 30 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_u_int8_t.h" 3 4
typedef unsigned char u_int8_t;
# 61 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/arm/types.h" 2 3 4
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_u_int16_t.h" 1 3 4
# 30 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_u_int16_t.h" 3 4
typedef unsigned short u_int16_t;
# 62 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/arm/types.h" 2 3 4
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_u_int32_t.h" 1 3 4
# 30 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_u_int32_t.h" 3 4
typedef unsigned int u_int32_t;
# 63 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/arm/types.h" 2 3 4
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_u_int64_t.h" 1 3 4
# 30 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_u_int64_t.h" 3 4
typedef unsigned long long u_int64_t;
# 64 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/arm/types.h" 2 3 4


typedef int64_t register_t;




# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_intptr_t.h" 1 3 4
# 72 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/arm/types.h" 2 3 4
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_uintptr_t.h" 1 3 4
# 34 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_uintptr_t.h" 3 4
typedef unsigned long uintptr_t;
# 73 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/arm/types.h" 2 3 4




typedef u_int64_t user_addr_t;
typedef u_int64_t user_size_t;
typedef int64_t user_ssize_t;
typedef int64_t user_long_t;
typedef u_int64_t user_ulong_t;
typedef int64_t user_time_t;
typedef int64_t user_off_t;
# 104 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/arm/types.h" 3 4
typedef u_int64_t syscall_arg_t;
# 38 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/machine/types.h" 2 3 4
# 31 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_intptr_t.h" 2 3 4

typedef __darwin_intptr_t intptr_t;
# 54 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdint.h" 2 3 4




# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/_types/_intmax_t.h" 1 3 4
# 32 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/_types/_intmax_t.h" 3 4
typedef long int intmax_t;
# 59 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdint.h" 2 3 4
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/_types/_uintmax_t.h" 1 3 4
# 32 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/_types/_uintmax_t.h" 3 4
typedef long unsigned int uintmax_t;
# 60 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdint.h" 2 3 4
# 53 "/Library/Developer/CommandLineTools/usr/lib/clang/14.0.0/include/stdint.h" 2 3
# 32 "../Headers/Executive/Types.h" 2
# 1 "/Library/Developer/CommandLineTools/usr/lib/clang/14.0.0/include/stdarg.h" 1 3
# 14 "/Library/Developer/CommandLineTools/usr/lib/clang/14.0.0/include/stdarg.h" 3
typedef __builtin_va_list va_list;
# 32 "/Library/Developer/CommandLineTools/usr/lib/clang/14.0.0/include/stdarg.h" 3
typedef __builtin_va_list __gnuc_va_list;
# 33 "../Headers/Executive/Types.h" 2

# 1 "../Headers/Executive/arm64/Types.h" 1
# 35 "../Headers/Executive/Types.h" 2








typedef int32_t REFCOUNT;
# 31 "../Headers/Executive/IObject.h" 2
# 1 "../Headers/Executive/UUID.h" 1
# 36 "../Headers/Executive/UUID.h"
typedef union UUID
{
 uint8_t bytes[16];
 struct
 { uint32_t d1;
  uint32_t d2;
  uint32_t d3;
  uint32_t d4;
 } d;
 struct
 {
  uint32_t data1;
  uint16_t data2;
  uint16_t data3;
  uint8_t data4[8];
 } guid;
 struct
 {
  uint32_t time_low;
  uint16_t time_mid;
  uint16_t time_hi_and_version;
  uint8_t clock_seq_hi_and_reserved;
  uint8_t clock_seq_low;
  uint8_t node[6];
 } uuid;
} UUID;


typedef union UUID uuid_t;
# 74 "../Headers/Executive/UUID.h"
# 1 "../Headers/Executive/initguid.h" 1
# 75 "../Headers/Executive/UUID.h" 2
# 32 "../Headers/Executive/IObject.h" 2
# 1 "../Headers/Executive/Errors.h" 1
# 32 "../Headers/Executive/Errors.h"
typedef int STATUS;
# 33 "../Headers/Executive/IObject.h" 2
# 42 "../Headers/Executive/IObject.h"
typedef struct IObject IObject; struct IObject { struct IObject_vtable_ *lpVtbl; }; struct IObject_vtable_
{



 STATUS (*queryInterface)(struct IObject *self, const union UUID * const riid, void **object) ;
 REFCOUNT (*retain)(struct IObject *self) ;
 REFCOUNT (*release)(struct IObject *self) ;


};
# 69 "../Headers/Executive/IObject.h"
static const UUID IID_IObject __attribute__((unused)) = { { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46 } };
# 31 "../Headers/Executive/IPlatform.h" 2
# 1 "../Headers/Executive/IAllocator.h" 1




typedef struct IAllocator IAllocator;
# 30 "../Headers/Executive/IAllocator.h"
# 1 "../Headers/Executive/IObject.h" 1
# 31 "../Headers/Executive/IAllocator.h" 2
# 40 "../Headers/Executive/IAllocator.h"
typedef struct IAllocator IAllocator; struct IAllocator { struct IAllocator_vtable_ *lpVtbl; }; struct IAllocator_vtable_
{




 STATUS (*queryInterface)(struct IAllocator *self, const union UUID * const riid, void **object) ;
 int32_t (*retain)(struct IAllocator *self) ;
 int32_t (*release)(struct IAllocator *self) ;



 void* (*alloc)(struct IAllocator *self, size_t nbytes) ;
 void* (*realloc)(struct IAllocator *self, void *ptr, size_t nbytes) ;
 void (*free)(struct IAllocator *self, void *ptr) ;
 size_t (*size)(struct IAllocator *self, void *ptr) ;
 int (*didAlloc)(struct IAllocator *self, void *ptr) ;
 void (*compact)(struct IAllocator *self) ;


};
# 83 "../Headers/Executive/IAllocator.h"
static const UUID IID_IAllocator __attribute__((unused)) = { { 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46 } };
# 32 "../Headers/Executive/IPlatform.h" 2
# 44 "../Headers/Executive/IPlatform.h"
typedef struct IPlatform IPlatform; struct IPlatform { struct IPlatform_vtable_ *lpVtbl; }; struct IPlatform_vtable_
{




 STATUS (*queryInterface)(struct IPlatform *self, const union UUID * const riid, void **object) ;
 int32_t (*retain)(struct IPlatform *self) ;
 int32_t (*release)(struct IPlatform *self) ;



 void (*panic)(struct IPlatform *self, const char *string) ;
 void (*setDefaultAllocator)(struct IPlatform *self, IAllocator *allocator) ;


};
# 79 "../Headers/Executive/IPlatform.h"
static const UUID IID_IPlatform __attribute__((unused)) = { { 0xd0, 0x2b, 0x26, 0x58, 0xe5, 0xc1, 0x4f, 0xce, 0x9e, 0xa7, 0xae, 0x39, 0x99, 0x66, 0x02, 0xc6 } };
# 24 "../Headers/PAL/PAL.h" 2
# 1 "../Headers/PAL/Platform.h" 1
# 24 "../Headers/PAL/Platform.h"
# 1 "../Headers/Executive/IPlatform.h" 1
# 25 "../Headers/PAL/Platform.h" 2







static const UUID CLSID_PAL_Platform __attribute__((unused)) = { { 0xab, 0xa1, 0x34, 0x43, 0x50, 0xf7, 0x44, 0x9f, 0xbe, 0x24, 0x6b, 0x71, 0x90, 0xb4, 0xd8, 0x71 } };
# 25 "../Headers/PAL/PAL.h" 2
# 1 "../Headers/PAL/MemoryManager.h" 1
# 24 "../Headers/PAL/MemoryManager.h"
# 1 "../Headers/Executive/IMemoryManager.h" 1




typedef struct IMemoryManager IMemoryManager;
# 31 "../Headers/Executive/IMemoryManager.h"
# 1 "../Headers/Executive/IObject.h" 1
# 32 "../Headers/Executive/IMemoryManager.h" 2
# 1 "../Headers/Executive/IRegion.h" 1




typedef struct IRegion IRegion;
# 31 "../Headers/Executive/IRegion.h"
# 1 "../Headers/Executive/IObject.h" 1
# 32 "../Headers/Executive/IRegion.h" 2





typedef enum
{
   RF_MASK_TYPE = 255,
   RF_NORMAL = 0,
   RF_TRANSIENT = (1<<0),
   RF_DMA = (1<<1),
   RF_NOT_BANKED = (1<<2),
   RF_PURGEABLE = (1<<3),
   RF_STACK = (1<<4),
   RF_MASK_OPTIONS = 3840,
   RF_NO_WAIT = 256,
   RF_UNINITIALIZED = 512,
   RF_MASK_PROT = 61440,
   RF_NONE = 0,
   RF_READ = 4096,
   RF_WRITE = 8192,
   RF_EXEC = 16384,
   RF_MASK_HINTS = 983040,
   RF_MASK_LEVEL = 15728640,
   RF_LVL_0 = 0,
   RF_LVL_1 = (1<<40),
   RF_LVL_2 = (2<<40)
} RegionFlags;




typedef struct IRegion IRegion; struct IRegion { struct IRegion_vtable_ *lpVtbl; }; struct IRegion_vtable_
{




 STATUS (*queryInterface)(struct IRegion *self, const union UUID * const riid, void **object) ;
 int32_t (*retain)(struct IRegion *self) ;
 int32_t (*release)(struct IRegion *self) ;



 RegionFlags (*flags)(struct IRegion *self) ;
 int (*queryOwnerInterface)(struct IRegion *self, const union UUID * const riid, void **ptr) ;
 uint8_t* (*base)(struct IRegion *self) ;
 size_t (*pages)(struct IRegion *self) ;
 size_t (*bytes)(struct IRegion *self) ;


};
# 105 "../Headers/Executive/IRegion.h"
static const UUID IID_IRegion __attribute__((unused)) = { { 0xe7, 0x39, 0xec, 0xdb, 0x06, 0xec, 0x40, 0xc9, 0x95, 0xf7, 0x99, 0xc2, 0x2a, 0x0c, 0x4a, 0x7b } };
# 33 "../Headers/Executive/IMemoryManager.h" 2
# 1 "../Headers/Executive/IRegionHolder.h" 1




typedef struct IRegionHolder IRegionHolder;
# 30 "../Headers/Executive/IRegionHolder.h"
# 1 "../Headers/Executive/IObject.h" 1
# 31 "../Headers/Executive/IRegionHolder.h" 2
# 43 "../Headers/Executive/IRegionHolder.h"
typedef struct IRegionHolder IRegionHolder; struct IRegionHolder { struct IRegionHolder_vtable_ *lpVtbl; }; struct IRegionHolder_vtable_
{




 STATUS (*queryInterface)(struct IRegionHolder *self, const union UUID * const riid, void **object) ;
 int32_t (*retain)(struct IRegionHolder *self) ;
 int32_t (*release)(struct IRegionHolder *self) ;





};
# 74 "../Headers/Executive/IRegionHolder.h"
static const UUID IID_IRegionHolder __attribute__((unused)) = { { 0xd2, 0x1b, 0x6d, 0x73, 0x78, 0x03, 0x4f, 0xa4, 0xba, 0x93, 0xd7, 0x34, 0x98, 0xd2, 0xd6, 0x55 } };
# 34 "../Headers/Executive/IMemoryManager.h" 2
# 46 "../Headers/Executive/IMemoryManager.h"
typedef struct IMemoryManager IMemoryManager; struct IMemoryManager { struct IMemoryManager_vtable_ *lpVtbl; }; struct IMemoryManager_vtable_
{




 STATUS (*queryInterface)(struct IMemoryManager *self, const union UUID * const riid, void **object) ;
 int32_t (*retain)(struct IMemoryManager *self) ;
 int32_t (*release)(struct IMemoryManager *self) ;



 int (*regionFromPointer)(struct IMemoryManager *self, void *ptr, IRegion **region) ;
 int (*pageSize)(struct IMemoryManager *self) ;
 int (*obtainRegion)(struct IMemoryManager *self, size_t count, RegionFlags flags, IRegionHolder *owner, IRegion **region) ;
 int (*obtainTransientRegion)(struct IMemoryManager *self, size_t count, RegionFlags flags, IRegionHolder *owner, IRegion **region) ;


};
# 85 "../Headers/Executive/IMemoryManager.h"
static const UUID IID_IMemoryManager __attribute__((unused)) = { { 0xf0, 0x37, 0xaf, 0x3e, 0xa4, 0x1f, 0x48, 0x13, 0xb2, 0xdc, 0x69, 0xbf, 0x96, 0x04, 0x9b, 0xf2 } };
# 25 "../Headers/PAL/MemoryManager.h" 2







static const UUID CLSID_PAL_MemoryManager __attribute__((unused)) = { { 0x2f, 0x26, 0x86, 0x22, 0x3a, 0x49, 0x49, 0xd8, 0xaa, 0x23, 0x6e, 0xfb, 0x1a, 0xd0, 0x99, 0x89 } };
# 26 "../Headers/PAL/PAL.h" 2
# 1 "../Headers/PAL/BootEnvironment.h" 1
# 24 "../Headers/PAL/BootEnvironment.h"
# 1 "../Headers/Executive/IBootEnvironment.h" 1




typedef struct IBootEnvironment IBootEnvironment;
# 30 "../Headers/Executive/IBootEnvironment.h"
# 1 "../Headers/Executive/IObject.h" 1
# 31 "../Headers/Executive/IBootEnvironment.h" 2
# 43 "../Headers/Executive/IBootEnvironment.h"
typedef struct IBootEnvironment IBootEnvironment; struct IBootEnvironment { struct IBootEnvironment_vtable_ *lpVtbl; }; struct IBootEnvironment_vtable_
{




 STATUS (*queryInterface)(struct IBootEnvironment *self, const union UUID * const riid, void **object) ;
 int32_t (*retain)(struct IBootEnvironment *self) ;
 int32_t (*release)(struct IBootEnvironment *self) ;





};
# 74 "../Headers/Executive/IBootEnvironment.h"
static const UUID IID_IBootEnvironment __attribute__((unused)) = { { 0xf1, 0x2b, 0xc7, 0xd1, 0xe4, 0x14, 0x40, 0x75, 0x84, 0xbd, 0xd5, 0x71, 0x22, 0x91, 0xf2, 0x83 } };
# 25 "../Headers/PAL/BootEnvironment.h" 2







static const UUID CLSID_PAL_BootEnvironment __attribute__((unused)) = { { 0xb3, 0xbe, 0x0a, 0x7a, 0xe1, 0xc9, 0x43, 0xe7, 0x9c, 0x3f, 0x0e, 0x18, 0xab, 0xa6, 0xb8, 0x80 } };
# 27 "../Headers/PAL/PAL.h" 2
# 1 "../Headers/PAL/PlatformDiagnostics.h" 1
# 24 "../Headers/PAL/PlatformDiagnostics.h"
# 1 "../Headers/Executive/IPlatformDiagnostics.h" 1




typedef struct IPlatformDiagnostics IPlatformDiagnostics;
# 30 "../Headers/Executive/IPlatformDiagnostics.h"
# 1 "../Headers/Executive/IObject.h" 1
# 31 "../Headers/Executive/IPlatformDiagnostics.h" 2





typedef enum
{
   LOG_EMERG = 100,
   LOG_EMERGENCY = LOG_EMERG,
   LOG_ALERT = 50,
   LOG_CRIT = 40,
   LOG_CRITICAL = LOG_CRIT,
   LOG_ERR = 30,
   LOG_ERROR = LOG_ERR,
   LOG_WARN = 20,
   LOG_WARNING = LOG_WARN,
   LOG_NOTICE = 10,
   LOG_INFO = 0,
   LOG_DEBUG = -1,
   LOG_DEBUG2 = -2,
   LOG_DEBUG3 = -3,
   LOG_DEBUG4 = -4,
   LOG_DEBUG5 = -5,
   LOG_DEBUG6 = -6,
   LOG_DEBUG7 = -7
} LogLevel;




typedef struct IPlatformDiagnostics IPlatformDiagnostics; struct IPlatformDiagnostics { struct IPlatformDiagnostics_vtable_ *lpVtbl; }; struct IPlatformDiagnostics_vtable_
{




 STATUS (*queryInterface)(struct IPlatformDiagnostics *self, const union UUID * const riid, void **object) ;
 int32_t (*retain)(struct IPlatformDiagnostics *self) ;
 int32_t (*release)(struct IPlatformDiagnostics *self) ;



 void (*log)(struct IPlatformDiagnostics *self, LogLevel level, const char *string) ;


};
# 94 "../Headers/Executive/IPlatformDiagnostics.h"
static const UUID IID_IPlatformDiagnostics __attribute__((unused)) = { { 0x59, 0x15, 0xac, 0x8d, 0x93, 0xd9, 0x48, 0xe6, 0xbb, 0xdf, 0xd6, 0xec, 0xdd, 0x1a, 0x8f, 0xaf } };
# 25 "../Headers/PAL/PlatformDiagnostics.h" 2







static const UUID CLSID_PAL_PlatformDiagnostics __attribute__((unused)) = { { 0xd3, 0xb7, 0xb5, 0x17, 0x9d, 0xac, 0x4a, 0xca, 0x80, 0x12, 0xcf, 0xec, 0xb5, 0x76, 0xe5, 0x69 } };
# 28 "../Headers/PAL/PAL.h" 2






extern int PAL_metaClass(const union UUID * const clsid, const union UUID * const iid, void **out) __attribute__((weak_import)) __attribute__((weak)) __asm__("_" "PAL" "$" "metaClass" "@" "0.0");

extern void PAL_panic(const char *string) __attribute__((weak_import)) __attribute__((weak)) __asm__("_" "PAL" "$" "__panic" "@" "0.0");
# 11 "PAL-stubs.c" 2
# 22 "PAL-stubs.c"
int
PAL_metaClass(const union UUID * const clsid, const union UUID * const iid, void **out)
{
 (void) (clsid);
 (void) (iid);
 (void) (out);

 return 7;
}




void
PAL_panic(const char *str)
{
 (void) (str);
}
