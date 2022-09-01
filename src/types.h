#ifndef TYPES_H
#define TYPES_H

typedef unsigned int   u32;
typedef          int   s32;
typedef unsigned short u16;
typedef          short s16;
typedef unsigned char  u8;
typedef          char  s8;

#define l16(address) (u16)((address) & 0xFFFF)

#define h16(address) (u16)(((address) >> 16) & 0xFFFF)

#endif
