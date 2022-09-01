# OS-skeleton
bare bones kernel and bootloader that can be built upon to create more impressive and feature rich 32-bit operating systems

## running
run `make iso` to create the image file

not that it works differently on hardware depending on the hardware vendors. Mouse input might work if your computer has an internal pointing device or if your computer supports 2 ps/2 inputs and possible with a usb mouse since they typically will emulate ps/2 mice. I got the keyboard input to work on both of the laptops I tested on but only one of them worked with the mouse driver

## RECOURSES

## OSDEV.org:

### homepage:
https://wiki.osdev.org/Main_Page

### keyboard:
https://wiki.osdev.org/PS/2_Keyboard

### inline assembly:
https://wiki.osdev.org/Inline_assembly

### babysteps series:
https://wiki.osdev.org/Babystep1

### VGA:
https://wiki.osdev.org/VGA_Resources

### SANiK's mouse driver:
https://forum.osdev.org/viewtopic.php?t=10247

## Tutorialspoint assembly programming series:
https://www.tutorialspoint.com/assembly_programming/

## To Do Huangs Operating System from 0 to 1 github page:
https://github.com/tuhdo/os01

## Intel's developer manuals:
https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html

## os dever:

### creating the gdt table in assembly:
http://web.archive.org/web/20190424213806/http://www.osdever.net/tutorials/view/the-world-of-protected-mode

### creating the idt:
http://web.archive.org/web/20210515200857/http://www.osdever.net/bkerndev/Docs/idt.htm

http://web.archive.org/web/20211226232232/http://www.osdever.net/bkerndev/Docs/isrs.htm

### FREE VGA:
http://www.osdever.net/FreeVGA/home.htm

## Nick Blundell's How To Write an Operating System :
https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf

## Cfenollosa's os-tutorial project:
https://github.com/cfenollosa/os-tutorial

##  James Molloy's kernel development tutorials

### idt and gdt
https://web.archive.org/web/20160327011227/http://www.jamesmolloy.co.uk/tutorial_html/4.-The%20GDT%20and%20IDT.html


## Netwide Assembler documentation:

https://www.nasm.us/docs.php

## GNU Assembler manual:

https://sourceware.org/binutils/docs/as/

## LWN net, Linux Device Drivers:
https://lwn.net/Kernel/LDD3/
