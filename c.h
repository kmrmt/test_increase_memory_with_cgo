#pragma once

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void header();
void stat(const char*);

typedef void* object_repository_t;

object_repository_t or_init();
void or_close(object_repository_t);
size_t or_insert(object_repository_t, float*, size_t);
void or_remove(object_repository_t, size_t);
float* or_get(object_repository_t, size_t);
size_t or_size(object_repository_t);

#ifdef __cplusplus
}
#endif
