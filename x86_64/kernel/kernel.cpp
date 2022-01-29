#include "sources.h"
#include "writer/writer.h"
#include "writer/vga_colors.h"

#define VGA_MAIN_COLOR 0x80 | 0x00

extern const char LOGO[];
extern "C" void _start(){
    cls(VGA_MAIN_COLOR);
    Hprintln("Welcome to HexaOS!\nThis operating system is made by only one person so its not the most functional,but I hope it's atleast interesting to see!\n", VGA_MAIN_COLOR);
    Hprintln(LOGO, VGA_COLOR_BACKGROUND_DARK_GREY | VGA_COLOR_FOREGROUND_GREEN);
    while(true){

    }   
}