#include "idt.h"
#include "types.h"

#define IDT_ENTRIES 256

idt_gate_t idt[IDT_ENTRIES];
idt_register_t idt_reg;


void set_idt_gate(int n, u32 handler) {
    idt[n].low_offset = l16(handler);
    idt[n].sel = KERNEL_CS; //code segment selector in the gdt or ldt
    idt[n].always0 = 0;
    idt[n].flags = 0x8E; //10001110 -> first 4 bits determine gate type (1110 is 32 bit interrupt gate), bit number 4 must be 0 or is unused (i think), the 2 following determine privilege level(00 for kernel level) last bit must be one
    idt[n].high_offset = h16(handler);
}

void set_idt() {
    idt_reg.base = (u32) &idt;
    idt_reg.limit = IDT_ENTRIES * sizeof(idt_gate_t) - 1;

    __asm__ __volatile__("lidt (%0)" : : "r" (&idt_reg));//if written in assembly would be something like: lidt[idtr] where idtr is the location of the idt regiter
}

/*static inline void lidt(void* base, uint16_t size)
{   // This function works in 32 and 64bit mode
    struct {
        uint16_t length;
        void*    base;
    } __attribute__((packed)) IDTR = { size, base };

    asm ( "lidt %0" : : "m"(IDTR) );  // let the compiler choose an addressing mode
}*/
