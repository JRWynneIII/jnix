#include <stdbool.h> 
#include <stddef.h>
#include <stdint.h>
#include <kernel/system.h>

unsigned char* mallocBase __attribute__((aligned(4096))) = (unsigned char*)0x01000000;
unsigned char* mallocTop __attribute__((aligned(4096))) = (unsigned char*)0xBFFFFFFF;

extern void loadPageDir(unsigned int*);
extern void enablePaging();

void add_page_table(uint32_t address);

typedef struct kATT_entry {
	unsigned char* phy_addr;
	size_t size_bytes;
	struct kATT_entry* next;
	struct kATT_entry* prev;
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
		newBlock.prev = &kATT;
	}
	else {
		newBlock.phy_addr = (kATT.last->phy_addr + kATT.last->size_bytes + 1 + sizeof(kATT_entry_t));
		newBlock.size_bytes = size;
		newBlock.next = NULL;
		newBlock.prev = kATT.last;
	}

	// Copy kATT entry to end of allocated block
	kATT_entry_t* newBlockPtr = memcpy((newBlock.phy_addr + size + sizeof(kATT_entry_t)), &newBlock, sizeof(kATT_entry_t)); 
	// Append to list
	kATT.last->next = newBlockPtr;
	kATT.last = newBlockPtr;
	return &(newBlockPtr->phy_addr);
}

void* kfree(unsigned char* ptr) {
	kATT_entry_t* cur = &kATT;
	while(cur->next != NULL) {
		if (cur->phy_addr == ptr) {
			//Unlink node and relink the surrounding nodes
			cur->prev->next = cur->next;
			cur->next->prev = cur->prev;
			break;
		}
		cur = cur->next;
	}
	
}

uint32_t pdir[1024] __attribute__((aligned(4096)));

void init_paging() {
	uint32_t ptbl[1024] __attribute__((aligned(4096)));
	for (int i = 0; i < 1024; i++)
	{
		pdir[i] = 0x00000002;
		ptbl[i] = (i * 0x1000) | 3; // supervisor level; rw
	}
	// First 400MiB is kernel memory
	for (int i = 0; i < 100; i++) {
		pdir[i] = ((unsigned int)ptbl) | 3;
	}
	loadPageDir(pdir);
	enablePaging();
}
