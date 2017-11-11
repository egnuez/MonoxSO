#include "../stdlib/include/stdlib.h"
#include "include/idt.h"

/* 
 * The interrupt EOI byte must be sent to the PIC after an IRQ is handled.
 * The PIC will not send any more IRQs until it receives the EOI.
 *
 * The are two PIC controller: master and slave. When an IRQ sent by the 
 * slave is acknowledged, then an EOI must be sent to both controllers.
 */
#define PIC_EOI              0x20

/*
 * Port at which the master PIC chip listens:
 */
#define PIC_MASTER_CMD_PORT  0x20
#define PIC_MASTER_DATA_PORT 0x21

/*
 * Port at which the slave PIC chip listens:
 */
#define PIC_SLAVE_CMD_PORT   0xA0
#define PIC_SLAVE_DATA_PORT  0xA1


extern void _irq0();
extern void _irq1();
extern void _irq2();
extern void _irq3();
extern void _irq4();
extern void _irq5();
extern void _irq6();
extern void _irq7();
extern void _irq8();
extern void _irq9();
extern void _irq10();
extern void _irq11();
extern void _irq12();
extern void _irq13();
extern void _irq14();
extern void _irq15();

/* This array is actually an array of function pointers. We use
*  this to handle custom IRQ handlers for a given IRQ */
void *irq_routines[16] =
{
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0
};

/* This installs a custom IRQ handler for the given IRQ */
void irq_install_handler(int irq, void (*handler)(INT_REGS *r))
{
  irq_routines[irq] = handler;
}

/* This clears the handler for a given IRQ */
void irq_uninstall_handler(int irq)
{
  irq_routines[irq] = 0;
}

/* Normally, IRQs 0 to 7 are mapped to entries 8 to 15. This
 * is a problem in protected mode, because IDT entry 8 is a
 * Double Fault! Without remapping, every time IRQ0 fires,
 * you get a Double Fault Exception, which is NOT actually
 * what's happening. We send commands to the Programmable
 * Interrupt Controller (PICs - also called the 8259's) in
 * order to remap IRQ0 through 15 to IDT entries 32 through 47.
 */
/*
inline void io_wait()
{
    // port 0x80 is used for 'checkpoints' during POST.
    // The Linux kernel seems to think it is free for use :-/
    asm volatile( "outb %%al, $0x80"
                  : : "a"(0) );
}
*/

void remap_PIC()
{
  outportb(PIC_MASTER_CMD_PORT,  0x11);  /* Tell master PIC to wait for 3 initialization bytes. */
//  io_wait();
  outportb(PIC_SLAVE_CMD_PORT,   0x11);  /* Tell slave PIC to wait for 3 initialization bytes. */
//  io_wait();
  outportb(PIC_MASTER_DATA_PORT, 0x20);  /* Remap: set master PIC offset to 0x20 (32). */
//  io_wait();
  outportb(PIC_SLAVE_DATA_PORT,  0x28);  /* Remap: set slave PIC offset to 0x28 (40).  */
//  io_wait();
  outportb(PIC_MASTER_DATA_PORT, 0x04);  /* Tell master PIC that there is a slave PIC at IRQ2 (bit mask 0000 0100) */
//  io_wait();
  outportb(PIC_SLAVE_DATA_PORT,  0x02);  /* Tell slave PIC that its cascade identity is 2 (0000 0010) */
//  io_wait();
  outportb(PIC_MASTER_DATA_PORT, 0x01);  /* Set master PIC operation mode to 8086/8088 (MCS-80/85) mode. */
//  io_wait();
  outportb(PIC_SLAVE_DATA_PORT,  0x01);  /* Set slave PIC operation mode to 8086/8088 (MCS-80/85) mode. */
///  io_wait();
  outportb(PIC_MASTER_DATA_PORT, 0x00);  /* Clear master PIC mask. */
  outportb(PIC_SLAVE_DATA_PORT,  0x00);  /* Clear slave PIC mask. */
}

/* Remap the interrupt controllers, and then we install
*  the appropriate ISRs to the correct entries in the IDT. This
*  is just like installing the exception handlers */
void install_irq()
{
  remap_PIC();

	set_idt_interrupt_gate(32, (unsigned)_irq0);
	set_idt_interrupt_gate(33, (unsigned)_irq1);
	set_idt_interrupt_gate(34, (unsigned)_irq2);
	set_idt_interrupt_gate(35, (unsigned)_irq3);
	set_idt_interrupt_gate(36, (unsigned)_irq4);
	set_idt_interrupt_gate(37, (unsigned)_irq5);
	set_idt_interrupt_gate(38, (unsigned)_irq6);
	set_idt_interrupt_gate(39, (unsigned)_irq7);
	set_idt_interrupt_gate(40, (unsigned)_irq8);
	set_idt_interrupt_gate(41, (unsigned)_irq9);
	set_idt_interrupt_gate(42, (unsigned)_irq10);
	set_idt_interrupt_gate(43, (unsigned)_irq11);
	set_idt_interrupt_gate(44, (unsigned)_irq12);
	set_idt_interrupt_gate(45, (unsigned)_irq13);
	set_idt_interrupt_gate(46, (unsigned)_irq14);
	set_idt_interrupt_gate(47, (unsigned)_irq15);
}

/*
 * This function gets called when an IRQ comes in.
 */
void _irq_handler(INT_REGS *r)
{
  /* This is a blank function pointer */
  void (*handler)(INT_REGS *r);

  /* 
   * Find out if we have a custom handler to run for this
   * IRQ, and then finally, run it. If there is no handler,
   * do nothing.
   */
  handler = irq_routines[r->int_no - 32];
  if (handler)
  {
    handler(r);
  }

  /* If the IDT entry that was invoked was greater than 40
   * (meaning IRQ8 - 15), then we need to send an EOI to
   * the slave controller */
  if (r->int_no >= 40)
  {
    outportb(PIC_SLAVE_CMD_PORT, PIC_EOI);
  }

  /* In either case, we need to send an EOI to the master
   * interrupt controller too: */
  outportb(PIC_MASTER_CMD_PORT, PIC_EOI);
}


