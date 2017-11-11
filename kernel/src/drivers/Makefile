RM	:= rm
CC  := gcc

OBJDIR = obj/

CFLAGS	:= -Wall -O0 -fno-stack-protector -fno-builtin -nostdlib -ffreestanding -nostdinc -fno-pic -fno-unwind-tables -fno-exceptions -m32

OBJS_ := display.o \
	kb.o \
	pit.o

OBJS := $(addprefix obj/, $(OBJS_))

all: $(OBJS)

obj/%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	$(RM) -f $(OBJS)

