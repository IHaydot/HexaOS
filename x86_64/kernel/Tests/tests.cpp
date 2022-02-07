#include "../writer/writer.hpp"

namespace System{
    void test_dead_memory(){
        char* mem = (char*) 0xdeadbeef;
        *mem = 'D';
    }
    void dividing_test(){
        int i = 1 / 0;
        Hprintln(IntToString(i));
        Hprintln("\n");
    }
}