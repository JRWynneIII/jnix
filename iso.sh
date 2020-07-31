#!/bin/sh

set -e
. ./build.sh

mkdir -p isodir/boot/grub

cp sysroot/boot/jnix.kernel isodir/boot/jnix.kernel

cat > isodir/boot/grub/grub.cfg << EOF
menuentry "jnix" {
	multiboot /boot/jnix.kernel
}
EOF

grub2-mkrescue -o jnix.iso isodir

./qemu.sh
