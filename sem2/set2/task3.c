#include <stdio.h>
#include <stdint.h>


int main(int argc, char *argv[])
{
    char *compiler = "other";
    int bitness = 0;
    char *asserts = "enabled";

#if UINTPTR_MAX == 0xffffffff
    bitness = 32;
#elif UINTPTR_MAX == 0xffffffffffffffff
    bitness = 64;
#endif


#ifdef __GNUC__
    if (__GNUC__) {
        compiler = "GCC";
    }
#endif

# ifdef __clang__
    if (__clang__) {
        compiler = "clang";
    }
#endif
    
# ifdef __TINYC__
    if (__TINYC__) {
        compiler = "TCC";
    }
#endif

#ifdef NDEBUG
    asserts = "disabled";
#endif 

    printf("Compiler: %s\nBitness: %d\nAsserts: %s", compiler, bitness, asserts);

    return 0;
}
