#!/bin/bash
set -e
SYSROOT=sysroot/
vncviewer &
/usr/libexec/qemu-kvm -drive if=floppy,index=0,media=disk,file=harddrive -vga cirrus -cdrom jnix.iso -m 1G -cpu pentium3

