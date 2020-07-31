#include <cpuid.h>
#include <kernel/cpuid.h>

// Developed from https://gitlab.com/bps-projs/U365/blob/testing/src/arch/i686/cpu-detect.c
//
cpuid_t get_cpuid() {
	cpuid_t data;
	__get_cpuid(0, &data.eax, &data.ebx, &data.ecx, &data.edx);
	if (data.ebx == 0x756e6547) {
		data.make = "GenuineIntel";
		__get_cpuid(1, &data.eax, &data.ebx, &data.ecx, &data.edx);
		int model = (data.eax >> 4) & 0x0F;
		int family = (data.eax >> 8) & 0x0F;
		int type = (data.eax >> 12) & 0x3;
		switch(type) {
			case 0:
				data.type = "Original OEM";
				break;
			case 1:
				data.type = "Overdrive";
				break;
			case 2:
				data.type = "Dual-capable";
				break;
			case 3:
				data.type = "Reserved";
				break;
		}
		switch(family) {
			case 3:
				data.family = "i386";
				break;
			case 4:
				data.family = "i486";
				switch(model) {
					case 0:
					case 1:
						data.model = "DX";
						break;
					case 2:
						data.model = "SX";
						break;
					case 3:
						data.model = "487/DX2";
						break;
					case 4:
						data.model = "SL";
						break;
					case 5:
						data.model = "SX2";
						break;
					case 7:
						data.model = "Write-back enhanced DX2";
						break;
					case 8:
						data.model = "DX4";
						break;
				}
				break;
			case 5:
				data.family = "Pentium";
				switch(model) {
					case 1:
						data.model = "60/66";
						break;
					case 2:
						data.model = "75-200";
						break;
					case 3:
						data.model = "for 486 system";
						break;
					case 4:
						data.model = "MMX";
						break;
				}
				break;
			case 6:
				data.family = "Pentium Pro";
				switch(model) {
					case 1:
						data.model = "Pentium Pro";
						break;
					case 3:
						data.model = "Pentium II Model 3";
						break;
					case 5:
						data.model = "Pentium II Model 5/Xeon/Celeron";
						break;
					case 6:
						data.model = "Celeron";
						break;
					case 7:
						data.model = "Pentium III/Pentium III Xeon - external L2 cache";
						break;
					case 8:
						data.model = "Penitum III/Pentium III Xeon - internal L2 cache";
						break;
					default:
						data.model = "Unknown!";
						break;
				}
				break;
			case 15:
				data.family = "Pentium 4";
				break;
		}
	}
	else if (data.ebx == 0x68747541) {
		data.make = "AMD";
		__get_cpuid(1, &data.eax, &data.ebx, &data.ecx, &data.edx);
		int model = (data.eax >> 4) & 0x0F;
		int family = (data.eax >> 8) & 0x0F;
		int type = (data.eax >> 12) & 0x3;
		switch(family) {
			case 4:
				data.family = "486 family";
				break;
			case 5:
				switch(model) {
					case 7:
						data.model = "K6 Model";
						break;
					case 8:
						data.model = "K6-2 Model 8";
						break;
					case 9:
						data.model = "K6-III Model 9";
						break;
					default:
						data.model = "K5/K6 Model";
						break;
				}
				break;
			case 6:
				switch(model) {
					case 3:
						data.model = "Duron";
						break;
					case 4:
						data.model = "Athlon";
						break;
					case 6:
						data.model = "Athlon MP/Mobile Athlon";
						break;
					case 7:
						data.model = "Mobile Duron Model 7";
						break;
					default:
						data.model = "Duron/Athlon Model";
						break;
				}
			data.type = "AMD";
		}

	}
	return data;
}
