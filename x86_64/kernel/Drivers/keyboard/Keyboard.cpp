#pragma once
#include "../../sources.hpp"
#include "../../writer/writer.hpp"
#include "../keyboard/Keyboard.hpp"
namespace System
{
    void keyboard_handler1(uint8_t key, uint8_t chr)
    {
        if (chr != 0)
        {
            HprintCHR(chr);
        }
    }

    void keyboard_handler_main(uint8_t ScanCode, uint8_t chr, uint8_t mode)
    {
        bool num_lock = false;
        bool scroll_lock = false;
        bool caps_lock = false;

        switch (mode)
        {
        case 1:
            switch (ScanCode)
            {
            case 0x3e:
                Hprintln("\nShutting down OS...");
                asm volatile("hlt");
            case 0x45:
                num_lock = !num_lock;
                break;
            case 0x46:
                scroll_lock = !scroll_lock;
                break;
            case 0x3a:
                caps_lock = !caps_lock;
                break;
            case 0x0e:
                HandleBackspace();
                break;
            case 0x1c:
                Hprintln("\n");
                break;
            case 0x0f:
                HandleTab();
            default:
                break;
            }
            keyboard_handler1(ScanCode, chr);
            break;
        default:
            Hprintln("Invalid keyboard handler mode");
            asm volatile("hlt");
        }
    }

}
