.code32
.intel_syntax noprefix
.text

.global _gdtp
.global _load_gdt
_load_gdt:
  lgdt _gdtp
  mov ax, 0x10      # 0x10 is the offset in the GDT to our data segment
  mov ds, ax        # Load all data segment selectors
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov ss, ax
  jmp 0x08:.flush   # 0x08 is the offset to our code segment: Far jump!
.flush:
  ret

.section .data
  _gdtp:       .byte 1,2,3,4,5,6
