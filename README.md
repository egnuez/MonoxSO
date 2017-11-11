# Pre-Monox

## 2-Stages - BootLoader (MBR)

- Read Fat
- Serach and Load 2ndstage.out into Fat-16 FS
- Search and Load Kernel.bin
- Load GDT
- Load IDT
- Switch to Protected Mode
- Jump To Kernel loaded on 0x20000

## Kernel:
- Multiboot Info
- Cpu Vendor Detect etect 
- Rewrites GDT
- Rewrites IDT
- Loads IRQ Exceptions (0-31)
- Handles Timer Ticks and Keyboard IRQ
- Shows a message and waits for IRQ's

## Emulation

- Bochs
- Qemu
- VirtualBox


   page         0x006000 
   page 1       0x006000
|  directory    0x005000
   bitmap
   gdt
   idt
   2 o 3 vars
|  Kernl bss    0x003000
|  Kernl data   0x002000
|  Kernl text   0x001000
|  HARDWARE?
|  Stack        0x0007ff
|
|
|               0x000000
