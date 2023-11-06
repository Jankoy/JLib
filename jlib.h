#ifndef JLIB_H_
#define JLIB_H_

#include <stddef.h>

#define ARENA_INITIAL_SIZE 64

typedef struct {
	void* base_ptr;
	void* alloc_pos;
} arena_t;

void* arena_alloc(arena_t* arena, size_t size);
void arena_free(arena_t* arena);

typedef struct {
	char* str;
	size_t size;
} string_t;

string_t string_create(arena_t* arena, size_t size);
//string_t str_cpy();

// This is an stb-style library so you must define JLIB_IMPLEMENTATION before including it in your main file
// you can also define JLIB_ASSERT, JLIB_MALLOC, JLIB_CALLOC, JLIB_REALLOC and JLIB_FREE before the include to use your own
// versions of those functions

#ifdef JLIB_IMPLEMENTATION

#ifndef JLIB_ASSERT
#include <assert.h>
#define JLIB_ASSERT assert
#endif //JLIB_ASSERT

#ifndef JLIB_MALLOC
#include <stdlib.h>
#define JLIB_MALLOC malloc
#endif //JLIB_MALLOC

#ifndef JLIB_REALLOC
#include <stdlib.h>
#define JLIB_REALLOC realloc
#endif //JLIB_REALLOC

#ifndef JLIB_FREE
#include <stdlib.h>
#define JLIB_FREE free
#endif //JLIB_FREE

void* arena_alloc(arena_t* arena, size_t size)
{
	void* ret_ptr = NULL;
	if (arena->base_ptr == NULL) {
		arena->base_ptr = JLIB_MALLOC(size);
		arena->alloc_pos = arena->base_ptr;
	} else {
		size_t current_size = (size_t)((char*)arena->alloc_pos - (char*)arena->base_ptr);
		void* tmp_ptr = arena->base_ptr;
		tmp_ptr = realloc(tmp_ptr, current_size + size);
		arena->base_ptr = tmp_ptr;
		arena->alloc_pos = (void*)((char*)arena->base_ptr + current_size);
	}
	ret_ptr = arena->alloc_pos;
	arena->alloc_pos = (void*)((char*)arena->alloc_pos + size);
	return ret_ptr;
}

void arena_free(arena_t* arena)
{
	JLIB_FREE(arena->base_ptr);
	arena->base_ptr = NULL;
	arena->alloc_pos = NULL;
}

string_t string_create(arena_t* arena, size_t size)
{
	string_t str = {0};
	str.str = arena_alloc(arena, size);
	str.size = size;
	return str;
}

#endif //JLIB_IMPLEMENTATION
#endif //JLIB_H_
