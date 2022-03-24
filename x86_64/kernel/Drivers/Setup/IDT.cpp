#include "../../sources.hpp"
#include "../../writer/writer.hpp"
#include "../../IO/IO.hpp"
#include "../PS2/keyboard/KeyboardLookupTableS1.hpp"
#include "../PS2/keyboard/Keyboard.hpp"
#include "../../cmds/boot/boot_cmd.hpp"
#include "../USB/Keyboard/keyboard.hpp"
struct IDT64
{
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
extern uint64_t general_handler;
extern uint64_t breakpoint_handler;
extern uint64_t division_handler;
extern uint64_t overflow_hanlder;
extern uint64_t double_fault_handler;
extern uint64_t page_fault_handler;
extern uint64_t cmd_handler;
extern uint64_t usb_init_handler;
extern "C" void InitIDTASM();
namespace System
{

    void Init_IDT()
    {
        Hprintln("Initializing IDT...\n");

        for(int i = 0; i < 257; i++){
            _idt[i].zero = 0;
            _idt[i].low_offset = (uint16_t)(((uint64_t)&general_handler & 0x000000000000ffff));
            _idt[i].mid_offset = (uint16_t)(((uint64_t)&general_handler & 0x00000000ffff0000) >> 16);
            _idt[i].high_offset = (uint32_t)(((uint64_t)&general_handler & 0xffffffff00000000) >> 32);
            _idt[i].ist = 0;
            _idt[i].selector = 0x08;
            _idt[i].types_n_attr = 0x8e;
        }

        _idt[0].zero = 0;
        _idt[0].low_offset = (uint16_t)(((uint64_t)&division_handler & 0x000000000000ffff));
        _idt[0].mid_offset = (uint16_t)(((uint64_t)&division_handler & 0x00000000ffff0000) >> 16);
        _idt[0].high_offset = (uint32_t)(((uint64_t)&division_handler & 0xffffffff00000000) >> 32);
        _idt[0].ist = 0;
        _idt[0].selector = 0x08;
        _idt[0].types_n_attr = 0x8e;

        _idt[1].zero = 0;
        _idt[1].low_offset = (uint16_t)(((uint64_t)&isr1 & 0x000000000000ffff));
        _idt[1].mid_offset = (uint16_t)(((uint64_t)&isr1 & 0x00000000ffff0000) >> 16);
        _idt[1].high_offset = (uint32_t)(((uint64_t)&isr1 & 0xffffffff00000000) >> 32);
        _idt[1].ist = 0;
        _idt[1].selector = 0x08;
        _idt[1].types_n_attr = 0x8e;

        _idt[3].zero = 0;
        _idt[3].low_offset = (uint16_t)(((uint64_t)&breakpoint_handler & 0x000000000000ffff));
        _idt[3].mid_offset = (uint16_t)(((uint64_t)&breakpoint_handler & 0x00000000ffff0000) >> 16);
        _idt[3].high_offset = (uint32_t)(((uint64_t)&breakpoint_handler & 0xffffffff00000000) >> 32);
        _idt[3].ist = 0;
        _idt[3].selector = 0x08;
        _idt[3].types_n_attr = 0x8e;

        _idt[4].zero = 0;
        _idt[4].low_offset = (uint16_t)(((uint64_t)&overflow_hanlder & 0x000000000000ffff));
        _idt[4].mid_offset = (uint16_t)(((uint64_t)&overflow_hanlder & 0x00000000ffff0000) >> 16);
        _idt[4].high_offset = (uint32_t)(((uint64_t)&overflow_hanlder & 0xffffffff00000000) >> 32);
        _idt[4].ist = 0;
        _idt[4].selector = 0x08;
        _idt[4].types_n_attr = 0x8e;

        _idt[8].zero = 0;
        _idt[8].low_offset = (uint16_t)(((uint64_t)&double_fault_handler & 0x000000000000ffff));
        _idt[8].mid_offset = (uint16_t)(((uint64_t)&double_fault_handler & 0x00000000ffff0000) >> 16);
        _idt[8].high_offset = (uint32_t)(((uint64_t)&double_fault_handler & 0xffffffff00000000) >> 32);
        _idt[8].ist = 0;
        _idt[8].selector = 0x08;
        _idt[8].types_n_attr = 0x8e;

        _idt[0x0e].zero = 0;
        _idt[0x0e].low_offset = (uint16_t)(((uint64_t)&page_fault_handler & 0x000000000000ffff));
        _idt[0x0e].mid_offset = (uint16_t)(((uint64_t)&page_fault_handler & 0x00000000ffff0000) >> 16);
        _idt[0x0e].high_offset = (uint32_t)(((uint64_t)&page_fault_handler & 0xffffffff00000000) >> 32);
        _idt[0x0e].ist = 0;
        _idt[0x0e].selector = 0x08;
        _idt[0x0e].types_n_attr = 0x8e;

        _idt[157].zero = 0;
        _idt[157].low_offset = (uint16_t)(((uint64_t)&cmd_handler & 0x000000000000ffff));
        _idt[157].mid_offset = (uint16_t)(((uint64_t)&cmd_handler & 0x00000000ffff0000) >> 16);
        _idt[157].high_offset = (uint32_t)(((uint64_t)&cmd_handler & 0xffffffff00000000) >> 32);
        _idt[157].ist = 0;
        _idt[157].selector = 0x08;
        _idt[157].types_n_attr = 0x8e;

        _idt[158].zero = 0;
        _idt[158].low_offset = (uint16_t)(((uint64_t)&usb_init_handler & 0x000000000000ffff));
        _idt[158].mid_offset = (uint16_t)(((uint64_t)&usb_init_handler & 0x00000000ffff0000) >> 16);
        _idt[158].high_offset = (uint32_t)(((uint64_t)&usb_init_handler & 0xffffffff00000000) >> 32);
        _idt[158].ist = 0;
        _idt[158].selector = 0x08;
        _idt[158].types_n_attr = 0x8e;

        remap_PIC();

        outb(0x21, 0xfd);
        outb(0xa1, 0xff);
        InitIDTASM();
    }

    bool num_lock = false;
    bool scroll_lock = false;
    bool caps_lock = false;
    bool shift = false;

    void extern_keyboard_booleans(bool b1, bool b2 = false, bool b3 = false, bool b4 = false)
    {
        num_lock = b1;
        scroll_lock = b2;
        caps_lock = b3;
        shift = b4;
    }

    extern "C" void general_handler_C(){
        HprintER("THE KERNEL HAS HIT AN UNDEFINED FAULT! EXITING THE KERNEL...");
        asm volatile("hlt");
    }

    extern "C" void breakpoint_handler_C(){
        Hprintln("\n");
        Hprintln("THE KERNEL HAS HIT A BREAKPOINT, NOTHING OUR OF THE ORDINARY. MOVING ON...\n");
    }

    extern "C" void division_handler_C(){
        HprintER("DIVISION BY ZERO HAS BEEN ATTEMPTED WHICH IS AN IMPOSSIBLE TASK! EXITING THE KERNEL...");
    }

    extern "C" void overflow_handler_C(){
        HprintER("A STACK OVERFLOW HAS HAPPENED, CURRENTLY THE SYSTEM CANNOT DO ANYTHING AGAINST THIS! EXITING THE KERNEL...");
    }

    extern "C" void double_fault_handler_C(){
        HprintER("A DOUBLE FAULT HAPPENED! EXITING THE KERNEL...");
    }

    extern "C" void page_fault_handler_C(){
        HprintER("A PAGE FAULT HAPPENED! EXITING THE KERNEL...");
    }

    extern "C" void usb_init_handler_C(){
        init_usb_keyboard();
    }

    extern "C" void isr1_handler()
    {
        uint8_t ScanCode = inb(0x60);
        uint8_t chr = 0;
        /*if (ScanCode == 0x45)
        {
            num_lock = true;
        }
        if (ScanCode < 0x3a)
        {
            if (!num_lock)
            {
                chr = ScanCodeLookup[ScanCode];
            }
            else
            {
                chr = ScanCodeLookup[ScanCode];
                switch (ScanCode)
                {
                case 0x47:
                    chr = '7';
                    break;
                case 0x48:
                    chr = '8';
                    break;
                }
            }
        }OLD KEYBOARD HANDLER */ 

        if(ScanCode < 0x3a){
            chr = ScanCodeLookup[ScanCode];
        }
        
        keyboard_handler_main(ScanCode, chr);
        outb(0x20, 0x20);
        outb(0xa0, 0x20);
    }

    extern "C" void cmd_handler_C(){
        Hprintln("CMD handler\n");
        boot_cmd_init();
    }
}