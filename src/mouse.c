//heavily based on SANiK's mouse driver

#include "isr.h"
#include "utility.h"
#include "io.h"
#include "pic.h"
#include "keyboard.h"
#include "kernel.h"
#include "screen.h"

u8 mouse_cycle=0;
u8 mouse_byte[3];
u8 mouse_x=0;
u8 mouse_y=0;

u8 ysign=0;
u8 xsign=0;
u8 xover=0;
u8 yover=0;

u8 overflowx = 64;//0b01000000;
u8 overflowy = 128;//0b10000000;
u8 signx = 16;//0b00010000;
u8 signy = 32;//0b00100000;

//Mouse functions
void mouse_handler(registers_t *r)
{
  switch(mouse_cycle)
  {
    case 0:
      ysign = mouse_byte[0] & signy;
      xsign = mouse_byte[0] & signx;
      yover = mouse_byte[0] & overflowy;
      xover = mouse_byte[0] & overflowx;
      mouse_byte[mouse_cycle]=inb(0x60);
      mouse_cycle++;
      break;
    case 1:
      mouse_byte[mouse_cycle]=inb(0x60);
      mouse_cycle++;
      mouse_x += mouse_byte[1];
      break;
    case 2:
      mouse_byte[mouse_cycle]=inb(0x60);
      mouse_y -= mouse_byte[2];
      mouse_cycle=0;
      break;
  }


  u8 *VGA = (u8*)0xA0000;
  u16 offset;

    for (int x = 0; x <= 320; x++){
      for (int y = 0; y <= 200; y++){
          offset = x + 320 * y;

          u8 color = 0;

          VGA[offset] = color;//working as intended yaaay
      }
  }
  disp_char_absolute('+', mouse_x, mouse_y, 0x6f);
  if(mouse_byte[0] & 1){//if left_click
    /*char *video_address = (char*)0xb8050;
    video_address[0] = 'L';//address[1] sets forground and background color of character
    video_address[2] = 'e';
    video_address[4] = 'f';
    video_address[6] = 't';
    video_address[8] = '-';
    video_address[10] = 'c';
    video_address[12] = 'l';
    video_address[14] = 'i';
    video_address[16] = 'c';*/
    left_clickmsg();
  }
}

void mouse_wait(u8 a_type)
{
  u32 _time_out=100000;//sizeof(u32);
  if(a_type==0)
  {
    while(_time_out--) //Data
    {
      if((inb(0x64) & 1)==1)
      {
        return;
      }
    }
    return;
  }
  else
  {
    while(_time_out--) //Signal
    {
      if((inb(0x64) & 2)==0)
      {
        return;
      }
    }
    return;
  }
}

void mouse_write(u8 a_write) //unsigned char
{
  //Wait to be able to send a command
  mouse_wait(1);
  //Tell the mouse we are sending a command
  outb(0x64, 0xD4);
  //Wait for the final part
  mouse_wait(1);
  //Finally write
  outb(0x60, a_write);
}

u8 mouse_read()
{
  //Get's response from mouse
  mouse_wait(0);
  return inb(0x60);
}

void mouse_install()
{
  u8 _status;  //unsigned char

  //Enable the auxiliary mouse device
  mouse_wait(1);
  outb(0x64, 0xA8);

  //Enable the interrupts
  mouse_wait(1);
  outb(0x64, 0x20);
  mouse_wait(0);
  _status=(inb(0x60) | 2);
  mouse_wait(1);
  outb(0x64, 0x60);
  mouse_wait(1);
  outb(0x60, _status);

  //__some shit i found__
  /*mouse_write(0xE8);
  mouse_read();

  mouse_write(0x00);
  mouse_read();

  mouse_write(0xF3);
  mouse_read();

  mouse_write(200);
  mouse_read();*/
  //


  //Tell the mouse to use default settings
  mouse_write(0xF6);
  mouse_read();  //Acknowledge

  //Enable the mouse
  mouse_write(0xF4);
  mouse_read();  //Acknowledge

  //Setup the mouse handler
  irq_install_handler(IRQ12, mouse_handler);//might only work for ps/2 mice although most usb mice emulate ps/2 mice (it did work on my laptops touchpad so there ya go)
}
