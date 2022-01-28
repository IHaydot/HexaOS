#include "../sources.h"
#include "../IO/IO.h"
#define VGA_START 0xb8000
#define VGA_COLOR 0x0f
#define CURSOR1 0x3d4
#define CURSOR2 0x3d5
uint16_t cursor_pos = 0;
uint16_t vga_color = VGA_COLOR;
uint16_t SetCursorPosFromWH(uint8_t width, uint8_t height){
    return height * 80 + width;
}

void SetCursorPosition(uint16_t val){
    outb(CURSOR1, 0x0f);
    outb(CURSOR2, (uint8_t)(val & 0xff));
    outb(CURSOR1, 0x0e);
    outb(CURSOR2, (uint8_t)((val >> 8) & 0xff));
    cursor_pos = val;
}
uint16_t strlen(const char *str){
    uint16_t len = 0;
    while(str[len]){
        len++;
    }
    return len;
}
void Hprintln(const char* str){
    char* mem = (char*) VGA_START;
    uint8_t* strPTR = (uint8_t*) str;
    uint16_t index = cursor_pos;
    while(*strPTR != 0){
        switch(*strPTR){
            case 10:
                index += 80 - index;
                break;
            default:
                *(mem + index * 2) = *strPTR;
                index++;
        }
        strPTR++;
    }
    SetCursorPosition(index);
}