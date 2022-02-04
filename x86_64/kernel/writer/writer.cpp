#include "../sources.hpp"
#include "../IO/IO.hpp"
#include "vga_colors.hpp"
#define VGA_START 0xb8000
#define VGA_COLOR 0x0f
#define CURSOR1 0x3d4
#define CURSOR2 0x3d5

namespace System
{

    uint16_t cursor_pos = 0;
    uint16_t vga_color = VGA_COLOR;
    uint16_t SetCursorPosFromWH(uint8_t width, uint8_t height)
    {
        return height * 80 + width;
    }

    void SetCursorPosition(uint16_t val)
    {
        outb(CURSOR1, 0x0f);
        outb(CURSOR2, (uint8_t)(val & 0xff));
        outb(CURSOR1, 0x0e);
        outb(CURSOR2, (uint8_t)((val >> 8) & 0xff));
        cursor_pos = val;
    }
    uint16_t strlen(const char *str)
    {
        uint16_t len = 0;
        while (str[len])
        {
            len++;
        }
        return len;
    }
    void Hprintln(const char *str, uint8_t color = VGA_COLOR_BACKGROUND_DARK_GREY | VGA_COLOR_FOREGROUND_BLACK)
    {
        char *mem = (char *)VGA_START;
        uint8_t *strPTR = (uint8_t *)str;
        uint16_t index = cursor_pos;
        while (*strPTR != 0)
        {
            switch (*strPTR)
            {
            case 10:
                index += 80;
                index -= index % 80;
                break;
            default:
                *(mem + index * 2) = *strPTR;
                *(mem + index * 2 + 1) = color;
                index++;
            }
            strPTR++;
        }
        SetCursorPosition(index);
    }

    char HexToStringOutput[128];
    const char *HexToString(uint8_t value)
    {
        uint8_t *vlptr = &value;
        uint8_t *ptr;
        uint8_t tmp;
        uint8_t size = (sizeof(uint8_t)) * 2 - 1;
        uint8_t i;
        for (i = 0; i < size; i++)
        {
            ptr = ((uint8_t *)vlptr + i);
            tmp = ((*ptr & 0xf0) >> 4);
            HexToStringOutput[size - (i * 2 + 1)] = tmp + (tmp > 9 ? 55 : 48);
            tmp = ((*ptr & 0x0f));
            HexToStringOutput[size - (i * 2 + 0)] = tmp + (tmp > 9 ? 55 : 48);
        }
        HexToStringOutput[size + 1] = 0;
        return HexToStringOutput;
    }

    void HprintCHR(char printee, uint8_t color = VGA_COLOR_BACKGROUND_DARK_GREY | VGA_COLOR_FOREGROUND_BLACK)
    {
        char *mem = (char *)VGA_START;
        *(mem + cursor_pos * 2) = printee;
        *(mem + cursor_pos * 2 + 1) = color;

        SetCursorPosition(cursor_pos + 1);
    }

    void cls(uint64_t color = VGA_COLOR_BACKGROUND_DARK_GREY | VGA_COLOR_FOREGROUND_BLACK)
    {
        uint64_t value = 0;
        value += color << 8;
        value += color << 24;
        value += color << 40;
        value += color << 56;
        for (uint64_t *i = (uint64_t *)0xb8000; i < (uint64_t *)(0xb8000 + 4000); i++)
        {
            *i = value;
        }
    }

    const char *HexToAscii(uint8_t value)
    {
        switch (value)
        {
        case 'q':
            return "q";
        }
    }

    void HandleBackspace()
    {
        char *mem = (char *)VGA_START;
        *(mem + cursor_pos * 2 - 2) = ' ';
        SetCursorPosition(cursor_pos - 1);
    }

    void HandleTab()
    {
        char *mem = (char *)VGA_START;
        *(mem + cursor_pos * 2 + 8) = ' ';
        SetCursorPosition(cursor_pos + 4);
    }

    char IntToStringOutput[128];
    const char* IntToString(int value){

        uint8_t Neg = 0;
        if(value < 0){
            Neg = 1;
            value *= -1;
            IntToStringOutput[0] = '-';
        }
        uint8_t size = 0;
        uint64_t STester = (uint64_t)value;
        while (STester / 10 > 0){
            STester /= 10;
            size++;
        }
        uint8_t ind = 0;
        uint64_t NewVal = (uint64_t)value;
        while(NewVal / 10 > 0){
            uint8_t remainder = NewVal % 10;
            NewVal /= 10;
            IntToStringOutput[Neg + size - ind] = remainder + 48;
            ind++;
        }
        uint8_t remainder = NewVal % 10;
        IntToStringOutput[Neg + size - ind] = remainder + 48;
        IntToStringOutput[Neg + size + 1] = 0;
        return IntToStringOutput;
    }

    char floatToStringOutput[128];
    const char* floatToString(float value, uint8_t decimals){
        uint8_t Neg = 0;
        char* intPTR = (char*)IntToString((int)value);
        char* floatPTR = floatToStringOutput;
        if(value < 0){
            Neg = 1;
            value *= -1;
            *floatPTR = '-';
        }
        while(*intPTR != 0){
            *floatPTR = *intPTR;
            floatPTR++;
            intPTR++;
        }
        *floatPTR = '.';
        floatPTR++;

        float NewVal = value - (int)value;

        for(uint8_t i = 0; i < decimals; i++){
            NewVal *= 10;
            *floatPTR = (int)NewVal + 48;
            NewVal -= (int)NewVal;
            floatPTR++;
        }

        return floatToStringOutput;
    }
}
