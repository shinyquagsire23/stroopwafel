#ifndef WAFEL_PATCH_H
#define WAFEL_PATCH_H

#include <string.h>
#include "ios_dynamic.h"
#include "latte/cache.h"

#define _U32_PATCH(_addr, _val, _copy_fn) { \
    _copy_fn((uintptr_t)_addr, (u32)_val); \
}
#define _ASM_PATCH(_addr, _str, _copy_fn) { \
    __asm__ volatile (           \
    ".globl pre_" #_addr "\n"    \
    ".globl post_" #_addr "\n"   \
    "b post_" #_addr "\n"        \
    "pre_" #_addr ":\n"          \
    ".arm\n"                     \
    _str "\n"                    \
     ".arm\n"                    \
    "post_" #_addr ":\n");       \
    extern void pre_##_addr();   \
    extern void post_##_addr();  \
    _copy_fn((uintptr_t)_addr, (uintptr_t)pre_##_addr, (u32)post_##_addr - (u32)pre_##_addr); \
}
#define _BL_TRAMPOLINE(_addr, _dst, _copy_fn) { \
    u32 bl_offs = (((u32)_dst - (u32)(_addr)) - 8) / 4; \
    u32 bl_insn = 0xEB000000 | (bl_offs & 0xFFFFFF); \
    _U32_PATCH(_addr, bl_insn, _copy_fn); \
}
#define _BL_T_TRAMPOLINE(_addr, _dst, _copy_fn) { \
    u32 bl_offs = (((u32)_dst - (u32)(_addr)) - 4) / 2; \
    u32 bl_insn = 0xF000F800 | (bl_offs & 0x7FF) | (((bl_offs >> 11) & 0x3FF) << 16); \
    _U32_PATCH(_addr, bl_insn, _copy_fn); \
}
#define _BRANCH_PATCH(_addr, _dst, _copy_fn) { \
    u32 bl_offs = (((u32)_dst - (u32)(_addr)) - 8) / 4; \
    u32 bl_insn = 0xEA000000 | (bl_offs & 0xFFFFFF); \
    _U32_PATCH(_addr, bl_insn, _copy_fn); \
}

#define ARRARG(...) {__VA_ARGS__}
#define _SEARCH_PATCH(_search, _start_addr, _next_macro, ...) {                                            \
    u8 search[] = ARRARG _search;                                                                          \
    uintptr_t _addr = (uintptr_t)boyer_moore_search((void*)_start_addr, 0x200000, search, sizeof(search)); \
    if (!_addr) {                                                                                          \
        debug_printf("Failed to find search pattern!\n");                                                  \
        for (int i = 0; i < sizeof(search); i++) {                                                         \
            debug_printf("%02x ", search[i]);                                                              \
        }                                                                                                  \
        debug_printf("\n");                                                                                \
        while(1);                                                                                          \
    }                                                                                                      \
    _next_macro(_addr, __VA_ARGS__);                                                                       \
}

//
// Pre-MMU -- Lookups done manually
//
static void _patch_u32_k(uintptr_t addr, u32 val)
{
    memcpy((void*)ios_elf_vaddr_to_paddr(addr), &val, sizeof(u32));
}

static void _patch_copy_k(uintptr_t dst, uintptr_t src, size_t sz)
{
    memcpy((void*)ios_elf_vaddr_to_paddr(dst), (void*)src, sz);
}

#define U32_PATCH_K(_addr, _val) _U32_PATCH(_addr, _val, _patch_u32_k)
#define ASM_PATCH_K(_addr, _str) _ASM_PATCH(_addr, _str, _patch_copy_k)
#define BL_TRAMPOLINE_K(_addr, _dst) _BL_TRAMPOLINE(_addr, _dst, _patch_u32_k)
#define BL_T_TRAMPOLINE_K(_addr, _dst) _BL_T_TRAMPOLINE(_addr, _dst, _patch_u32_k)
#define BRANCH_PATCH_K(_addr, _dst) _BRANCH_PATCH(_addr, _dst, _patch_u32_k)

#define MEMCPY_SK(_search, _start_addr, ...) _SEARCH_PATCH(_search, _start_addr, MEMCPY_K, __VA_ARGS__)
#define U32_PATCH_SK(_search, _start_addr, ...) _SEARCH_PATCH(_search, _start_addr, U32_PATCH_K, __VA_ARGS__)
#define ASM_PATCH_SK(_search, _start_addr, ...) _SEARCH_PATCH(_search, _start_addr, ASM_PATCH_K, __VA_ARGS__)
#define BL_TRAMPOLINE_SK(_search, _start_addr, ...) _SEARCH_PATCH(_search, _start_addr, BL_TRAMPOLINE_K, __VA_ARGS__)
#define BL_T_TRAMPOLINE_SK(_search, _start_addr, ...) _SEARCH_PATCH(_search, _start_addr, BL_T_TRAMPOLINE_K, __VA_ARGS__)
#define BRANCH_PATCH_SK(_search, _start_addr, ...) _SEARCH_PATCH(_search, _start_addr, BRANCH_PATCH_K, __VA_ARGS__)


//
// Post-MMU
//
static void _patch_u32(uintptr_t addr, u32 val)
{
    memcpy((void*)addr, &val, sizeof(u32));
    dc_flushrange((void*)addr, sizeof(u32));
}

static void _patch_copy(uintptr_t dst, uintptr_t src, size_t sz)
{
    memcpy((void*)dst, (void*)src, sz);
    dc_flushrange((void*)dst, sizeof(u32));
}
#define MEMCPY_PATCH(_addr, _dst, _sz) _patch_copy(_addr, _dst, _sz)
#define U32_PATCH(_addr, _val) _U32_PATCH(_addr, _val, _patch_u32)
#define ASM_PATCH(_addr, _str) _ASM_PATCH(_addr, _str, _patch_copy)
#define BL_TRAMPOLINE(_addr, _dst) _BL_TRAMPOLINE(_addr, _dst, _patch_u32)
#define BL_T_TRAMPOLINE(_addr, _dst) _BL_T_TRAMPOLINE(_addr, _dst, _patch_u32)
#define BRANCH_PATCH(_addr, _dst) _BRANCH_PATCH(_addr, _dst, _patch_u32)

#define MEMCPY_S(_search, _start_addr, ...) _SEARCH_PATCH(_search, _start_addr, MEMCPY, __VA_ARGS__)
#define U32_PATCH_S(_search, _start_addr, ...) _SEARCH_PATCH(_search, _start_addr, U32_PATCH, __VA_ARGS__)
#define ASM_PATCH_S(_search, _start_addr, ...) _SEARCH_PATCH(_search, _start_addr, ASM_PATCH, __VA_ARGS__)
#define BL_TRAMPOLINE_S(_search, _start_addr, ...) _SEARCH_PATCH(_search, _start_addr, BL_TRAMPOLINE, __VA_ARGS__)
#define BL_T_TRAMPOLINE_S(_search, _start_addr, ...) _SEARCH_PATCH(_search, _start_addr, BL_T_TRAMPOLINE, __VA_ARGS__)
#define BRANCH_PATCH_S(_search, _start_addr, ...) _SEARCH_PATCH(_search, _start_addr, BRANCH_PATCH, __VA_ARGS__)


#endif // WAFEL_PATCH_H