#include "object_repository.hpp"
#include <cstring>
#include <iostream>

ObjectRepository::ObjectRepository(): object_repository(), removed_list() {}

size_t ObjectRepository::insert(float* v, size_t size) {
    float* arr = new float[size];
    memcpy(arr, v, size);
    if (!removed_list.empty()) {
        size_t i = removed_list.top();
        removed_list.pop();
        object_repository[i] = arr;
        return i;
    } else {
        object_repository.push_back(arr);
        return object_repository.size() - 1;
    }
}

void ObjectRepository::remove(size_t i) {
    delete[] object_repository[i];
    object_repository[i] = nullptr;
    removed_list.push(i);
}

size_t ObjectRepository::size() const {
    return object_repository.size();
}

float* ObjectRepository::get(size_t i) {
    return object_repository[i];
}

float* ObjectRepository::operator[](size_t i) {
    return object_repository[i];
}
