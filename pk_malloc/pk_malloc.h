#ifndef _PK_MALLOC
#define _PK_MALLOC

#include <stdlib.h>
#include <string.h>

#define RESERVE 1024

void mem_init(void);

void* mem_malloc(size_t size);
void* mem_realloc(void* mem, size_t new_size);
void mem_free(void* mem);

void mem_copy(void* dest, void* source, size_t size);

size_t mem_sizeof(void* mem);

#endif

