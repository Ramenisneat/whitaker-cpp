#pragma once

#include <whitaker/types.hpp>
#include <string>
#include <vector>

namespace words{

    void loadDictionary(std::string &fileName, std::vector<DictEntry> &entries, std::vector<StemRef> &stemList);
    void loadInflections(std::string &fileName, std::vector<InflEntry> &inflections);
    void loadUniques(std::string &fileName, std::vector<UniqueEntry> &uniques);
    void loadAddons(std::string &fileName);


}