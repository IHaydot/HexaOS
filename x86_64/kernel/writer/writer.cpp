#include "../sources.h"
#include "../IO/IO.h"
#define VGA_START 0xb8000
#define VGA_COLOR 0x0f
#define CURSOR1 0x3d4
#define CURSOR2 0x3d5
void SetCursorPosition(uint16_t val){
    outb(CURSOR1, 0x0f);
    outb(CURSOR2, (uint8_t)(val & 0xff));
    outb(CURSOR1, 0x0e);
    outb(CURSOR2, (uint8_t)((val >> 8) & 0xff));
}