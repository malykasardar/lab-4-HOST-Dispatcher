#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 1024

typedef struct Block {
    size_t size;
    int free;
    struct Block* next;
} Block;

static char memory[MEMORY_SIZE];

static Block* freeList = NULL;

void initMemory() {
    freeList = (Block*)memory;
    freeList->size = MEMORY_SIZE;
    freeList->free = 1;
    freeList->next = NULL;
}

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
    return NULL;
}

void freeMemory(void* ptr) {
    Block* block = (Block*)((char*)ptr - sizeof(Block));
    block->free = 1;
}





/*********************************************************************
 * Group Number: 1
 *   - Abdullah Hanoosh, Student ID: 100749026
 *   - Malyka Sardar, Student ID: 100752640
 *   - Marwan Alam, Student ID: 100842087
 *   - Vidurshan Sribalasuhabiramam, Student ID: 100558257
 *********************************************************************/
