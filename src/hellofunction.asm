;prints message using function from other file

[BITS 16]       ;   16 bit code
[ORG 0x7c00]    ;   BIOS loads bootloader at physical address 0x7C00 and thus we tell the assembler to assemble instructions from that section

mov bp, 0x8000 ; Set the base of the stack a little above where BIOS loads our boot sector - so it won ’t overwrite us.
mov sp, bp

mov bx, HELLO_MSG ; Use BX as a parameter to our function , so we can specify the address of a string.
;add bx, 0x7c00 if you uncomment this line and comment the org line it will still print the hello_msg

call print  ;call pushes the return address(next address) to the stack

mov bx, GOODBYE_MSG

call print

jmp $

%include "print_string.asm"

; Data
HELLO_MSG:
    db 'Hello, World!', 0x00 ; <-- The zero on the end tells our routine when to stop printing characters

GOODBYE_MSG:
    db 'Goodbajs!', 0x00


; Padding and magic number.
times 510 -( $ - $$ ) db 0x00
dw 0xaa55
