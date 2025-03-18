#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 1024  // Define the total memory size

// Memory block structure
typedef struct Block {
    size_t size;
    int free;
    struct Block* next;
} Block;

// Global memory pool
static char memory[MEMORY_SIZE];

// Head of the free block list
static Block* freeList = NULL;

// Initialize the memory pool
void initMemory() {
    freeList = (Block*)memory;
    freeList->size = MEMORY_SIZE;
    freeList->free = 1;
    freeList->next = NULL;
}

// Memory allocation function using First Fit
void* allocateMemory(size_t size) {
    Block* current = freeList;
    while (current) {
        if (current->free && current->size >= size) {
            current->free = 0;
            if (current->size > size + sizeof(Block)) {
                Block* nextBlock = (Block*)((char*)current + size + sizeof(Block));
                nextBlock->size = current->size - size - sizeof(Block);
                nextBlock->free = 1;
                nextBlock->next = current->next;
                current->size = size;
                current->next = nextBlock;
            }
            return (void*)((char*)current + sizeof(Block));
        }
        current = current->next;
    }
    return NULL;  // No memory available
}

// Free the allocated memory
void freeMemory(void* ptr) {
    Block* block = (Block*)((char*)ptr - sizeof(Block));
    block->free = 1;
}
