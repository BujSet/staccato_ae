#include <stdio.h>
#include <stdint.h>

// Function to check RDSEED support using CPUID
int check_rdseed_support() {
    uint32_t eax = 7, ebx = 0, ecx = 0, edx = 0;
    
    // Call CPUID with EAX=7 to get structured extended features
    __asm__("cpuid"
            : "+a" (eax), "=b" (ebx), "=c" (ecx), "=d" (edx)
            : "a" (7), "c" (0));
            
    // RDSEED is supported if bit 18 of EBX is set
    // According to Intel SDM: Structured Extended Features, EBX[18]
    return (ebx >> 18) & 1;
}

int main() {
    if (check_rdseed_support()) {
        printf("RDSEED is supported on this CPU.\n");
    } else {
        printf("RDSEED is NOT supported on this CPU.\n");
    }
    return 0;
}
