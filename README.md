jnix Kernel
============

jnix (Occasionally ~~mis~~pronounced jinx) is to be a POSIX compliant, Unix-like kernel project targeted at 32 bit x86 procs. All code herein is provided AS IS with no guarantee that it will even compile much less work.

To build:
----------
First set up a i686 cross compiler suite (Use the latest binutils and gcc). You must also have grub and xorriso installed for the iso to be created. To build the bootable ISO, just run
```bash
$ ./iso.sh
```

If you have qemu installed, it will automatically launch `qemu-system-i386` and boot the system. This isn't necessary as you can `dd` the iso to a disk or USB drive and boot on a real machine. jnix has only been tested in qemu so if you get it booting on bare metal, please let me know!

Contribution:
-------------
If you would like to contribute code to this project, please feel free to fork it and submit a pull request! Please have each PR only close one (or set of related) issues so I can more easily track what has and needs to be done.
