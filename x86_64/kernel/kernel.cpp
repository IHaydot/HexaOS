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

#define DEBUG
#define VGA_MAIN_BACKGROUND_COLOR 0x10
#define VGA_MAIN_FOREGROUND_COLOR 0x0f
#define VGA_MAIN_COLOR VGA_MAIN_BACKGROUND_COLOR | VGA_MAIN_FOREGROUND_COLOR

extern const char LOGO[];
///To give arguments to the assembly kernel, use the following register layout: ebx = mode(0xe9d for interrupts), rax for mode arguments(for instsance, in interrupt mode rax = 0x157 would mean interrupt 157 would be invoked)
///Example:
///asm volitile("mov $0x157, %rax"
///             "mov $0xe9d, %ebx");
///assembly_kernel();
namespace System
{
    void stack_overflow()
    {
        stack_overflow();
    }
    extern "C" void _start()
    {
        Init_IDT();
        srand(3289);
        cls(VGA_MAIN_BACKGROUND_COLOR, VGA_MAIN_FOREGROUND_COLOR);
        Hprintln("Welcome to HexaOS!\nThis operating system is made by only one person so its not the most functional,but I hope it's atleast interesting to see!\n");
        SetVGAColor(VGA_COLOR_BACKGROUND_BlUE, VGA_COLOR_FOREGROUND_GREEN);
        Hprintln(LOGO);
        SetVGAColor(VGA_MAIN_BACKGROUND_COLOR, VGA_MAIN_FOREGROUND_COLOR);
        Hprintln("\n");

        int157();

        HprintSU("Reached the end of the kernel!");
        

        while (true)
        {
        }
    }

}