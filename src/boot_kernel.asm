[bits 16]
[org 0x7c00]
kernel_offset equ 0x1000

xor ax, ax
mov ds, ax
mov ss, ax
mov gs, ax
mov es, ax

mov [boot_drive], dl

mov bp, 0x9000
mov sp, bp

mov bx, real_msg
call print


call load_kernel
call vga_mode

jmp enter_pm

;include files
%include "print_string.asm"
%include "load_disk.asm"
%include "gdt.asm"
%include "print_protected.asm"
%include "enter_pm.asm"


[bits 16]

load_kernel:

    mov bx, kernel_msg
    call print

    mov bx, kernel_offset
    mov dh, 15;number of sectors to read
    mov dl, [boot_drive]
    call disk_load

    ret


[bits 16]
vga_mode:
    pusha
    mov ah, 0x00
    mov al, 0x13
    int 0x10
    popa
    ret

[bits 32]

enable_A20:
    pusha
    in al, 0x92
    or al, 2
    out 0x92, al
    popa
    ret

begin:

    mov ebx, protected_msg
    call print_pm
    call enable_A20
    call kernel_offset ;jump to kernel address
    ;call main

jmp $

;variables
boot_drive db 0x00
real_msg db "real ", 0
protected_msg db " protected ", 0
kernel_msg db "kernel ", 0


times 510-($-$$) db 0x0
dw 0xaa55
