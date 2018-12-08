#ifndef CPUID_H
#define CPUID_H
#include <stdint.h>
typedef struct cpuid {
	uint32_t eax;
	uint32_t ebx;
	uint32_t ecx;
	uint32_t edx;
	char* make;
	char* model;
	char* family;
	char* type;
} cpuid_t;

cpuid_t get_cpuid();
#endif
