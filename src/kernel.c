#include "isr.h"
#include "idt.h"
#include "utility.h"
#include "keyboard.h"
#include "mouse.h"
#include "screen.h"
#include "pic.h"

void keypressmsg(){
        /* char *video_address = (char*)0xb8000;
        //print interrupt num____________
        video_address[0] = 'A';//address[1] sets forground and background color of character
        video_address[2] = ':';
        video_address[4] = 'p';
        video_address[6] = 'r';
        video_address[8] = 'e';
        video_address[10] = 's';
        video_address[12] = 's';
        video_address[14] = 'e';
        video_address[16] = 'd';*/
        for(u8 i = 0; i < 20; i++){
            disp_char('A', i, 0, 0x6f);
        }

}
void left_clickmsg(){
        /* char *video_address = (char*)0xb8000;
        //print interrupt num____________
        video_address[0] = 'A';//address[1] sets forground and background color of character
        video_address[2] = ':';
        video_address[4] = 'p';
        video_address[6] = 'r';
        video_address[8] = 'e';
        video_address[10] = 's';
        video_address[12] = 's';
        video_address[14] = 'e';
        video_address[16] = 'd';*/
        for(u8 i = 0; i < 20; i++){
            disp_char('a', i, 4, 0x6f);
        }
}

//extern void wait1();

void main() {


    //give computer some time before initializing the drivers(perhaps bad)
    /*for(int i = 0; i < 299999999; i++){
    //__asm__(".intel_syntax noprefix");
        __asm__("nop");
        //__asm__(".att_syntax prefix");
    }*/
    isr_install();  ///initializes the interrupt service registers
    //outb(60, 0xa7);//disable ps/2 mouse
    //outb(60, 0xad);//disabled ps/2 keyboard

    keyboard_init();
    mouse_install();
    /* Test the interrupts */
    //__asm__ __volatile__("int $2");
    //__asm__ __volatile__("int $3");

    //char *video_address = (char*)0xb8010;
    //*video_address = '_';

    /*u8 *VGA = (u8*)0xA0000;
    u16 offset;

     for (int x = 0; x <= 320; x++){
        for (int y = 0; y <= 200; y++){
            offset = x + 320 * y;

            u8 color = y;

            VGA[offset] = color;//working as intended yaaay
        }

    }*/
    __asm__ __volatile__("int $19");
}


