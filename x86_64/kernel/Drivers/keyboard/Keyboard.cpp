#pragma once
#include "../../sources.hpp"
#include "../../writer/writer.hpp"

void keyboard_handler1(uint8_t key, uint8_t chr){
    if(chr != 0){
        HprintCHR(chr);
    }
}

void keyboard_handler_main(uint8_t ScanCode, uint8_t chr, uint8_t mode = 1){
    switch(mode){
        case 1:
            keyboard_handler1(ScanCode, chr);
            break;
        default:
            Hprintln("Invalid keyboard handler mode");
            asm volatile ("hlt");
    }
}
