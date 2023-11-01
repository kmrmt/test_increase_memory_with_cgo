#include "c.h"
#include <stdlib.h>
#include <stdio.h>

int main() {
    const int dim = 128;
    const int size = 1000000;

    header();
    stat("start");

    float* vectors = (float*)malloc(sizeof(float) * dim * size);
    for (int i = 0; i < size; i++) {
        vectors[i * dim] = i;
    }
    size_t *ids = (size_t *)malloc(sizeof(size_t) * size);

    object_repository_t o = or_init();
    for (int n = 0; n < 100; n++) {
        stat("init");
        for (int i = 0; i < size; i++) {
            ids[i] = or_insert(o, &vectors[i * dim], dim);
        }
        stat("insert");

        for (int i = 0; i < size; i++) {
            or_remove(o, ids[i]);
        }
        stat("remove");
    }
    or_close(o);

    free(ids);
    free(vectors);

    stat("finish");
}