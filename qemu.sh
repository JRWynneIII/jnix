#!/bin/bash
set -e
SYSROOT=sysroot/
qemu-system-i386 -drive if=floppy,index=0,media=disk,file=harddrive -vga cirrus -cdrom jnix.iso -m 4G

