;[SECTION .text] ;text --> executable text, bss --> declare variables, data --> constants
[bits 16]
[org 0x7c00]

mov bp, 0x9c00
mov sp, bp

mov bx, hello_real_string
call print

jmp  enter_pm ;enter protected mode

;jmp $


%include "print_string.asm"
%include "gdt.asm"
%include "print_protected.asm"
%include "enter_pm.asm"

[bits 32] ; tell the assembler to generate code for 32-bit mode

begin:
	
	mov ebx, hello_protected_string
	call print_pm

	jmp $

;Global vars
hello_real_string db "hello real-mode", 0
hello_protected_string db "hello protected-mode", 0

;bootsector padding and magic bytes
times 510-($-$$) db 0
dw 0xaa55
