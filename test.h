#pragma once

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void header();
void stat(const char *op);
size_t insert(float*, size_t);
void remove_(size_t);

#ifdef __cplusplus
}
#endif