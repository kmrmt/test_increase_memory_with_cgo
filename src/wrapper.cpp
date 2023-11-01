#include "wrapper.hpp"

std::unique_ptr<ObjectRepository> create() {
    return std::make_unique<ObjectRepository>();
}
