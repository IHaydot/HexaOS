#pragma once
#include "../sources.h"
#include "vga_colors.h"
void SetCursorPosition(uint16_t val);
uint16_t strlen(const char *str);
void Hprintln(const char* str, uint8_t color = VGA_COLOR_BACKGROUND_BlUE | VGA_COLOR_FOREGROUND_WHITE);
uint16_t SetCursorPosFromWH(uint8_t width, uint8_t height);
void cls(uint64_t color = VGA_COLOR_BACKGROUND_LIGHT_GREY | VGA_COLOR_FOREGROUND_BLACK);
//template <typename T>
//const char* HexToString(T value); 