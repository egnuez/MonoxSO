#include "../stdlib/include/stdlib.h"

/* Defines an GDT table entry */

typedef struct 
{
    uint16 limit_low;           // The lower 16 bits of the limit.
    uint16 base_low;            // The lower 16 bits of the base.
    uint8  base_middle;         // The next 8 bits of the base.
    uint8  access;              // Access flags, determine what ring this segment can be used in.
    uint8  granularity;
    uint8  base_high;           // The last 8 bits of the base.
} __attribute__((packed)) GDT_DESCRIPTOR;

GDT_DESCRIPTOR gdt[4];

typedef struct
{
    uint16  limit;           /* GDT table length in bytes. */
    uint32  base;            /* Physical address of first descriptor entry. */
} __attribute__((packed)) GDT_PTR;

extern GDT_PTR _gdtp;

extern void _load_gdt();

void set_descriptor(uint8 num, uint32 base, uint32 limit, uint8 access, uint8 gran)
{

    gdt[num].base_low    = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high   = (base >> 24) & 0xFF;

    gdt[num].limit_low   = (limit & 0xFFFF);
    gdt[num].granularity = (limit >> 16) & 0x0F;

    gdt[num].granularity |= gran & 0xF0;
    gdt[num].access      = access;
}

void install_gdt(){

    /* Setup GDT pointer: */
 
    _gdtp.limit = (sizeof (GDT_DESCRIPTOR) * 3) - 1;
    _gdtp.base = (uint32) &gdt;
    
    /*
    gdt_set_gate(0, 0, 0, 0, 0);                // Null segment
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment
    */

    set_descriptor(0, 0, 0, 0, 0);                     // NUll Segment
    set_descriptor(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);      // Code Segment
    set_descriptor(2, 0, 0xFFFFFFFF, 0x92, 0xCF);      // Data Segment
 
   _load_gdt();
}
