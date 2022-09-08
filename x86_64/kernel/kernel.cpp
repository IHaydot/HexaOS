#include "multiboot2.h"
#include "sources.hpp"
#include "writer/writer.hpp"
#include "writer/vga_colors.hpp"
#include "Drivers/Setup/IDT.hpp"
#include "Drivers/PS2/keyboard/Keyboard.hpp"
#include "Tests/tests.hpp"
#include "cmds/boot/boot_cmd.hpp"
#include "instructions.hpp"
#include "Drivers/USB/Keyboard/keyboard.hpp"
#include "extras/random.hpp"
#include "Init/grub.hpp"
#include "Maths/Basics.hpp"
#include "Time/time.hpp"
#include "Memory/mem_funcs.hpp"
#include "Drivers/fs/fs.hpp"

#define DEBUG
#define VGA_MAIN_COLOR VGA_MAIN_BACKGROUND_COLOR | VGA_MAIN_FOREGROUND_COLOR

extern const char LOGO[];
extern const char HOMER[];
/// To give arguments to the assembly kernel, use the following register layout: ebx = mode(0xe9d for interrupts), rax for mode arguments(for instsance, in interrupt mode rax = 0x157 would mean interrupt 157 would be invoked)
/// Example:
/// asm volitile("mov $0x157, %rax"
///              "mov $0xe9d, %ebx");
/// assembly_kernel();

namespace System
{
    void stack_overflow()
    {
        stack_overflow();
    }

    extern "C" [[noreturn]] void _start()
    {
        Math math;
        Time time = get_time();
        Regs registers;

        Init_IDT();
        srand(time.second * time.minute - 54 + 0xaf);
        cls(VGA_MAIN_BACKGROUND_COLOR, VGA_MAIN_FOREGROUND_COLOR);
        Hprintln("Welcome to HexaOS!\nThis operating system is made by only one person so its not the most functional,but I hope it's atleast interesting to see!\n");
        SetVGAColor(VGA_MAIN_BACKGROUND_COLOR, VGA_COLOR_FOREGROUND_GREEN);
        Hprintln(LOGO);
        SetVGAColor(VGA_MAIN_BACKGROUND_COLOR, VGA_MAIN_FOREGROUND_COLOR);
        Hprintln("\n");

        int157(); //BOOTCMD

        if (unlikely(grub_magic != MULTIBOOT2_BOOTLOADER_MAGIC))
        {
            HprintER("For some reason the magic number provided by GRUB is incorrect meaning proceeding would lead to undefined behavior, here is what has been given to the kernel: ");
            Hprintln(IntToString(grub_magic));
            while (true)
            {
            }
        }
        else if (unlikely(grub_info & 7))
        {
            HprintER("Invalid GRUB informational structures provided to the kernel, proceeding is impossible. ADDR: ");
            Hprintln(IntToString(grub_info));
            while (true)
            {
            }
        }

        if(unlikely(InputPS2() == 'n')){
            cls(VGA_MAIN_BACKGROUND_COLOR, VGA_MAIN_FOREGROUND_COLOR);
        }

        size = *(unsigned *)grub_info;
        Hprintln("GRUB info structure size: ");
        Hprintln(IntToString(size));
        Hprintln("\n");

        cls(VGA_MAIN_BACKGROUND_COLOR, VGA_MAIN_FOREGROUND_COLOR);

        Filesystems fs;

        InitMultiboot2((Filesystems*)&fs);

        wait(1);

        HprintSU("Reached the end of the kernel!");

        println(HOMER);

        while (true);
    }

    
}