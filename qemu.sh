#!/bin/bash
set -e
SYSROOT=sysroot/
qemu-system-i386 -hda harddrive -net nic,model=rtl8139 -vga cirrus -kernel $SYSROOT/boot/jforth.kernel
