.code32
.intel_syntax noprefix
.text

jmp _start

# Multi Boot Header (Grub support)
# TODO: Soporte de header para formato no ELF

.align 4
.long      0x1BADB002
.long      0x00000003
.long      - (0x1BADB002+0x00000003)
.global _start

_start:

#  lea    esp, sys_stack     # Set up a stack.
  push eax                  # multiboot structure
  push ebx                  # multiboot magic number
  call   _start_kernel      # Jump to C function.
_stop:
  cli
  hlt
  jmp _stop
  
# Bin Kernel (Solo para flat Bin)
#.fill 512, 1, 0 
#sys_stack:

# ELF Kernel (Grub expande el bss porque entiende ELF :) )
#.bss
#.space 512
#sys_stack:

#.section .data
#  sec_id:      .ascii "DATA SECTION"
