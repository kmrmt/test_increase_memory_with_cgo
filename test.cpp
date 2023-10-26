#include <iostream>
#include <vector>
#include <queue>
#include <memory>
#include <fstream>
#include <sstream>
#include <string.h>
#include <execinfo.h>
#include <unistd.h>
#include <time.h>
#include "test.h"

std::string now() {
    time_t timer = time(NULL);
    struct tm *local_time = localtime(&timer);
    char time_str[64];
    strftime(time_str, 64, "%Y-%m-%d %H:%M:%S", local_time);
    return std::string(time_str);
}

void header() {
    printf("%s\toperation\tVmPeak\tVmSize\tVmHWM\tVmRSS\n", now().c_str());
}

void stat(const char *op) {
    pid_t pid = getpid();
    std::stringstream ss;
    ss << "/proc/" << pid << "/status";
    std::string filename;
    ss >> filename;

    std::ifstream ifs(filename);
    int vmpeak, vmsize, vmhwm, vmrss;
    std::string buf;
    while (std::getline(ifs, buf)) {
        std::stringstream b(buf);
        std::string type;
        int val;
        b >> type >> val;
        if (type == "VmPeak:") {
            vmpeak = val;
        } else if (type == "VmSize:") {
            vmsize = val;
        } else if (type == "VmHWM:") {
            vmhwm = val;
        } else if (type == "VmRSS:") {
            vmrss = val;
            break;
        }
    }

    printf("%s\t%s\t%d\t%d\t%d\t%d\n", now().c_str(), op, vmpeak, vmsize, vmhwm, vmrss);
}

std::vector<float*> object_repository;
std::priority_queue<size_t, std::vector<size_t>, std::greater<size_t> >	removed_list;

size_t insert(float* v, size_t size) {
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

void remove_(size_t i) {
    delete[] object_repository[i];
    object_repository[i] = nullptr;
    removed_list.push(i);
}
