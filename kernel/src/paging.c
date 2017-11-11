#include "paging.h"
#include "stdlib/include/stdlib.h"

extern uint32 end__;
uint32 placement_address = (uint32)&end__;
page_directory_t* current_directory;


void memsetb(uint8 *dest, uint8 val, uint32 len)
{
    uint8 *temp = (uint8 *)dest;
    for ( ; len != 0; len--) *temp++ = val;
}

uint32 kmalloc(uint32 sz)
{
    if (placement_address & 0x00000FFF)
    {
        // Align the placement address;
        placement_address &= 0xFFFFF000;
        placement_address += 0x1000;
    }
    uint32 tmp = placement_address;
    placement_address += sz;
    return tmp;
}

void switch_page_directory(page_directory_t* dir)
{
    current_directory = dir;
    asm volatile("mov %0, %%cr3":: "r"(&dir->tables));
    uint32 cr0;
    asm volatile("mov %%cr0, %0": "=r"(cr0));
    cr0 |= 0x80000000; // Enable paging!
    asm volatile("mov %0, %%cr0":: "r"(cr0));
}

void initialise_paging()
{
    page_directory_t* page_directory = (page_directory_t*)kmalloc(sizeof(page_directory_t));
    memsetb((uint8 *)page_directory, 0, sizeof(page_directory_t));

    //for(int i=0; i < 1024; i++) {
    page_table_t* page_table = (page_table_t*)kmalloc(sizeof(page_table_t));
    uint32 tmp = (uint32) page_table;
    memsetb((uint8*) page_table, 0, sizeof(page_table_t));
    page_directory->tables[0] = (page_table_t *) (tmp | 0x7);
    //if (i == 0) {
    uint32 current = 0;
    for (int j=0; j < 1024; j++) {
        page_table->pages[j] = current | 0x7;
        current += 0x1000; 
    }
    //}
    //}
    switch_page_directory(page_directory);
}

