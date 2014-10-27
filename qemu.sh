#!/bin/bash
set -e
SYSROOT=sysroot/
qemu-system-i386 -vga cirrus -kernel $SYSROOT/boot/jforth.kernel
