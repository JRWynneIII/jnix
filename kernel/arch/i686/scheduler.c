#include <stdbool.h> 
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <kernel/system.h> 

typedef enum state 
{
	RUNNING = 1,
	HALTED  = 0,	
} state_t;

typedef struct process
{
	void* binData; //Buffer that contains the binary's data
	size_t stackSize; //Size of the stack for the proc. Probably should be a preset
	size_t heapSize; //Size of the heap for the proc. This is where libc/malloc is different than allocate_mem() in libk
} process_t;

typedef struct rr_scheduler
{
	process_t proc;
	state_t state;
	scheduler_t* next; //Pointer to the next scheduler block
} scheduler_t;

scheduler_t* ksched;

size_t init_scheduler()
{
	// Add the control block to the scheduler as the head of the list
	scheduler_t pcb = { NULL, state_t RUNNING, NULL };
	ksched = &pcb;
}

size_t add_process(process_t proc)
{
	// Add proc to the scheduler buffer
}

