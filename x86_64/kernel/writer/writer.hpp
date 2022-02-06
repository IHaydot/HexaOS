#pragma once
#include "../sources.hpp"
#include "vga_colors.hpp"
namespace System
{
    void SetCursorPosition(uint16_t val);
    uint16_t strlen(const char *str);
    void Hprintln(const char *str, uint8_t color = VGA_COLOR_BACKGROUND_DARK_GREY | VGA_COLOR_FOREGROUND_BLACK);
    uint16_t SetCursorPosFromWH(uint8_t width, uint8_t height);
    void cls(uint64_t color = VGA_COLOR_BACKGROUND_DARK_GREY | VGA_COLOR_FOREGROUND_BLACK);
    const char *HexToString(uint8_t value);
    const char *HexToAscii(uint8_t value);
    void HprintCHR(char printee, uint8_t color = VGA_COLOR_BACKGROUND_DARK_GREY | VGA_COLOR_FOREGROUND_BLACK);
    void HandleBackspace();
    void HandleTab();
    const char* IntToString(int value);
    const char* floatToString(float value, uint8_t decimals = 3);
}