#ifndef MOUSE_H
#define MOUSE_H

#include "utility.h"
#include "pic.h"

extern u8 mouse_byte[];    //signed char
extern u8 mouse_x;         //signed char
extern u8 mouse_y;         //signed char

//Mouse functions
void mouse_handler(registers_t *r); //struct regs *a_r (not used but just there);


void mouse_wait(u8 a_type); //unsigned char

void mouse_write(u8 a_write); //unsigned char


u8 mouse_read();

void mouse_install();

#endif

