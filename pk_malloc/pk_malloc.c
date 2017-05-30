#include "pk_malloc.h"

char pool[RESERVE];

void mem_init()
{
	
	size_t* writer = (size_t*)(pool);
	while (writer - (size_t*)(pool) != RESERVE)
	{
		*writer = 0;
		writer++;
	}
	
}

void* mem_malloc(size_t size)
{
	size_t* header = (size_t*)(pool);
	while ((size_t*)(header) - (size_t*)(pool) < RESERVE)
	{
		size_t* start = header;
		if (*header == 0)
		{
			size_t available = 0;
			while (*header == 0)
			{
				available += sizeof(size_t);
				header++;
				if (available >= size + sizeof(size_t))
				{
					break;
				}
			}
			if (available >= size + sizeof(size_t))
			{
				*start = available;
				return (void*)(start + 1);
			}
		}
		else
		{
			header += *header / sizeof(size_t);
		}
	}
	return NULL;
}

void* mem_realloc(void* mem, size_t new_size)
{
	new_size += sizeof(new_size);
	size_t* header = (size_t*)(mem) - 1;
	if (*header >= new_size)
	{
		size_t* writer = header + new_size / sizeof(size_t);
		for (size_t dealloc = new_size; dealloc != *header; dealloc += sizeof(size_t))
		{
			*writer = 0;
			writer++;
		}
		*header = new_size;
		return mem;
	}
	else
	{
		size_t* writer = header + *header / sizeof(size_t);
		size_t available = 0;
		while (*writer == 0)
		{
			available += sizeof(size_t);
			writer++;
			if (available >= new_size - *header)
			{
				break;
			}
		}
		if (available >= new_size - *header)
		{
			*header = new_size;
			return mem;
		}
		else
		{
			void* realloc_t = mem_malloc(new_size - sizeof(size_t));
			if (realloc_t != NULL)
			{
				mem_copy(realloc_t, mem);
				mem_free(mem);
				return realloc_t;
			}
			else
			{
				return NULL;
			}
		}
	}
}

void mem_free(void* mem)
{
	size_t dealloc = 0;
	size_t* header = (size_t*)(mem) - 1;
	size_t occupy = *header;
	while (dealloc != occupy)
	{
		*header = 0;
		dealloc += sizeof(size_t);
		header++;
	}
}

void mem_copy(void* dest, void* source)
{
	size_t copy = 0;
	size_t* header = (size_t*)(source);
	size_t occupy = *(header - 1);
	size_t* writer = (size_t*)(dest);
	while (copy != occupy)
	{
		*writer = *header;
		writer++;
		header++;
		copy += sizeof(size_t);
	}
}

size_t mem_sizeof(void* mem)
{
	return *((size_t*)(mem) - 1) - sizeof(size_t);
}

