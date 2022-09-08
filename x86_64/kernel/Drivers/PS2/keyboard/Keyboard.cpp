#pragma once
#include "../../../sources.hpp"
#include "../../../writer/writer.hpp"
#include "../keyboard/Keyboard.hpp"
#include "../../../Init/grub.hpp"
#include "../../../IO/IO.hpp"
#include "KeyboardLookupTableS1.hpp"

namespace System
{

    //bool num_lock = false; //Deal with these
    //bool scroll_lock = false; //later 
    //bool caps_lock = false; //Consentrate on this

    void keyboard_handler1(uint8_t key, uint8_t chr)
    {
        if (chr != 0)
        {
            HprintCHR(chr);
        }
    }

    void KeyboardHandlerPS2Boot(uint8_t ScanCode, uint8_t chr){
        switch(ScanCode){
            case 0x3e:
                Hprintln("\nShutting down the operating system...");
                hlt(); //I know this doesnt really shut down the os
                break;
            
        }
    }

    void keyboard_handler_main(uint8_t ScanCode, uint8_t chr, uint8_t mode)
    {
        previous_input = chr;
        number_of_inputs++;

        bool num_lock = false; //Deal with these
        bool scroll_lock = false; //later 
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
    char InputPS2(){
        long long num = number_of_inputs;
        while(num == number_of_inputs);
        HandleBackspace();
        return previous_input;
    }

}
