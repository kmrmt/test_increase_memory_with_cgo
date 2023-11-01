#include "c.h"
#include "object_repository.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <execinfo.h>
#include <unistd.h>
#include <time.h>

void header() {
    std::cout << "time\toperation\tVmPeak\tVmSize\tVmHWM\tVmRSS" << std::endl;
}

void stat(const char *op) {
    pid_t pid = getpid();
    std::stringstream ss;
    ss << "/proc/" << pid << "/status";

    std::ifstream ifs(ss.str());
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

    time_t timer = time(NULL);
    struct tm *local_time = localtime(&timer);
    char now[64];
    strftime(now, 64, "%Y-%m-%d %H:%M:%S", local_time);
    std::cout << now << "\t" << op << "\t" << vmpeak << "\t" << vmsize << "\t" << vmhwm << "\t" << vmrss << std::endl;
}

object_repository_t or_init() {
    return static_cast<object_repository_t>(new ObjectRepository());
}

void or_close(object_repository_t o) {
    delete static_cast<ObjectRepository*>(o);
}

size_t or_insert(object_repository_t o, float* v, size_t size) {
    return (static_cast<ObjectRepository*>(o))->insert(v, size);
}

void or_remove(object_repository_t o, size_t i) {
    (static_cast<ObjectRepository*>(o))->remove(i);
}

float* or_get(object_repository_t o, size_t i) {
    return (static_cast<ObjectRepository*>(o))->get(i);
}

size_t or_size(object_repository_t o) {
    return (static_cast<ObjectRepository*>(o))->size();
}
