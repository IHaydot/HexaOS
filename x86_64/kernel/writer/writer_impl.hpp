#pragma once
#include "../sources.hpp"
namespace System
{
    char HexToStringOutput[128];
    template <typename T>
        const char *HexToString(T value)
        {
            T *vlptr = &value;
            uint8_t *ptr;
            uint8_t tmp;
            uint8_t size = (sizeof(T)) * 2 - 1;
            uint8_t i;
            for (i = 0; i < size; i++)
            {
                ptr = ((uint8_t *)vlptr + i);
                tmp = ((*ptr & 0xf0) >> 4);
                HexToStringOutput[size - (i * 2 + 1)] = tmp + (tmp > 9 ? 55 : 48);
                tmp = ((*ptr & 0x0f));
                HexToStringOutput[size - (i * 2 + 0)] = tmp + (tmp > 9 ? 55 : 48);
            }
            HexToStringOutput[size + 1] = 0;
            return HexToStringOutput;
        }
}