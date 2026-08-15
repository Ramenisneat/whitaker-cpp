#pragma once

#include <whitaker/types.hpp>
#include <string>
#include <vector>


namespace words{

    struct StemRange{
        const StemRef *begin;
        const StemRef *end;

    };

    struct Candidate{
        //void for now

        StemRef stem;
        InflEntry inflection;
    };

    void parse_latin(const std::vector<DictEntry> &dictionary, const std::vector<InflEntry> &inflections, const std::vector<StemRef> &stems, std::string_view line);
}