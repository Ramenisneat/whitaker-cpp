#pragma once

#include <whitaker/types.hpp>
#include <string>
#include <vector>

namespace words{

    std::vector<DictEntry> loadDictionary(std::string fileName);

}