HOST?=$(shell ../default-host.sh)
HOSTARCH:=i686#x86_64#$(shell ../target-triplet-to-arch.sh $(HOST))
 
CC=i686-elf-gcc#x86_64-elf-gcc
CFLAGS?=-O2 -g -std=gnu99
CPPFLAGS?=
LDFLAGS?=
LIBS?=
 
DESTDIR?=
PREFIX?=/usr/local
EXEC_PREFIX?=$(PREFIX)
INCLUDEDIR?=$(PREFIX)/include
LIBDIR?=$(EXEC_PREFIX)/lib
 
CFLAGS:=$(CFLAGS) -ffreestanding -fno-builtin -Wall -Wextra
CPPFLAGS:=$(CPPFLAGS) -D__is_jnix_libc -Iinclude -I../sysroot/usr/include
LIBK_CFLAGS:=-Wall -Wextra -ffreestanding -fno-builtin
LIBK_CPPFLAGS:=$(CPPFLAGS) -D__is_jnix_kernel -I../sysroot/usr/include
 
ARCHDIR:=arch/$(HOSTARCH)
 
include $(ARCHDIR)/make.config
 
CFLAGS:=$(CFLAGS) $(ARCH_CFLAGS)
CPFLAGS:=$(CPPFLAGS) $(ARCH_CPPFLAGS)
LIBK_CFLAGS:=$(LIBK_CFLAGS) $(KERNEL_ARCH_CFLAGS)
LIBK_CPFLAGS:=$(LIBK_CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)
 
FREEOBJS:=\
$(ARCH_FREEOBJS) \
stdio/gets.o \
stdio/printf.o \
stdio/putchar.o \
stdio/puts.o \
stdlib/abort.o \
stdlib/malloc.o \
string/memcmp.o \
string/memcpy.o \
string/memmove.o \
string/memset.o \
string/strlen.o \
 
HOSTEDOBJS:=\
$(ARCH_HOSTEDOBJS) \
 
OBJS:=\
$(FREEOBJS) \
$(HOSTEDOBJS) \
 
LIBK_OBJS:=$(FREEOBJS:.o=.libk.o)
 
BINARIES=libc.a libg.a libk.a
 
all: $(BINARIES)
 
.PHONY: all clean install install-headers install-libs
 
libc.a: $(OBJS)
	$(AR) rcs $@ $(OBJS)
 
libg.a:
	$(AR) rcs $@
 
libk.a: $(LIBK_OBJS)
	$(AR) rcs $@ $(LIBK_OBJS)
 
%.o: %.c
	$(CC) -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)
 
%.o: %.S
	$(CC) -c $< -o $@ $(CFLAGS) $(CPPFLAGS)
 
%.libk.o: %.c
	$(CC) -c $< -o $@ -std=gnu11 $(LIBK_CFLAGS) $(LIBK_CPPFLAGS)
 
%.libk.o: %.S
	$(CC) -c $< -o $@ $(LIBK_CFLAGS) $(LIBK_CPPFLAGS)
 
clean:
	rm -f $(BINARIES) $(OBJS) $(LIBK_OBJS) *.o */*.o */*/*.o
 
install: install-headers install-libs
 
install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -Rv include/* $(DESTDIR)$(INCLUDEDIR)
 
install-libs: $(BINARIES)
	mkdir -p $(DESTDIR)$(LIBDIR)
	cp $(BINARIES) $(DESTDIR)$(LIBDIR)
