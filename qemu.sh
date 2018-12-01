#!/bin/bash
set -e
SYSROOT=sysroot/
qemu-system-i386 -hda harddrive -vga cirrus -kernel $SYSROOT/boot/jforth.kernel
