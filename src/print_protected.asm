[bits 32]
; Define some constants
video_memory equ 0xb8000
white_on_black equ 0x0f
; prints a null - terminated string pointed to by EDX
print_pm:
    pusha
    mov edx, video_memory ; Set edx to the start of vid mem.
print_pm_loop:
    mov al, [ebx] ;using ebx as parameter
    ; Store the char at EBX in AL
    mov ah, white_on_black ; Store the attributes in AH
    cmp al, 0
    je  print_pm_done

    mov [edx], ax
    add ebx, 1
    add edx, 2
;Store char and attributes at current
;character cell.
;Increment EBX to the next char in string.

; Move to next character cell in vid mem.
    jmp print_pm_loop
 ; loop around to print the next char.
print_pm_done:
    popa
    ret
