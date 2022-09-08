#pragma once
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
typedef unsigned long uint64_h;
typedef unsigned long usize;
typedef char STATUS;
typedef char Privilige;
typedef const char *ID;
#define NULL 0
#define endl '\n'
#include "multiboot2.h"
#define VGA_START 0xb8000
#define likely(x)       __builtin_expect((x),1)
#define unlikely(x)     __builtin_expect((x),0)

typedef uint32_t Filesystem;

namespace System
{
    static uint64_t VIDEO_MEMORY_START = VGA_START;
    static uint64_t VIDEO_MEMORY_END = VGA_START + 4000;
    extern "C" void assembly_kernel();
    static bool IsInDebug = true;
    extern "C" uint32_t grub_magic;
    extern "C" uint32_t grub_info;
    static struct multiboot_tag *tag;
    static unsigned size;
    static multiboot_uint32_t mem_lower;
    static multiboot_uint32_t mem_higher;
    static multiboot_memory_map_t *mmap;
    static uint32_t cr2;
    static STATUS SUCCESS = 0x6CCE6;
    static STATUS FAILURE = 0xFAE8E;
    static Privilige KernelPRV = 0xcee9e3;
    static Privilige UserPRV = 0x8ce3c;
    static bool Success(STATUS arg)
    {
        if (arg == SUCCESS)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    static void hlt()
    {
        while (true)
        {
            asm volatile("hlt");
        }
    }

    static multiboot_memory_map_t *first_free_map = 0;
    static multiboot_memory_map_t *current_free_map = 0;
    static const uint64_t LIMIT_32 = 2147483647;
    static uint8_t VGA_MAIN_BACKGROUND_COLOR = 0x80;
    static uint8_t VGA_MAIN_FOREGROUND_COLOR = 0x0f;
    static char previous_input = '1';
    static float time_since_last_input = 0.01f;
    static long long number_of_inputs = 0;
    static void *keyboard_handler;
    

    enum Registers
    {
        cr3 = 0xc3,
    };

    class Regs
    {
    public:
        uint64_t read(Registers reg)
        {
            uint64_t cr3;
             asm volatile("mov %%cr3, %%rax\n\t"
                        "mov %%eax, %0" : "=m" (cr3));
            return cr3;
        }
    };
    static ID KERNEL_ID = "zX#;z_pq@vLEAN&&";

    enum Filesystem_list{
        ISO9660 = 0x00,
        FAT12 = 0xf12,
        FAT32 = 0xf32,
        FAT64 = 0xf64,
        ExFAT = 0xefa
    };
}
