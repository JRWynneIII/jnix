#include <cpuid.h>
#include <kernel/cpuid.h>

cpuid_t get_cpuid() {
	cpuid_t data;
	__get_cpuid(1, &data.eax, &data.ebx, &data.ecx, &data.edx);
	return data;
}
