#include "../../sources.hpp"
#include "../../writer/writer.hpp"
#include "../../IO/IO.hpp"
#include "../keyboard/KeyboardLookupTableS1.hpp"
#include "../keyboard/Keyboard.hpp"
struct IDT64{
    uint16_t low_offset;
    uint16_t selector;
    uint8_t ist;
    uint8_t types_n_attr;
    uint16_t mid_offset;
    uint32_t high_offset;
    uint32_t zero;
};
extern IDT64 _idt[256];
extern uint64_t isr1;
extern "C" void InitIDTASM();

void Init_IDT(){
    Hprintln("Initializing IDT...\n");
    
    _idt[1].zero = 0;
    _idt[1].low_offset = (uint16_t)(((uint64_t)&isr1 & 0x000000000000ffff));
    _idt[1].mid_offset = (uint16_t)(((uint64_t)&isr1 & 0x00000000ffff0000) >> 16);
    _idt[1].high_offset = (uint32_t)(((uint64_t)&isr1 & 0xffffffff00000000) >> 32);
    _idt[1].ist = 0;
    _idt[1].selector = 0x08;
    _idt[1].types_n_attr = 0x8e;
    
    remap_PIC();

    outb(0x21, 0xfd);
    outb(0xa1, 0xff);
    InitIDTASM();
}

bool num_lock = false;
bool scroll_lock = false;
bool caps_lock = false;
bool shift = false;

void extern_keyboard_booleans(bool b1, bool b2 = false, bool b3 = false, bool b4 = false){
    num_lock = b1;
    scroll_lock = b2;
    caps_lock = b3;
    shift = b4;
}

extern "C" void isr1_handler(){
    uint8_t ScanCode = inb(0x60);
    uint8_t chr = 0;
    if(ScanCode == 0x45){
        num_lock = true;
    }
    if(ScanCode < 0x3a){
        if(!num_lock){
            chr = ScanCodeLookup[ScanCode];
        }else{
            chr = ScanCodeLookup[ScanCode];
            switch(ScanCode){
                case 0x47:
                    chr = '7';
                    break;
                case 0x48:
                    chr = '8';
                    break;
            }
        }
    }
    keyboard_handler_main(ScanCode, chr);
    outb(0x20, 0x20);
    outb(0xa0, 0x20);
}