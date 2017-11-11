AS  := as
RM	:= rm
CC  := gcc
OC  := objcopy

OBJDIR = obj/
BINDIR = bin/

CFLAGS	:= -Wall -O0 -fno-stack-protector -fno-builtin -nostdlib -ffreestanding -nostdinc -fno-pic -fno-unwind-tables -fno-exceptions -m32
LDFLAGS := -m elf_i386 -T link.ld
ASFLAGS := -32
OCFLAGS := -O binary -j ".text" -j ".data" -j ".rodata" $(ELF) $(BIN)

BIN := $(BINDIR)/kernel.bin
ELF := $(BINDIR)/kernel.elf

OBJS_ := entry.o \
 	paging.o \
 	main.o \
	ordered_array.o \
	kheap.o \
	multiboot.o 

OBJS := $(addprefix obj/, $(OBJS_))

all: $(OBJS)

obj/%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

obj/%.o: %.s
	$(AS) $(ASFLAGS) -o $@ $<

clean:
	$(RM) -f $(OBJS)

