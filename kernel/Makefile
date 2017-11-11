AS  := as
RM	:= rm
CC  := gcc
OC  := objcopy

SRCDIR = src/
OBJDIR = obj/
BINDIR = bin/

CFLAGS	:= -Wall -O0 -fno-stack-protector -fno-builtin -nostdlib -ffreestanding -nostdinc -fno-pic -fno-unwind-tables -fno-exceptions -m32
LDFLAGS := -m elf_i386 -T $(SRCDIR)/link.ld
ASFLAGS := -32
OCFLAGS := -O binary -j ".text" -j ".data" -j ".rodata" $(ELF) $(BIN)

BIN := $(BINDIR)/kernel.bin
ELF := $(BINDIR)/kernel.elf

OBJS_MAIN := src/obj/entry.o \
			 src/obj/main.o \
			 src/obj/paging.o \
			 src/obj/multiboot.o

OBJS_STDLIB := 	src/stdlib/obj/mem.o \
				src/stdlib/obj/string.o \
				src/stdlib/obj/port.o

OBJS_X86 := src/x86/obj/idt.o \
			src/x86/obj/isr.o \
			src/x86/obj/irq.o \
			src/x86/obj/gdt.o \
			src/x86/obj/irq_asm.o \
			src/x86/obj/idt_asm.o \
			src/x86/obj/gdt_asm.o \
			src/x86/obj/cpuinfo.o

OBJS_DRIVERS := src/drivers/obj/display.o \
				src/drivers/obj/pit.o \
				src/drivers/obj/kb.o

OBJS := $(OBJS_MAIN) $(OBJS_STDLIB) $(OBJS_X86) $(OBJS_DRIVERS)

$(BIN): $(ELF)
	$(OC) $(OCFLAGS) $(ELF) $(BIN)

$(ELF):
	make -C src/
	make -C src/stdlib/
	make -C src/x86/
	make -C src/drivers/
	$(LD) $(LDFLAGS) -o $(ELF) $(OBJS) 

clean:
	$(RM) -f $(BIN)
	$(RM) -f $(ELF)
	make -C src/ clean
	make -C src/stdlib/ clean
	make -C src/x86/ clean
	make -C src/drivers/ clean

.PHONY: $(BIN) $(ELF) 
