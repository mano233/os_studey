#include <cstdlib>

/* private global variables */
static char *mem_heap;
static char *mem_brk;
static char *mem_max_addr;

#define MAX_HEAP 4096

void meme_init(){
	mem_heap = (char*)malloc(MAX_HEAP);
	mem_brk  = (char*)mem_heap;
	mem_max_addr = (char*)(mem_heap);
}
