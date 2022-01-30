#include "../../sources.h"
#include "../../writer/writer.h"
#include "../../IO/IO.h"
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
    for (uint64_t i = 0; i < 256; i++){
        _idt[i].zero = 0;
        _idt[i].low_offset = (uint16_t)(((uint64_t)&isr1 & 0x000000000000ffff));
        _idt[i].mid_offset = (uint16_t)(((uint64_t)&isr1 & 0x00000000ffff0000) >> 16);
        _idt[i].high_offset = (uint32_t)(((uint64_t)&isr1 & 0xffffffff00000000) >> 32);
        _idt[i].ist = 0;
        _idt[i].selector = 0x08;
        _idt[i].types_n_attr = 0x8e;
    }

    outb(0x21, 0xfd);
    outb(0xa1, 0xff);
    InitIDTASM();
}

extern "C" void isr1_handler(){
    Hprintln(HexToString(inb(0x60)));
    outb(0x20, 0x20);
    outb(0xa0, 0x20);
}