//
// Created by mano233 on 2020/12/10.
//

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

QVariantList DynamicAlloc::get_list() {
    list.clear();
    traversal([](void* bp) {
        int size        = GET_SIZE(HDRP(bp));
        QVariantMap map = {{"size", size}, {"alloc", GET_ALLOC(HDRP(bp))}};
        list.append(map);
    });
    return list;
}
void DynamicAlloc::malloc(const QString& id, size_t size) {
    if (!malloc_map.contains(id)){
        malloc_map.insert(id,mem_malloc(size));
    }
}
