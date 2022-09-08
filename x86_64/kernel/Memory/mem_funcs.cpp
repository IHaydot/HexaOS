#include "stddef.h"
#include "../sources.hpp"
#include "mem_funcs.hpp"
#include "../writer/writer.hpp"
namespace System{
    void* memset(void* destination, int value, size_t size){
        if(size == 0)return NULL;
        if(destination < 0){
            return NULL;
        }
        uint8_t* ptr = (uint8_t*)destination;
        while(size--){
            *ptr++ = value;
        }
        return destination;
    }
    void* memcpy(void* destination, const void* src, size_t size){
        if(size == 0)return NULL;
        if(destination < 0 or src < 0){
            return NULL;
        }
        for(int i = 0; size--; i++){
            uint8_t* dest_ptr = (uint8_t*)destination;
            uint8_t* src_ptr = (uint8_t*)src;
            dest_ptr[i] = src_ptr[i];
        }

        return destination;
    }

    int memcmp(const void* a, const void* b, size_t size){
        if(size == 0 or a < 0 or b < 0) return 0;
        for(int i = 0; size--; i++){
            uint8_t* a_ptr = (uint8_t*)a;
            uint8_t* b_ptr = (uint8_t*)b;
            if(a_ptr[i] != b_ptr[i]){
                if(a_ptr[i] > b_ptr[i])return 1; else return -1;
            }else continue;
        }
        return 0;
    }

    int strcmp(const char* a, const char* b){
        if(strlen(a) == 0 or strlen(b) == 0) return 0;
        else if(strlen(a) > strlen(b) or strlen(a) < strlen(b)) return 1;
        for(int i = 0; i < strlen(a); i++){
            if(a[i] == b[i])continue;
            return 1;
        }
        return 0;
    }

    int strncmp(const char* a, const char* b, size_t len){
        if(strlen(a) == 0 or strlen(b) == 0 or strlen(a) < len or strlen(b) < len) return 0;
        for(int i = 0; len--; i++){
            if(a[i] == b[i])continue;
            return 1;
        }
        return 0;
    }
}