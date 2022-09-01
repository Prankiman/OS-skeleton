#ifndef IO_H
#define IO_H

#include "types.h"

void outb(u16 port, u8 val);

u8 inb(u16 port);

void io_wait(void);


#endif
