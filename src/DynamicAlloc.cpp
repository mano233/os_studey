#include "DynamicAlloc.h"
#define WSIZE             4
#define DSIZE             8
#define MAX(x, y)         ((x) > (y) ? (x) : (y))
#define PACK(size, alloc) ((size) | (alloc))
#define GET(p)            (*(unsigned int*)(p))
#define PUT(p, val)       (*(unsigned int*)(p) = (val))
#define GET_SIZE(p)       (GET(p) & ~0x7)
#define GET_ALLOC(p)      (GET(p) & 0x1)
#define HDRP(bp)          ((char*)(bp)-WSIZE)
#define FTRP(bp)          ((char*)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)
#define NEXT_BLKP(bp)     ((char*)(bp) + GET_SIZE(((char*)(bp)-WSIZE)))
#define PREV_BLKP(bp)     ((char*)(bp)-GET_SIZE(((char*)(bp)-DSIZE)))

static QMap<void*, QString> malloc_map_vs;
static QMap<QString, void*> malloc_map_sv;
extern void set_fit_fun(int type);
QVariantList DynamicAlloc::get_list() {
    QVariantList list_all;
    for (void* bp = NEXT_BLKP(heap_listp); GET_SIZE(HDRP(bp)) > 0;
         bp       = NEXT_BLKP(bp)) {
        int size = GET_SIZE(HDRP(bp));
        QVariantMap map;
        if (GET_ALLOC(HDRP(bp))) {
            map = {{"size", size},
                   {"alloc", GET_ALLOC(HDRP(bp))},
                   {"id", malloc_map_vs[bp]}};
        } else {
            map = {{"size", size}, {"alloc", GET_ALLOC(HDRP(bp))}};
        }
        list_all.append(map);
    }
    return list_all;
}

void DynamicAlloc::setFitFun(int type){
	set_fit_fun(type);
}

void DynamicAlloc::malloc(QString id, size_t size) {
    if (malloc_map_sv.contains(id)){
        return;
    }
    void* memptr = mem_malloc(size);
    malloc_map_vs.insert(memptr, id);
    malloc_map_sv.insert(id, memptr);
}

void DynamicAlloc::free(QString id) {
    if(!malloc_map_sv.contains(id)){
		return;
    }
	void* memptr = malloc_map_sv[id];
    mm_free(memptr);
    malloc_map_sv.remove(id);
    malloc_map_vs.remove(memptr);
}
