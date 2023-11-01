#pragma once

#include "../object_repository.hpp"
#include "../c.h"
#include <memory>

std::unique_ptr<ObjectRepository> create();
