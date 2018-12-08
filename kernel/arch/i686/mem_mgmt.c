#include <stdbool.h> 
#include <stddef.h>
#include <stdint.h>
#include <kernel/system.h>

unsigned char* mallocBase = (unsigned char*)0x01000000;
unsigned char* mallocTop = (unsigned char*)0xBFFFFFFF;
unsigned char* freeBottom = (unsigned char*)0x01000000;

typedef struct kATT_entry {
	char* phy_addr;
	size_t size_bytes;
	struct kATT_entry* next;
} kATT_entry_t;

//Kernel address translation table
kATT_entry_t* kATT;

void* kATT_Init() {
	kATT_entry_t tail = { mallocBase, 0, NULL };
	kATT = &tail;
	return kATT;
}

void** kmalloc(size_t size) {
	kATT_entry_t newBlock;
	newBlock.size_bytes = size;
	kATT_entry_t* cur = kATT;
	
	// Find last block
	while(1) {
		if (cur->next == NULL) 
			break;
		cur = cur->next;
	}
	
	char* newAddr = cur->phy_addr + (sizeof(char) * cur->size_bytes) + 1;
	if ((newAddr + (sizeof(char) * size) + 1) >= mallocTop) {
		// TODO: Return an OOM error
		return NULL;
	}

	newBlock.phy_addr = newAddr;
	newBlock.size_bytes = size;
	newBlock.next = NULL;
	cur->next = &newBlock;
	return &(newBlock.phy_addr);
}

