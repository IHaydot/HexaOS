#include "stddef.h"
namespace System{
    void* memset(void* destination, int value, size_t size);
    void* memcpy(void* destination, const void* src, size_t size);
    int memcmp(const void* a, const void* b, size_t size);
    int strcmp(const char* a, const char* b);
    int strncmp(const char* a, const char* b, size_t len);
}