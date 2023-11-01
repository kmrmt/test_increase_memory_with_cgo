#pragma once

#include <stddef.h>
#include <vector>
#include <queue>

class ObjectRepository{
    std::vector<float*> object_repository;
    std::priority_queue<size_t, std::vector<size_t>, std::greater<size_t> >	removed_list;
public:
    ObjectRepository();
    size_t insert(float*, size_t);
    void remove(size_t);
    size_t size() const;
    float* get(size_t);
    float* operator[](size_t);
};
