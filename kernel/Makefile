HOST?=$(shell ../default-host.sh)
HOSTARCH:=i686#x86_64#$(shell ../target-triplet-to-arch.sh $(HOST))
 
CC=i686-elf-gcc#x86_64-elf-gcc
AS=i686-elf-as
CFLAGS?=-O2 -g
CPPFLAGS?=
LDFLAGS?=
LIBS?=
 
DESTDIR?=
PREFIX?=/usr/local
EXEC_PREFIX?=$(PREFIX)
BOOTDIR?=$(EXEC_PREFIX)/boot
INCLUDEDIR?=$(PREFIX)/include
 
CFLAGS:=$(CFLAGS) -ffreestanding -fno-builtin -Wall -Wextra
CPPFLAGS:=$(CPPFLAGS) -D__is_jforth_kernel -Iinclude -I../sysroot/usr/include
LDFLAGS:=$(LDFLAGS) -L../sysroot/usr/lib
LIBS:=$(LIBS) -nostdlib -lgcc -lk
 
ARCHDIR:=arch/$(HOSTARCH)
 
include $(ARCHDIR)/make.config
 
CFLAGS:=$(CFLAGS) $(KERNEL_ARCH_CFLAGS)
CPFLAGS:=$(CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)
LDFLAGS:=$(LDFLAGS) $(KERNEL_ARCH_LDFLAGS)
LIBS:=$(LIBS) $(KERNEL_ARCH_LIBS)
 
OBJS:=\
$(KERNEL_ARCH_OBJS) \
kernel/kernel.o \
 
CRTI_OBJ:=$(ARCHDIR)/crti.o
CRTBEGIN_OBJ:=$(shell $(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ:=$(shell $(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=crtend.o)
CRTN_OBJ:=$(ARCHDIR)/crtn.o
 
ALL_OUR_OBJS:=\
$(CRTI_OBJ) \
$(OBJS) \
$(CRTN_OBJ) \
 
OBJ_LINK_LIST:=\
$(CRTI_OBJ) \
$(CRTBEGIN_OBJ) \
$(OBJS) \
$(CRTEND_OBJ) \
$(CRTN_OBJ) \
 

all: jforth.kernel
 
.PHONY: all clean install install-headers install-kernel
 
jforth.kernel: $(OBJ_LINK_LIST) $(ARCHDIR)/linker.ld
	LD_LIBRARY_PATH=../sysroot/usr/lib $(CC) -T $(ARCHDIR)/linker.ld -o $@ $(CFLAGS) $(OBJ_LINK_LIST) $(LDFLAGS) $(LIBS)
 
%.o: %.c
	$(CC) -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)
 
%.o: %.S
	$(AS) -c $< -o $@ 
 
clean:
	rm -f jforth.kernel $(OBJS) $(ALL_OUR_OBJS) *.o */*.o */*/*.o
 
install: install-headers install-kernel
 
install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -RTv include $(DESTDIR)$(INCLUDEDIR)
 
install-kernel: jforth.kernel
	mkdir -p $(DESTDIR)$(BOOTDIR)
	cp jforth.kernel $(DESTDIR)$(BOOTDIR)
