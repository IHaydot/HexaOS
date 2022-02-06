#include "sources.hpp"
#include "writer/writer.hpp"
#include "writer/vga_colors.hpp"
#include "Drivers/Setup/IDT.hpp"
#include "Drivers/keyboard/Keyboard.hpp"

#define VGA_MAIN_BACKGROUND_COLOR 0x80
#define VGA_MAIN_FOREGROUND_COLOR 0x00
#define VGA_MAIN_COLOR VGA_MAIN_BACKGROUND_COLOR | VGA_MAIN_FOREGROUND_COLOR
extern const char LOGO[];
namespace System
{
    extern "C" void _start()
    {
        cls(VGA_MAIN_COLOR);
        Hprintln("Welcome to HexaOS!\nThis operating system is made by only one person so its not the most functional,but I hope it's atleast interesting to see!\n", VGA_MAIN_COLOR);
        Hprintln(LOGO, VGA_MAIN_BACKGROUND_COLOR | VGA_COLOR_FOREGROUND_GREEN);
        Hprintln("\n");
        Init_IDT();
        float t = -10.0 / 3.0;
        Hprintln(floatToString(t));
        Hprintln("\n");

        while (true)
        {
        }
    }
}