#include "test.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    const int dim = 128;
    const int size = 1000000;

    header();
    stat("start");

    float* vectors = (float*)malloc(sizeof(float) * dim * size);
    for (int i = 0; i < size; i++) {
        vectors[i * dim] = i;
    }

    for (int n = 0; n < 100; n++) {
        size_t *ids = (size_t *)malloc(sizeof(size_t) * size);
        stat("init");
        for (int i = 0; i < size; i++) {
            ids[i] = insert(&vectors[i * dim], dim);
        }
        stat("insert");

        for (int i = 0; i < size; i++) {
            remove_(ids[i]);
        }
        stat("remove");
        free(ids);
    }
    
    free(vectors);

    stat("finish");
}