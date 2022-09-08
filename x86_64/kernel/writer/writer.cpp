#include "../sources.hpp"
#include "../IO/IO.hpp"
#include "vga_colors.hpp"
#include "../extras/random.hpp"
#include "stddef.h"
#define VGA_START 0xb8000
#define VGA_COLOR 0x0f
#define CURSOR1 0x3d4
#define CURSOR2 0x3d5
#pragma once

namespace System
{
    //--------------------------VGA---------------------------
    static uint16_t current_color;
    static uint8_t current_background_color;
    static uint8_t current_foreground_color;
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
    void Hprintln(const char *str)
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
                *(mem + index * 2 + 1) = current_color;
                index++;
            }
            strPTR++;
        }
        SetCursorPosition(index);
    }

    void HprintCHR(char printee)
    {
        char *mem = (char *)VGA_START;
        *(mem + cursor_pos * 2) = printee;
        *(mem + cursor_pos * 2 + 1) = current_color;

        SetCursorPosition(cursor_pos + 1);
    }

    uint16_t VGAColorFrom(uint8_t background, uint8_t foreground){

        return background | foreground;
    }

    void SetVGAColor(uint8_t background, uint8_t foreground){
        current_color = VGAColorFrom(background, foreground);
        current_background_color = background;
        current_foreground_color = foreground;
    }


    void cls(uint8_t background = current_background_color, uint8_t foreground = current_foreground_color)
    {
        uint64_t color = VGAColorFrom(background, foreground);
        uint64_t value = 0;
        value += color << 8;
        value += color << 24;
        value += color << 40;
        value += color << 56;
        for (uint64_t *i = (uint64_t *)0xb8000; i < (uint64_t *)(0xb8000 + 4000); i++)
        {
            *i = value;
        }
        SetCursorPosition(0);
        current_background_color = background;
        current_foreground_color = foreground;
        current_color = color;
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
    const char* floatToString(float value, uint8_t decimals = 3){
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
    void HprintSU(const char* str){
        uint8_t background = current_background_color;
        uint8_t foreground = current_foreground_color;
        SetVGAColor(current_background_color, VGA_COLOR_FOREGROUND_GREEN);
        Hprintln("\n");
        Hprintln(str);
        Hprintln("\n");
        SetVGAColor(background, foreground);
    }

    void nln(){
        Hprintln("\n");
    }

    void println(const char* message){
        Hprintln(message); nln();
    }

    void HprintC(const char* msg, uint8_t background, uint8_t foreground){
        uint8_t backgroundB = current_background_color;
        uint8_t foregroundB = current_foreground_color;
        SetVGAColor(background, foreground);
        println(msg);
        SetVGAColor(backgroundB, foregroundB);
    }
    void HprintER(const char *str){
        uint8_t backgroundB = current_background_color;
        uint8_t foregroundB = current_foreground_color;
        SetVGAColor(current_background_color, VGA_COLOR_FOREGROUND_RED);
        println(str);
        SetVGAColor(backgroundB, foregroundB);
    }
    
    char* formatOutput;
    ///everything will be formatted to the previous value
    const char* format(const char* a, const char* b = 0, const char* c = 0, const char* d = 0){
        //formatOutput = (char*)malloc(sizeof(const char*) * 100);
        if(a == 0){
            return "need more values to format!";
        }
        const char* new_str;
        uint8_t* aPTR = (uint8_t*)a;
        int index = 0;
        while(*aPTR != 0){
            formatOutput[index] = *aPTR;
            aPTR++;
            index++;
        }
        if(b != 0){
            uint8_t* bPTR = (uint8_t*)b;
            while(*bPTR != 0){
                formatOutput[index] = *bPTR;
                bPTR++;
                index++;
            }
        }
        if(c != 0){
            uint8_t* cPTR = (uint8_t*)c;
            while(*cPTR != 0){
                formatOutput[index] = *cPTR;
                cPTR++;
                index++;
            }
        }
        if(d != 0){
            uint8_t* dPTR = (uint8_t*)d;
            while(*dPTR != 0){
                formatOutput[index] = *dPTR;
                dPTR++;
                index++;
            }
        }

        return formatOutput;
    }

    void NFTGeneratorOSINitVGA(){
        char* mem_start = (char*) VIDEO_MEMORY_START;

        for(int i = 0; i < VIDEO_MEMORY_END; i++){
            uint8_t fcolor = rand_in_range(0x00, 0x0f, 0);
            uint8_t bcolor = rand_in_range(0x00, 0xf0, 0);
            int rand = rand_in_range(0, 15, 0);
            char* cchar = (char*) random_pass_generator(1, 0);
            mem_start[i * 2] = *cchar;
            mem_start[i * 2 + 1] = VGAColorFrom(bcolor, fcolor);
            //NFT generator OS :D
        }
    }

    void printArr(char arr[], size_t size){
        for(int i = 0; i < size; i++){
            println((const char*)arr[i]);
        }
    }

    //--------------------------VBE---------------------------
    //TODO

}


