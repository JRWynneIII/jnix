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

typedef struct kATT_superblock {
	unsigned char* base;
	kATT_entry_t* next;
	kATT_entry_t* last;
} kATT_superblock_t;

//Kernel address translation table
static kATT_superblock_t kATT;

void kATT_Init() {
        kATT.base = mallocBase;
	kATT.next = &kATT.last;
	kATT.last = NULL;
}

void** kmalloc(size_t size) {
	kATT_entry_t newBlock;

	//The table is empty
	if (kATT.last == NULL) {
		newBlock.phy_addr = kATT.base;
		newBlock.size_bytes = size;
		newBlock.next = NULL;
	}
	else {
		newBlock.phy_addr = (kATT.last->phy_addr + kATT.last->size_bytes + 1 + sizeof(kATT_entry_t));
		newBlock.size_bytes = size;
		newBlock.next = NULL;
	}

	// Copy kATT entry to end of allocated block
	kATT_entry_t* newBlockPtr = memcpy((newBlock.phy_addr + size + sizeof(kATT_entry_t)), &newBlock, sizeof(kATT_entry_t));
	// Append to list
	kATT.last->next = newBlockPtr;
	kATT.last = newBlockPtr;
	return &(newBlockPtr->phy_addr);
}

