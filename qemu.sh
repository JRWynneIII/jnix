#!/bin/bash
set -e
SYSROOT=sysroot/
qemu-system-i386 -net nic,model=rtl8139 -vga cirrus -kernel $SYSROOT/boot/jforth.kernel
