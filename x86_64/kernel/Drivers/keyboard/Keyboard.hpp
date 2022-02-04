#pragma once
#include "../../sources.hpp"
namespace System
{
    void keyboard_handler1(uint8_t key, uint8_t chr);
    void keyboard_handler_main(uint8_t ScanCode, uint8_t chr, uint8_t mode = 1);
}