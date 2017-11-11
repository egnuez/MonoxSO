RM	:= rm
CC  := gcc
AS  := as
ASFLAGS := -32

OBJDIR = obj/

CFLAGS	:= -Wall -O0 -fno-stack-protector -fno-builtin -nostdlib -ffreestanding -nostdinc -fno-pic -fno-unwind-tables -fno-exceptions -m32

OBJS_ := gdt_asm.o \
	idt_asm.o \
 	irq_asm.o \
	gdt.o \
	idt.o \
	isr.o \
	irq.o \
	cpuinfo.o

OBJS := $(addprefix obj/, $(OBJS_))

all: $(OBJS)

obj/%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

obj/%.o: %.s
	$(AS) $(ASFLAGS) -o $@ $<

clean:
	$(RM) -f $(OBJS)

