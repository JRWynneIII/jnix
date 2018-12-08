#include <stdbool.h> 
#include <stddef.h>
#include <stdint.h>
#include <kernel/system.h>

unsigned char* mallocBase = (unsigned char*)0x01000000;
unsigned char* mallocTop = (unsigned char*)0xBFFFFFFF;

typedef struct kATT_entry {
	unsigned char* phy_addr;
	size_t size_bytes;
	struct kATT_entry* next;
} kATT_entry_t;

//Kernel address translation table
kATT_entry_t* kATT = NULL;

void* kATT_Init() {
	kATT_entry_t tail;
        tail.phy_addr = mallocBase;
	tail.size_bytes = 1;
        tail.next = NULL;
	kATT = &tail;
	return kATT;
}

void** kmalloc(size_t size) {
	kATT_entry_t newBlock;
	newBlock.size_bytes = size;
	kATT_entry_t* cur = kATT;
	
	// Find last block
	while(cur->next != NULL) {
		printk("next\n", COLOR_WHITE);
		cur = cur->next;
	}
	
	unsigned char* newAddr = cur->phy_addr + (sizeof(unsigned char) * cur->size_bytes) + 1;
	if ((newAddr + (sizeof(unsigned char) * size) + 1) >= mallocTop) {
		// TODO: Return an OOM error
		return NULL;
	}

	newBlock.phy_addr = newAddr;
	newBlock.size_bytes = size;
	newBlock.next = NULL;
	cur->next = &newBlock;
	return &(newBlock.phy_addr);
}

