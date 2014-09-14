Hobby-kernel
============

This is a simple, monolithic kernel being written as I follow various (sparse) tutorials. 

I do NOT own all of the code in this tutorial, though some of it is my own (Various parts of vga.c, system.c, as well as all of kernel.c and keyboard.c/keyboard.h are written by me.)

I've set up a cross-compiler (gnu) to compile this kernel for i586 processor. When you run make, it will compile and link all the appropriate files, create the bootable image (which includes GRUB for the bootloader) and then launch qemu with the appropriate flags. 
