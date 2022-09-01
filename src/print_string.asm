print:
    pusha ; Push all register values to the stack
    mov ah , 0x0e ; ah=0x0e -> tele-type mode
display_chars:
    mov al, [bx] ; '[]' -> store contents of the address rather than the address itself
    add bx, 1
    int 0x10 ; print the character in al
    cmp al, 0x00
    jne display_chars
    popa ; Restore original register values
    ret  ;pops the return address off the stack before jumping to it
