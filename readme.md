# pk_malloc

release date - 2017/05/30

Log:
- added mem_sizeof
- added mem_realloc
- added mem_copy
- added mem_free
- added mem_malloc

---

## Brief

Simple memory management library for embedded systems. Supports basic memory allocation from stack.

## Method Summary

Method Declaration | Arguments | Method Description
--- | --- | ---
void mem_init | void | initialize the memory pool
void\* mem_malloc | size_t size | allocates a memory chunk according to size
void\* mem_realloc | void\* mem, size_t new_size | reallocates a memory chunk
void mem_free | void\* mem | free a memory chunk
void mem_copy | void\* dest, void\* source | perform deep copy
size_t mem_sizeof | void* mem | retrieve allocated memory chunk size

## Method Details

### mem_init

This method initializes the memory pool. This is an initialization of the library and must be called on top of library usage.

### mem_malloc

This method allocates the specified amount of memory and returns a pointer to the first writable byte. Returns NULL if allocation fails.

## mem_realloc

This method resizes the allocated memory chunk, if necessary, may allocate a new memory chunk with the specified amount of memory, and returns a pointer to the first writable byte. The old pointer to the memory chunk may be different to the returned address. Returns NULL if the reallocation fails, in which no reallocation has taken place, the old pointer is safe to access.

## mem_free

This method releases the allocated memory back to the memory pool. The old pointer is now dangling.

## mem_sizeof

This method retrieves the allocated memory chunk size.
