#include "sources.hpp"
#include "writer/writer.hpp"

namespace System
{
    void breakpoint()
    {
        asm volatile("int3");
    }
    void int157(){
        asm volatile("mov $0x157, %rax\n\t"
                     "mov $0xe9d, %ebx");
        assembly_kernel();
    }
}