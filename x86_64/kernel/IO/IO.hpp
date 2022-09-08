#pragma once
#include "../sources.hpp"
void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);
uint32_t inl(uint16_t port);
void outl(uint16_t port, uint32_t val);
void remap_PIC();