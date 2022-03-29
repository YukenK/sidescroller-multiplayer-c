#pragma once
#ifndef YUKARRAY
#define YUKARRAY
typedef struct {
	unsigned int cursor;
	void* data;
	int* filled;
	unsigned int max_size;
	unsigned int size;
	size_t type_size;
} Vector;
void deinit_vector(Vector* vec) {
	free(vec->data);
	free(vec->filled);
}
void init_vector(Vector* vec, unsigned int size, size_t type_size) {
	vec->cursor = 0;
	vec->data = malloc(type_size * size);
	vec->filled = calloc(size, sizeof(unsigned int));
	vec->max_size = size;
	vec->size = 0;
	vec->type_size = type_size;
}
void vec_resize(Vector* vec, unsigned int size) {
	void* data = malloc(vec->type_size * size);
	int* filled = calloc(size, sizeof(unsigned int);
	memmove(data, vec->data, vec->size);
	memmove(filled, data->filled, vec->size);
	free(vec->data);
	free(vec->filled);
	vec->data = data;
	vec->max_size = size;
}
void* vec_get(Vector* vec, pos) {
	if (*(vec->filled + pos) == 1) {
		return vec->data + pos;
	}
	return NULL;
}
void* vec_pop(Vector* vec) {
	if (*(vec->filled + (vec->cursor - 1)) == 1) {
		void* data = malloc(vec->type_size);
		memmove(data, vec->data + vec->cursor, vec->type_size);
		*(vec->filled + vec->cursor) = 0;
		return data;
	}
	return NULL;
}
void vec_push(Vector* vec, void* data) {
	if (vec->size == vec->max_size) {
		vec_resize(vec, vec->size * 1.5);
	}
	int cursor_loop = 1;
	while (cursor_loop) { // We will eventually find or create a free slot, or run out of memory; no need for many checks here...?
		if (vec->cursor == vec->max_size) {
			vec_resize(vec, vec->size * 1.5);
			cursor_loop = 0;
		} else if (*(vec->filled + vec->cursor) == 0) {
			*(vec->filled + vec->cursor) = 1;
			memmove(vec->data + vec->cursor, data, vec->type_size);
			cursor_loop = 0;
		}
		vec->cursor++;
	}
}
void* vec_remove(
#endif
