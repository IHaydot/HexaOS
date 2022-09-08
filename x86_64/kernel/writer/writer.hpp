#pragma once
#include "../sources.hpp"
#include "vga_colors.hpp"
#include "stddef.h"
#define VGA_START 0xb8000
namespace System
{
    void SetCursorPosition(uint16_t val);
    uint16_t strlen(const char *str);
    void Hprintln(const char *str);
    uint16_t SetCursorPosFromWH(uint8_t width, uint8_t height);
    const char *HexToAscii(uint8_t value);
    void HprintCHR(char printee);
    void HandleBackspace();
    void HandleTab();
    const char *IntToString(int value);
    const char *floatToString(float value, uint8_t decimals = 3);
    void HprintER(const char *str);
    void SetVGAColor(uint8_t background, uint8_t foreground);
    /*char hexToStringOutput[128];
    template <typename T>
    const char *HexToString(T value)
    {
        T *valPtr = &value;
        uint8_t *ptr;
        uint8_t temp;
        uint8_t size = (sizeof(T)) * 2 - 1;
        uint8_t i;
        for (i = 0; i < size; i++)
        {
            ptr = ((uint8_t *)valPtr + i);
            temp = ((*ptr & 0xF0) >> 4);
            hexToStringOutput[size - (i * 2 + 1)] = temp + (temp > 9 ? 55 : 48);
            temp = ((*ptr & 0x0F));
            hexToStringOutput[size - (i * 2 + 0)] = temp + (temp > 9 ? 55 : 48);
        }
        hexToStringOutput[size + 1] = 0;
        return hexToStringOutput;
    }*/
    static uint16_t current_color;
    static uint8_t current_background_color;
    static uint8_t current_foreground_color;
    uint16_t VGAColorFrom(uint8_t background, uint8_t foreground);
    void HprintSU(const char *str);
    static char hexToStringOutput[128];
    template <typename T>
    const char *HexToString(T value)
    {
        T *valPtr = &value;
        uint8_t*ptr;
        uint8_t temp;
        uint8_t size = (sizeof(T)) * 2 - 1;
        uint8_t i;
        for (i = 0; i < size; i++)
        {
            ptr = ((uint8_t*)valPtr + i);
            temp = ((*ptr & 0xF0) >> 4);
            hexToStringOutput[size - (i * 2 + 1)] = temp + (temp > 9 ? 55 : 48);
            temp = ((*ptr & 0x0F));
            hexToStringOutput[size - (i * 2 + 0)] = temp + (temp > 9 ? 55 : 48);
        }
        hexToStringOutput[size + 1] = 0;
        return hexToStringOutput;
    }
    void nln();
    void cls(uint8_t background = current_background_color, uint8_t foreground = current_foreground_color);
    void println(const char* message);
    void HprintC(const char* msg, uint8_t background, uint8_t foreground);
    const char* format(const char* a, const char* b = 0, const char* c = 0, const char* d = 0);
    void NFTGeneratorOSINitVGA();
    void printArr(char arr[], size_t size);
}