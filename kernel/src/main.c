#include "include/multiboot.h"
#include "include/config.h"
#include "stdlib/include/stdlib.h"
#include "x86/include/gdt.h"
#include "x86/include/idt.h"
#include "x86/include/isr.h"
#include "x86/include/irq.h"
#include "x86/include/cpuinfo.h"
#include "drivers/include/pit.h"
#include "drivers/include/kb.h"
#include "drivers/include/display.h"
#include "paging.h"
#include "kheap.h"

void _start_kernel(multiboot_info_t * multiboot_addr, unsigned long magic)
{
	__asm__ __volatile__("cli");

    clear_screen();
	printf("%s - %s -- %s %s \n",	KERNEL_NAME,
									KERNEL_VERSION,
									KERNEL_DATE,
									KERNEL_TIME);

	printf("%s \n", KERNEL_LICENCE);
    print("Informacion enviada por GRUB:\n");
    multiboot_info(multiboot_addr, magic);
    printf("Inicializando Arquitectura: %s\n", cpu_detect());
    print("     GDT\n");
    install_gdt();
    print("     IDT\n");
	install_idt();
    print("     Excepciones\n");
	install_isrs();
    print("     Interrupciones\n");
	install_irq();
    initialise_paging();
    //initialise_memory();

    __asm__ __volatile__("sti");

    uint32 *ptr = (uint32*)0xA0000000;
    uint32 do_page_fault = *ptr;
    timer_install();
    keyboard_install();

mylabel:
    goto mylabel;
}
