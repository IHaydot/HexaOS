#pragma once
#include "stddef.h"
#include "../../sources.hpp"
#include "../../writer/writer.hpp"

namespace System{
    extern "C" void ata_read_sectors_via_lba();
    extern "C" uint32_t _ata_read_sectors_via_lba_arg = 0;

    class Filesystems{
    private:
        Filesystem current_filesystem = Filesystem_list::ISO9660;
        
    public:
        uint32_t bootdev = 0;
        Filesystems(){
            
        }

        explicit Filesystems(uint32_t bootdev) : bootdev(bootdev){}

        explicit Filesystems(Filesystem fs) : current_filesystem(fs){}

        Filesystems(uint32_t bootdev, Filesystem fs) : bootdev(bootdev), current_filesystem(fs){} 

        void get_bootdev(uint32_t bootdev){
            Filesystems::bootdev = bootdev;
        }


    }; 
}