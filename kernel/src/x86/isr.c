#include "../stdlib/include/stdlib.h"
#include "../drivers/include/display.h"
#include "include/idt.h"

/* These are function prototypes for all of the exception
 * handlers: The first 32 entries in the IDT are reserved
 * by Intel, and are designed to service exceptions. 
 * 
 * The actual handler code is in idt_asm.s
 */
extern void _isr0();
extern void _isr1();
extern void _isr2();
extern void _isr3();
extern void _isr4();
extern void _isr5();
extern void _isr6();
extern void _isr7();
extern void _isr8();
extern void _isr9();
extern void _isr10();
extern void _isr11();
extern void _isr12();
extern void _isr13();
extern void _isr14();
extern void _isr15();
extern void _isr16();
extern void _isr17();
extern void _isr18();
extern void _isr19();
extern void _isr20();
extern void _isr21();
extern void _isr22();
extern void _isr23();
extern void _isr24();
extern void _isr25();
extern void _isr26();
extern void _isr27();
extern void _isr28();
extern void _isr29();
extern void _isr30();
extern void _isr31();

/*
 * Install interrupt service routines for interrupts 0 through 31.
 */
void install_isrs()
{
  set_idt_interrupt_gate(0,  (unsigned)_isr0);
  set_idt_interrupt_gate(1,  (unsigned)_isr1);
  set_idt_interrupt_gate(2,  (unsigned)_isr2);
  set_idt_interrupt_gate(3,  (unsigned)_isr3);
  set_idt_interrupt_gate(4,  (unsigned)_isr4);
  set_idt_interrupt_gate(5,  (unsigned)_isr5);
  set_idt_interrupt_gate(6,  (unsigned)_isr6);
  set_idt_interrupt_gate(7,  (unsigned)_isr7);
  set_idt_interrupt_gate(8,  (unsigned)_isr8);
  set_idt_interrupt_gate(9,  (unsigned)_isr9);
  set_idt_interrupt_gate(10, (unsigned)_isr10);
  set_idt_interrupt_gate(11, (unsigned)_isr11);
  set_idt_interrupt_gate(12, (unsigned)_isr12);
  set_idt_interrupt_gate(13, (unsigned)_isr13);
  set_idt_interrupt_gate(14, (unsigned)_isr14);
  set_idt_interrupt_gate(15, (unsigned)_isr15);
  set_idt_interrupt_gate(16, (unsigned)_isr16);
  set_idt_interrupt_gate(17, (unsigned)_isr17);
  set_idt_interrupt_gate(18, (unsigned)_isr18);
  set_idt_interrupt_gate(19, (unsigned)_isr19);
  set_idt_interrupt_gate(20, (unsigned)_isr20);
  set_idt_interrupt_gate(21, (unsigned)_isr21);
  set_idt_interrupt_gate(22, (unsigned)_isr22);
  set_idt_interrupt_gate(23, (unsigned)_isr23);
  set_idt_interrupt_gate(24, (unsigned)_isr24);
  set_idt_interrupt_gate(25, (unsigned)_isr25);
  set_idt_interrupt_gate(26, (unsigned)_isr26);
  set_idt_interrupt_gate(27, (unsigned)_isr27);
  set_idt_interrupt_gate(28, (unsigned)_isr28);
  set_idt_interrupt_gate(29, (unsigned)_isr29);
  set_idt_interrupt_gate(30, (unsigned)_isr30);
  set_idt_interrupt_gate(31, (unsigned)_isr31);
}

/* This is a simple string array. It contains the message that
*  corresponds to each and every exception. We get the correct
*  message by accessing like:
*  exception_message[interrupt_number] */
char *exception_messages[] =
{
  "Division By Zero",
  "Debug",
  "Non Maskable Interrupt",
  "Breakpoint",
  "Into Detected Overflow",
  "Out of Bounds",
  "Invalid Opcode",
  "No Coprocessor",

  "Double Fault",
  "Coprocessor Segment Overrun",
  "Bad TSS",
  "Segment Not Present",
  "Stack Fault",
  "General Protection Fault",
  "Page Fault",
  "Unknown Interrupt",

  "Coprocessor Fault",
  "Alignment Check",
  "Machine Check",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",

  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved"
};

/* All of our Exception handling Interrupt Service Routines will
*  point to this function. This will tell us what exception has
*  happened! Right now, we simply halt the system by hitting an
*  endless loop. All ISRs disable interrupts while they are being
*  serviced as a 'locking' mechanism to prevent an IRQ from
*  happening and messing up kernel data structures */
void _fault_handler(INT_REGS *r)
{
  if (r->int_no < 32)
  {
    print(exception_messages[r->int_no]);
    print(" Exception. System Halted!\n");
    for (;;);
  }
}
