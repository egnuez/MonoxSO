#include "../stdlib/include/stdlib.h"

static char cpu_name[12] = "no_detected";

char * cpu_detect() {

    uint32 eax, ebx, ecx, edx;

    asm volatile("cpuid":"=a"(eax),"=b"(ebx),
                 "=c"(ecx),"=d"(edx):"a"(0));

    cpu_name[3] = (ebx >> 24) & 0xFF;
    cpu_name[2] = (ebx >> 16) & 0xFF;
    cpu_name[1] = (ebx >> 8) & 0xFF;
    cpu_name[0] = ebx & 0xFF;
    
    cpu_name[7] = (edx >> 24) & 0xFF;
    cpu_name[6] = (edx >> 16) & 0xFF;
    cpu_name[5] = (edx >> 8) & 0xFF;
    cpu_name[4] = edx & 0xFF;

    cpu_name[11] = (ecx >> 24) & 0xFF;
    cpu_name[10] = (ecx >> 16) & 0xFF;
    cpu_name[9] = (ecx >> 8) & 0xFF;
    cpu_name[8] = ecx & 0xFF;

    cpu_name[12] = 0x0;

    return cpu_name;

}
