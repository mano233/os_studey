#include <stdlib.h>
#define MAX_HEAP 4194304
/* private global variables */
char* mem_heap;
char* mem_brk;
char* mem_max_addr;

void mem_init() {
    mem_heap     = (char*)(malloc(MAX_HEAP));
    mem_brk      = mem_heap;
    mem_max_addr = (char*)(mem_heap + MAX_HEAP);
}

void* mem_sbrk(int incr) {
    char* old_brk = mem_brk;
    if ((incr < 0) || (mem_brk + incr) > mem_max_addr) {
        return (void*)(-1);
    }
    mem_brk += incr;
    return (void*)(old_brk);
}
