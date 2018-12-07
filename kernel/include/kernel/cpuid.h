#ifndef CPUID_H
#define CPUID_H
#include <stdint.h>
typedef struct cpuid {
	uint32_t eax;
	uint32_t ebx;
	uint32_t ecx;
	uint32_t edx;
} cpuid_t;

cpuid_t get_cpuid();
#endif
