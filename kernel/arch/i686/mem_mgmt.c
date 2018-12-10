#include <stdbool.h> 
#include <stddef.h>
#include <stdint.h>
#include <kernel/system.h>

unsigned char* mallocBase = (unsigned char*)0x01000000;
unsigned char* mallocTop = (unsigned char*)0xBFFFFFFF;

typedef struct kATT_entry {
	unsigned char* phy_addr;
	size_t size_bytes;
} kATT_entry_t;

//Kernel address translation table
kATT_entry_t kATT[64000];

void* kATT_Init() {
	kATT_entry_t head, tail;
        head.phy_addr = mallocBase;
	head.size_bytes = 1;
	tail.phy_addr = NULL;
	tail.size_bytes = 0;
	kATT[0] = head;
	kATT[1] = tail;
	return kATT;
}

void** kmalloc(size_t size) {
	kATT_entry_t newBlock;
	kATT_entry_t cur = kATT[0];

	printk("kATT.size_bytes = ", COLOR_RED);
	printk(itoa(cur.size_bytes), COLOR_RED);
	printk("\n",COLOR_WHITE);
	
	// Find last block
	int i = 0;
	while(kATT[i+1].phy_addr != NULL) {
		printk(itoa(cur.phy_addr), COLOR_WHITE);
		printk("\n", COLOR_WHITE);
		cur = kATT[i];
		i++;
	}

	unsigned char* newAddr = (unsigned char*)(cur.phy_addr + (sizeof(unsigned char) * cur.size_bytes) + 1);
	if ((newAddr + (sizeof(unsigned char) * size) + 1) >= mallocTop) {
		// TODO: Return an OOM error and/or do compaction
		return NULL;
	}

	printk(itoa(newAddr), COLOR_WHITE);
	printk("\n", COLOR_WHITE);


	newBlock.phy_addr = newAddr;
	newBlock.size_bytes = size;
	kATT_entry_t tmp = kATT[i+1];
	kATT[i+1] = newBlock;
	kATT[i+2] = tmp;
	return &(kATT[i+1].phy_addr);
}

