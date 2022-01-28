extern "C" void _start(){
    char* mem = (char*) 0xb8000;
    *mem = 'D';
}