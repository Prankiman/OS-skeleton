gdt_start:

gdt_null:
   dq 0


; offset 0x8 (8 bytes)
gdt_code:
   dw 0xffff    ;setting the limit
   dw 0         ;base address to 0

   ;segment descriptor
   db 0         ;base continuation (i start the bit counting for the segment descriptor bits here)
   db 10011010b ;bits: 8 -> access flag, 9 -> read, 10 -> conforming, 11 -> code or data segment(yes/no), 12 -> code or data segment(code/data), 13-14 -> privilage level, 15 -> present flag
   db 11001111b ; bits 16-19 -> last bits in segment limit, bit 20 -> available to system programmers flag (ignored by cpu), bit 21 -> always 0, bit 22 -> size (1 for 32 bit and 0 for 16-bit), 23 -> multiply segment limit by 4kb
   db 0

; offset 0x10 (16 bytes)
gdt_data:
   dw 0xffff
   dw 0

   db 0

   db 10010010b ;same as for gdt-code but bit 9 enables write access instead of read and the 10th bit enables expand direction (0=down, 1=up)

   db 11001111b ;almost same as for code-segment, bit 22 -> related to segment limit (1 to allow 4gb limit)

   db 0

gdt_end:

gdt_desc:
   ;first we define 16 bits as the gdt size and then 32 bits as the gdt address
   dw gdt_end - gdt_start - 1; should be 1 less than the true size as defined by intel: "Because segment descriptors are always 8 bytes long, the GDT limit should always be one less than an integral multiple of eight (that is, 8N – 1)"
   dd gdt_start


data_seg equ gdt_data-gdt_start
code_seg equ gdt_code-gdt_start

