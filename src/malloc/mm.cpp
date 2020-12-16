#include <cstddef>
#include <list>
/* Basic constants abd macros */
#define WSIZE             4
#define DSIZE             8
#define CHUNKSIZE         (1 << 7)
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

extern void* mem_sbrk(int);

char* heap_listp;

char* last_findp;

static void* extend_heap(size_t);

static void* coalesce(void*);

extern void mem_init();

/**
 * 适配算法的枚举类型:
 * 首次适应(first_fit,FF)算法
 * 循环首次适应(next_fit,NF)算法
 * 最佳适应(best_fit,BF)算法
 * 最坏适应(worst fit,WF)算法
 */
enum FIT_FUN { ff_fit = 0, nf_fit = 1, bf_fit = 2, wf_fit = 3 };

/* 枚举对象,默认适配方式为FF */
static FIT_FUN fit_fun = ff_fit;

/**
 *
 * 初始化内存堆
 * 赋予基本内存结构,由一个字的全0块,一个双字的序言块以及一个字的结尾块组成
 * 初次扩充时将在序言块和结尾块中插入一个空闲块
 *
 *      | Prologue  | epilogue
 * +----+-----------+-----+
 * | 0  | 8/1 | 8/1 | 0/1 |
 * +----+-----+-----+-----+
 *            ^
 *            |
 *       heap_listp
 *
 * 其中headp_lisp指向序言块
 *
 * 一个内存块的具体结构有header,data,foot组成
 * 其中header、foot为便于操作保存了*相同的信息*，具体结构如下：
 *
 * 32                             3          0
 * +------------------------------+----------+
 * |         Block Size           | alloc bit|
 * +------------------------------+----------+
 *
 * block size总是字节对齐的（8的倍数）后三位总是为0,因此使用后3位保存其他信息
 * 这里用于保存alloc bit（000表示空闲，001表示已分配）
 *
 * @return
 */
int mm_init() {
    // 初始化内存模型
    mem_init();
    if ((heap_listp = static_cast<char*>(mem_sbrk(4 * WSIZE))) == (void*)-1) {
        return -1;
    }
    PUT(heap_listp, 0);
    PUT(heap_listp + (1 * WSIZE), PACK(DSIZE, 1));
    PUT(heap_listp + (2 * WSIZE), PACK(DSIZE, 1));
    PUT(heap_listp + (3 * WSIZE), PACK(0, 1));
    heap_listp += (2 * WSIZE);
    if (extend_heap(CHUNKSIZE / WSIZE) == NULL) {
        return -1;
    }
    return 0;
}

/**
 * 扩展堆内存
 * @param words
 * @return
 */
static void* extend_heap(size_t words) {
    char* bp;
    // 对大小进行内存对齐
    size_t size = (words % 2) ? (words + 1) * WSIZE : words * WSIZE;
    if ((long)(bp = static_cast<char*>(mem_sbrk(size))) == -1) {
        return nullptr;
    }
    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK(size, 0));
    PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1));
    return coalesce(bp);
}

/**
 * 对内存块进行边界合并
 * @param bp 要操作的内存块
 * @return
 */
static void* coalesce(void* bp) {
    size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
    size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
    size_t size       = GET_SIZE(HDRP(bp));
    if (prev_alloc && next_alloc) {
        return bp;
    } else if (prev_alloc && !next_alloc) {
        size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
        PUT(HDRP(bp), PACK(size, 0));
        PUT(FTRP(bp), PACK(size, 0));
    } else if (!prev_alloc && next_alloc) {
        size += GET_SIZE(HDRP(PREV_BLKP(bp)));
        PUT(FTRP(bp), PACK(size, 0));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        bp = PREV_BLKP(bp);
    } else {
        size += GET_SIZE(HDRP(PREV_BLKP(bp))) + GET_SIZE(FTRP(NEXT_BLKP(bp)));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
        bp = PREV_BLKP(bp);
    }
    return bp;
}
// TODO: 完成循环首次适应算法
static void* nf_fit_fun(size_t asize){
	char* bp = last_findp;
    // 遍历所有内存块
    for (bp = last_findp; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp)) {
        // 找到一个空闲块且大小<=asize
		if (!GET_ALLOC(HDRP(bp)) && (asize <= GET_SIZE(HDRP(bp)))) {
			last_findp = PREV_BLKP(bp);
        }
    }

	return nullptr;
}
static void* wf_fit_fun(size_t asize) {
    std::list<void*> bp_list;
    void* bp;
    // 遍历所有内存块
    for (bp = heap_listp; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp)) {
        if (!GET_ALLOC(HDRP(bp)) && (asize <= GET_SIZE(HDRP(bp)))) {
            bp_list.push_back(bp);
        }
    }
    if (bp_list.empty()) {
        return nullptr;
    }
	// 将内存块按照大小从大到小排序
    bp_list.sort([](const void* a, const void* b) {
        return GET_SIZE(HDRP(a)) - GET_SIZE(HDRP(b));
    });
    bp = bp_list.front();
    if (GET_SIZE(HDRP(bp)) >= asize) {
        return bp;
    }
    return nullptr;
}
static void* ff_fit_fun(size_t asize) {
    for (void* bp = heap_listp; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp)) {
        if (!GET_ALLOC(HDRP(bp)) && (asize <= GET_SIZE(HDRP(bp)))) {
            return bp;
        }
    }
    return nullptr;
}

static void* find_fit(size_t asize) {
    switch (fit_fun) {
        case ff_fit:
            return ff_fit_fun(asize);
        case nf_fit:
			return nullptr;
        case bf_fit:
            return nullptr;
        case wf_fit:
            return wf_fit_fun(asize);
        default:
            return nullptr;
    }
}

/**
 * 拆分空闲块，将大的空闲划分一块用于分配
 * @param bp
 * @param asize
 */
static void place(void* bp, size_t asize) {
    size_t csize = GET_SIZE(HDRP(bp));
    if ((csize - asize) >= (2 * WSIZE)) {
        PUT(HDRP(bp), PACK(asize, 1));
        PUT(FTRP(bp), PACK(asize, 1));
        bp = NEXT_BLKP(bp);
        PUT(HDRP(bp), PACK(csize - asize, 0));
        PUT(FTRP(bp), PACK(csize - asize, 0));
    } else {
        PUT(HDRP(bp), PACK(csize, 1));
        PUT(FTRP(bp), PACK(csize, 1));
    }
}

inline void set_fit_fun(int type) {
    switch (type) {
        case 0:
            fit_fun = ff_fit;
            return;
        case 1:
            fit_fun = nf_fit;
            return;
        case 2:
            fit_fun = bf_fit;
            return;
        default:
            fit_fun = ff_fit;
    }
}

void* mem_malloc(size_t size) {
    size_t asize;
    size_t extendsize;
    char* bp = nullptr;
    if (size == 0) {
        return nullptr;
    }
    asize = size <= DSIZE ? 2 * DSIZE
                          : DSIZE * ((size + (DSIZE) + (DSIZE - 1)) / DSIZE);
    if ((bp = static_cast<char*>(find_fit(asize))) != nullptr) {
        place(bp, asize);
        return bp;
    }
    extendsize = MAX(asize, CHUNKSIZE);
    if ((bp = static_cast<char*>(extend_heap(extendsize / WSIZE))) == nullptr)
        return nullptr;
    place(bp, asize);
    return bp;
}

void mm_free(void* bp) {
    size_t size = GET_SIZE(HDRP(bp));
    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK(size, 0));
    coalesce(bp);
}
