#ifndef SCREEN_H
#define SCREEN_H

#define VGA_CTRL_REGISTER 0x3d4
#define VGA_DATA_REGISTER 0x3d5
#define VGA_OFFSET_LOW 0x0f
#define VGA_OFFSET_HIGH 0x0e

#define vid_mem 0xa0000

#include "types.h"

void disp_char(char c, u8 xx, u8 yy, u8 cc);
void disp_char_absolute(char c, u8 xx, u8 yy, u8 cc);

#endif
