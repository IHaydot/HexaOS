#include "../multiboot2.h"
#include "../sources.hpp"
#include "../writer/writer.hpp"
#include "../Time/time.hpp"
#include "../Drivers/fs/fs.hpp"

namespace System{
    void InitMultiboot2(Filesystems* fs){
        for(tag = (struct multiboot_tag *)(grub_info + 8); tag->type != MULTIBOOT_TAG_TYPE_END; tag = (struct multiboot_tag *)((multiboot_uint8_t *) tag + ((tag->size + 7) & ~7))){
            switch(tag->type){
                case MULTIBOOT_TAG_TYPE_BASIC_MEMINFO:
                    mem_lower = ((struct multiboot_tag_basic_meminfo *) tag)->mem_lower;
                    mem_higher = ((struct multiboot_tag_basic_meminfo *) tag)->mem_upper;
                    //Hprintln("Mem be like:\n");
                    break;
                case MULTIBOOT_TAG_TYPE_MMAP:
                    for(mmap = ((struct multiboot_tag_mmap *) tag)->entries; 
                        (multiboot_uint8_t *) mmap < (multiboot_uint8_t *) tag + tag->size;
                        mmap = (multiboot_memory_map_t *)((uint64_h)mmap + ((struct multiboot_tag_mmap *)tag)->entry_size)){
                        Hprintln("Memory map starting addr: "); Hprintln(HexToString(mmap->addr)); nln();
                        //Hprintln("Memory map ending addr: "); Hprintln(HexToString(mmap->addr + mmap->len)); nln();
                        //Hprintln(IntToString(mmap->type)); nln();
                        //wait(2);
                        if(mmap->type == 1 and mmap->addr == 0x0){
                            println("Found the first memory map!");
                            first_free_map->addr = mmap->addr;
                            first_free_map->len = mmap->len;
                            first_free_map->type = mmap->type;
                            first_free_map->zero = mmap->zero;
                            
                        }else if(mmap->type == 1 and mmap->addr != 0x0){
                            println("Found a secondary memory map!");
                            if(first_free_map == 0) first_free_map = mmap;
                        }

                    }
                    break;
                
                case MULTIBOOT_TAG_TYPE_BOOTDEV:

                    fs->get_bootdev(((multiboot_tag_bootdev*) tag)->biosdev);

                    break;
            }
        }
        nln();
    }
}