#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>  // for sbrk
#include <cassert>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

namespace Mem {
    /**
     * Machine word size. Depending on the architecture,
     * can be 4 or 8 bytes.
     */
    using word_t = intptr_t;

    /**
     * Allocated block of memory. Contains the object header structure,
     * and the actual payload pointer.
     */
    struct Block {
        // 1. Object header
        // Block size.
        size_t size;

        // Whether this block is currently used.
        bool used;

        //  Next block in the list.
        Block* next;

        // 2. User data
        // Payload pointer.
        word_t data[1];
    };

    /**
     * Heap start. Initialized on first allocation.
     */
    static Block* heapStart = nullptr;

    /**
     * Current top. Updated on each allocation.
     */
    static auto top = heapStart;

    /**
     * Aligns the size by the machine word.
     */
    inline size_t align(size_t n) {
        return (n + sizeof(word_t) - 1) & ~(sizeof(word_t) - 1);
    }

    /**
     * Returns total allocation size, reserving in addition the space for
     * the Block structure (object header + first data word).
     *
     * Since the `word_t data[1]` already allocates one word inside the Block
     * structure, we decrease it from the size request: if a user allocates
     * only one word, it's fully in the Block struct.
     */
    inline size_t allocSize(size_t size) {
        return size + sizeof(Block) - sizeof(std::declval<Block>().data);
    }

    /**
     * Requests (maps) memory from OS.
     */
    Block* requestFromOS(size_t size) {
        // Current heap break.
        auto* block = static_cast<Block*>(sbrk(0));
        // OOM.
        if (sbrk(allocSize(size)) == reinterpret_cast<const void*>(-1)) {
            return nullptr;
        }
        return block;
    }

    /**
     * First-fit algorithm.
     *
     * Returns the first free block which fits the size.
     */
    Block* firstFit(size_t size) {
        auto* block = heapStart;
        while (block != nullptr) {
            // O(n) search.
            if (block->used || block->size < size) {
                block = block->next;
                continue;
            }
            // Found the block:
            return block;
        }
        return nullptr;
    }

    /**
     * Tries to find a block of a needed size.
     */
    Block* findBlock(size_t size) { return firstFit(size); }

    /**
     * Allocates a block of memory of (at least) `size` bytes.
     */
    word_t* alloc(size_t size) {
        size = align(size);

        // 1. Search for an available free block:
        if (auto* block = findBlock(size)) {  // (1)
            return block->data;
        }

        // 2. If block not found in the free list, request from OS:
        auto* block = requestFromOS(size);

        block->size = size;
        block->used = true;

        // Init heap.
        if (heapStart == nullptr) {
            heapStart = block;
        }

        // Chain the blocks.
        if (top != nullptr) {
            top->next = block;
        }

        top = block;

        // User payload:
        return block->data;
    }


    /**
     * Returns the object header.
     */
    Block* getHeader(word_t* data) {
        return reinterpret_cast<Block*>(reinterpret_cast<char*>(data) +
                                        sizeof(std::declval<Block>().data) -
                                        sizeof(Block));
    }

    /**
     * Frees a previously allocated block.
     */
    void free(word_t* data) {
        auto* block = getHeader(data);
        block->used = false;
    }

    int fd;

    /**
     * Allocation arena for custom sbrk example.
     */
    static void* arena = nullptr;

    /**
     * Program break;
     */
    static char* _brk = nullptr;

    /**
     * Arena size.
     */
    static size_t arenaSize = 4194304;  // 4 MB

    void* my_sbrk(intptr_t increment) {
        // 0. Pre-allocate a large arena using `mmap`. Init program break
        //    to the beginning of this arena.
        _brk = static_cast<char*>(arena);
        // 1. If `increment` is 0, return current break position.
        if (increment == 0)
            return _brk;
        // 2. If `current + increment` exceeds the top of
        //    the arena, return -1.
        if (_brk - static_cast<char*>(arena) > arenaSize - increment)
            return reinterpret_cast<void*>(-1);
        // 3. Otherwise, increase the program break on
        //    `increment` bytes.
        _brk += increment;
        return _brk;
    }
}  // namespace Mem
using namespace Mem;

int main(int argc, char const* argv[]) {
    // Test case 1: Alignment
    // A request for 3 bytes is aligned to 8.
    auto* p1 = alloc(3);  // (1)
    auto* p1b = getHeader(p1);
    assert(p1b->size == sizeof(word_t));

    // Test case 2: Exact amount of aligned bytes
    auto* p2 = alloc(8);  // (2)
    auto* p2b = getHeader(p2);
    assert(p2b->size == 8);

    // Test case 3: Free the object
    free(p2);
    assert(p2b->used == false);

    // Test case 4: The block is reused
    // A consequent allocation of the same size reuses
    // the previously freed block.
    auto* p3 = alloc(8);
    auto* p3b = getHeader(p3);
    assert(p3b->size == 8);
    assert(p3b == p2b);  // Reused!

    puts("All assertions passed!");

    // my_sbrk(12);
    struct stat sb {};

    if ((fd = open("/Users/mano233/Documents/c_projects/untitled3/map",
                   O_RDWR)) < 0) {
        perror("open");
    }

    if ((fstat(fd, &sb)) == -1) {
        perror("fstat");
    }

    arena =
        mmap(nullptr, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    static_cast<char*>(arena)[0] = '0';
    if (my_sbrk(sb.st_size) == reinterpret_cast<const void*>(-1))
        return -1;
    if ((msync(arena, sb.st_size, MS_SYNC)) == -1) {
        perror("msync");
    }

    if ((munmap(arena, sb.st_size)) == -1) {
        perror("munmap");
    }
    close(fd);
}
