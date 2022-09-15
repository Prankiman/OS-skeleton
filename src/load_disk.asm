;---------------------------------------------


;dl <- drive number. Our caller sets it as a parameter and gets it from BIOS
; (0 = floppy, 1 = floppy2, 0x80 = hdd, 0x81 = hdd2)



; load DH sectors to ES : BX from drive DL
disk_load:
    push cx
    push dx
    ;push dx ; Store DX on stack so later we can recall
    ; how many sectors were request to be read,
    ; even if it is altered in the meantime

    mov cx, 5   ;5 attempts

attempt:
    mov ah, 0x02 ; BIOS read sector function
    mov al, dh ; Read DH sectors
    mov ch, 0x00 ; Select cylinder 0
    mov dh, 0x00 ; Select head 0
    mov cl, 0x02 ; Start reading from second sector ( i.e.
    ; after the boot sector )
    int 0x13 ; BIOS interrupt
    jc retry ; Jump if error ( i.e. carry flag set )

    pop dx ; Restore DX from the stack

    cmp dh, al ; if AL ( sectors read ) != DH ( sectors expected )
    jne disk_error ; display error message

    pop cx

done:
    ret

retry:
    mov ah, 0x00 ;Reset diskdrive
    int 0x13
    cmp cx, 0x00
    je  disk_error
    dec cx
    jmp attempt

disk_error:
    mov bx, DISK_ERROR_MSG
    call print
    jmp $
; Variables
DISK_ERROR_MSG: db "Disk read error!", 0
;--------------------------------------------
