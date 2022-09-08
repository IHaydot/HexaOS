//! NO LONGER UPDATED AS THE OPERATING SYSTEM NOW BOOTS FROM ISO9660
/*
#include "stddef.h"
#include "../../../sources.hpp"
#include "fat12.hpp"
#include "../../../writer/writer.hpp"

//  eax - cylinder
//  ebx - head
//  ecx - sector
extern "C" void ata_read_lba_via_chs();

extern "C" uint32_t o_cylinder = 0;
extern "C" uint32_t o_head = 0;
extern "C" uint32_t o_sector = 0;

namespace System{
    void FAT::get_bootdev(uint32_t device){
        FAT::bootdev = device;
    }
    
}*/