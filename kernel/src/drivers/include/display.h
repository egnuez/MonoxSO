#ifndef DISPLAY_H
#define DISPLAY_H

#include "../../stdlib/include/stdlib.h"

void clear_screen();
void printch(char c);
void print(char *ch);
void print_hex(uint8 key);
void print_hex16(uint16 key);
void print_hex32(uint32 key);
void printf(const char *format, ...);

#endif
