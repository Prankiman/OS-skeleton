;hellow world bootloader program, based on: https://www.viralpatel.net/taj/tutorial/hello_world_bootloader.php

[BITS 16]       ;   16 bit code
[ORG 0x7c00]    ;   BIOS loads bootloader at physical address 0x7C00 and thus we tell the assembler to assemble instructions from that section

mov ah, 0x0e ;enter tele-type mode by putting '0x0e' into the ah register

mov al, 0x0a ;ASCII code for end of line
int 0x10

mov al, 'H'  ;store 'H' into the al register (same as 'mov al 0x48' since 48 is the hex value corresponding to the 'H' ASCII character)
int 0x10    ;video related calls are made through the 'int 0x10' BIOS interrupt and thus what was stored in al will be outputed to the screen

;_____writing the rest of the message_______
mov al, 'E'
int 0x10
mov al, 'L'
int 0x10
int 0x10
mov al, 'O'
int 0x10
mov al, 0x0a ;ASCII code for end of line
int 0x10

mov al, 0x08 ;code for backspace

times 10 int 0x10

mov al, 'W'
int 0x10
mov al, 'O'
int 0x10
mov al, 'R'
int 0x10
mov al, 'L'
int 0x10
mov al, 'D'
int 0x10
;________________________________________________


jmp $   ;jump to the current address (infinite loop)

times 510-($-$$) db 0 ;the bootsector is 512 bytes long and the '$$' denotes the starting location of our program and thus ($-$$) is the length of the instructions read so far and we fill the rest of the bootsector apart from the last two bytes with zeroes

dw 0xaa55   ;fill the last 2 bytes with the boot signature telling the bios that the code is bootable
