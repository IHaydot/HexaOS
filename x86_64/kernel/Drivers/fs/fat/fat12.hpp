//!  NO LONGER UPDATED AS THE OPERATING SYSTEM NOW BOOTS FROM ISO9660
/*
#pragma once
#include "stddef.h"
#include "../../../sources.hpp"
#include "../../../writer/writer.hpp"

namespace System{
    class FAT{
    private:
        int cylinder = 0;
        int head = 0;
        int sector = 0;
    public:
        uint32_t bootdev = 0;
        FAT(){
            println(format("Hello default FAT!"));
        }

        explicit FAT(int sector) : sector(sector){
            println(format("Hello explicit FAT with sector: ", IntToString(FAT::sector)));
        }

        FAT(int cylinder, int head, int sector) : cylinder(cylinder), head(head), sector(sector){
            println("Hello all FAT!");
        }

        void get_bootdev(uint32_t bootdev);
    };
}*/