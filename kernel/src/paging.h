#ifndef PAGING_H
#define PAGING_H

#include "stdlib/include/stdlib.h"

typedef uint32 page_t; // 20 MSB bytes, frame addr and 12 LSB bytes for flags

typedef struct {
    page_t pages[1024];
} page_table_t;

typedef struct {
    page_table_t* tables[1024];
} page_directory_t;

void initialise_paging();
uint32 kmalloc(uint32 sz);

#endif
