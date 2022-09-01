[bits 16]

enter_pm:

cli

xor ax, ax
mov ds, ax ;setting data segment to
mov ss, ax
mov es, ax,
mov gs, ax

lgdt [gdt_desc] ;tells cpu where to find the gdt and its's size
 
;by setting bit 0 in the cr0 register to 1 we enter protected mode
mov eax, cr0
or eax, 0x1
mov cr0, eax

;jmp code_seg:start_pm ;make far jump and flush cache of instructions
jmp 0x08:start_pm ;make far jump and flush cache of instructions

[bits 32]

start_pm:
;change all segment registers to the data_seg constant defined in the  gdt_seg.asm file
	mov ax, data_seg
	mov ss, ax
	mov ds, ax
	mov gs, ax
	mov fs, ax
	mov es, ax
;storing correct address in the stack pointers is important

;different addresses correspond to different memory types and has different uses

;500-9ffff, RAM, Free memory (boot sector starts at 7c00)

	mov ebp, 0x90000
	mov esp, ebp

jmp begin ;jumping to label defined in the boot assembly file
