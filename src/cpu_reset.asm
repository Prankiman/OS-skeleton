 ;Wait for a empty Input Buffer

 global wait1

 wait1:
    in   al, 0x64
    test al, 00000010b
    jne  wait1

    ;Send 0xFE to the keyboard controller.
    mov  al, 0xFE
    out  0x64, al
