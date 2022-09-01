;prints message using function from other file

[BITS 16]       ;   16 bit code
[ORG 0x7c00]    ;   BIOS loads bootloader at physical address 0x7C00 and thus we tell the assembler to assemble instructions from that section

mov bp, 0x8000 ; Set the base of the stack a little above where BIOS loads our boot sector - so it won ’t overwrite us.
mov sp, bp

mov dx, 0x1fb6 ; store the value to print in dx

call print_hex ; call the function

mov dx, 0x1fb5
call print_hex
; prints the value of DX as hex.

jmp $

print_hex:
    pusha

    ;note that the hex value for ascii numbers starts at '0' = hex 30 and ends at '9' = hex 39 and the hex values for ascii lowercase letters starts at 'a' = hex 61 and ends at 'z' = hex 7a which we will use for number to string convertion

    mov cx, 0x4 ;16 bit hex values only contains 4 characters and thus we will use cx to convert each hex digit to corresponding ascii value for set digit

hex_to_ascii:
    sub cx, 0x1 ;decrement cx by 1

    mov ax, dx  ;copy dx into ax
    shr dx, 0x4 ; shift dx by 4 bits i.e remove the right most digit for example 0x1fb6 >> 0x4 becomes 0x01fb
    and ax, 0xf ;0xf in binary is 1111 and thus using the and operation will only give us the last 4 bits or the last hex digit: 0x1fb6 and 0xf -> 0x6

    mov bx, HEX_OUT
    add bx, 0x2       ;bx is at address where the first '0' in '0x0000' is located and adding 2 "skips" the '0x' part
    add bx, cx      ;add cx so we are at the correct hex digit (from the most right digit till the left most digit)

    cmp ax, 0xa ;check if digit is a decimal number or a letter

    jl to_num ;if letter (less than 10) jump to to_num address



to_letter:
    add byte [bx], 0x27  ;the 'byte' is a type specifier to tell the assembler we are adding a 8-bit number;ascii 'a' hex value is 0x61 so we add 0x27 so that we will end up adding 0x61 after we add the extra 0xa later since [bx] will only have the value 0x30 which is the ascii value for '0'

to_num:
    add word [bx], ax

    cmp cx, 0x0   ;if cx is 0 we have converted all digits to ascii values and stored them
    je print_converted
    jmp hex_to_ascii    ;if cx > 0 we continue the process of converting the hex digits to its corresponding ascii values

print_converted:
    mov bx, HEX_OUT
    call print ; print the string pointed to by bx
    mov cx, 0x4
    add bx, 0x2
reset_hex_out:;need to reset the bytes at the hex_out address
    mov byte [bx], '0'
    sub cx, 0x1
    add bx, 0x1
    cmp cx, 0x0
    jne reset_hex_out

    popa
    ret

%include "print_string.asm"

; global variables
HEX_OUT: db '0x0000', 0

; Padding and magic number.
times 510 -( $ - $$ ) db 0x00
dw 0xaa55

