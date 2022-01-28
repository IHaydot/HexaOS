#include "sources.h"
#include "writer/writer.h"
#include "writer/vga_colors.h"
extern "C" void _start(){
    cls();
    SetCursorPosition(0);
    Hprintln("Welcome to HexaOS!\nThis operating system is made by only one person so its not the most functional,but I hope it's atleast interesting to see!\n", VGA_COLOR_BACKGROUND_LIGHT_GREY | VGA_COLOR_FOREGROUND_BLACK);
    while(true){

    }   
}