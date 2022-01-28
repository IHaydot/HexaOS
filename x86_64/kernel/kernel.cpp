#include "sources.h"
#include "writer/writer.h"
extern "C" void _start(){
    SetCursorPosition(0);
    Hprintln("Hello kernel!\n");
    while(true){

    }   
}