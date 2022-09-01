#include "io.h"
#include "utility.h"
#include "idt.h"
#include "isr.h"
#include "pic.h"
#include "screen.h"


#define MAX_COLS 80 //temporary

void isr_install() {
    set_idt_gate(0, (u32)isr0);
    set_idt_gate(1, (u32)isr1);
    set_idt_gate(2, (u32)isr2);
    set_idt_gate(3, (u32)isr3);
    set_idt_gate(4, (u32)isr4);
    set_idt_gate(5, (u32)isr5);
    set_idt_gate(6, (u32)isr6);
    set_idt_gate(7, (u32)isr7);
    set_idt_gate(8, (u32)isr8);
    set_idt_gate(9, (u32)isr9);
    set_idt_gate(10, (u32)isr10);
    set_idt_gate(11, (u32)isr11);
    set_idt_gate(12, (u32)isr12);
    set_idt_gate(13, (u32)isr13);
    set_idt_gate(14, (u32)isr14);
    set_idt_gate(15, (u32)isr15);
    set_idt_gate(16, (u32)isr16);
    set_idt_gate(17, (u32)isr17);
    set_idt_gate(18, (u32)isr18);
    set_idt_gate(19, (u32)isr19);
    set_idt_gate(20, (u32)isr20);
    set_idt_gate(21, (u32)isr21);
    set_idt_gate(22, (u32)isr22);
    set_idt_gate(23, (u32)isr23);
    set_idt_gate(24, (u32)isr24);
    set_idt_gate(25, (u32)isr25);
    set_idt_gate(26, (u32)isr26);
    set_idt_gate(27, (u32)isr27);
    set_idt_gate(28, (u32)isr28);
    set_idt_gate(29, (u32)isr29);
    set_idt_gate(30, (u32)isr30);
    set_idt_gate(31, (u32)isr31);

    PIC_remap(0x20, 0x28);//master pic offset is at 0x20 or 32 (where the irqs start) and the slave pick offset is ay 0x28 or 40 (where irq 8 starts)


    // Install the IRQs
    set_idt_gate(32, (u32)irq0);
    set_idt_gate(33, (u32)irq1);
    set_idt_gate(34, (u32)irq2);
    set_idt_gate(35, (u32)irq3);
    set_idt_gate(36, (u32)irq4);
    set_idt_gate(37, (u32)irq5);
    set_idt_gate(38, (u32)irq6);
    set_idt_gate(39, (u32)irq7);
    set_idt_gate(40, (u32)irq8);
    set_idt_gate(41, (u32)irq9);
    set_idt_gate(42, (u32)irq10);
    set_idt_gate(43, (u32)irq11);
    set_idt_gate(44, (u32)irq12);
    set_idt_gate(45, (u32)irq13);
    set_idt_gate(46, (u32)irq14);
    set_idt_gate(47, (u32)irq15);


    set_idt(); // Load with ASM
}

/* To print the message which defines every exception */
static const char *exception_messages[32] = {
    "zero division",
    "debug",
    "non maskable interrupt",
    "breakpoint",
    "into detected overflow",
    "out of bounds",
    "invalid opcode",
    "no coprocessor",

    "double faul",
    "coprocessor segment overrun",
    "bad TSS",
    "segment not present",
    "stack fault",
    "general protection fault",
    "page fault ",
    "unknown interrupt",
    "coprocessor fault",
    "alignment check  ",
    "machine check ",
    "reserved",
    "reserved",
    "reserved",
    "reserved",
    "reserved",
    "reserved",
    "reserved",
    "reserved",
    "reserved",
    "reserved",
    "reserved",
    "reserved",
    "reserved"
};

//temporary until i fix a proper screen driver

int char_off(int x){return 2 * x;}

void isr_handler(registers_t *r) {
    /*if(r->int_no < 32){
    char *video_address = (char*)0xb8000;
    //print interrupt num____________
    video_address[0] = 'i';//address[1] sets forground and background color of character
    video_address[2] = 'n';
    video_address[4] = 't';
    video_address[6] = ':';
    video_address[8] = r->int_no+'0';//note 2 digit values will be represented with corresponding ascii character for example int number 13 will be represented as "="
    }*/

        //const char *errormsg = exception_messages[r->int_no];
        const char *str = exception_messages[r->int_no];//"honey";
        char c = 0;
        int x = 0;
        while ((c = *str++) != 0){
            disp_char(c, x, r->int_no, 0x67);
            x++;
        }
}
