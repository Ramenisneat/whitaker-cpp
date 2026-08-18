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
        DictEntry entry;
    };

    inline bool cmp_gender (Gender a, Gender b){
        return (a == b || (b == Gender::COMMON && a != Gender::NEUTER) || b == Gender::UNKNOWN);
    }

    inline bool cmp_decn (uint8_t a_decl, uint8_t a_var, uint8_t b_decl, uint8_t b_var){
        if (a_decl == b_decl && a_var == b_var)
            return true;
        
        if (a_decl != 9 && (b_decl == 0 && b_var == 0))
            return true;
        
        if (b_decl == a_decl && b_var == 0)
            return true;
        
        return false;
    }

    std::ostream& operator<<(std::ostream& os, const Candidate& candidate);
    void printCandidates(std::ostream& os, const std::vector<Candidate>& candidates);
    
    std::vector<Candidate> parse_latin(const std::vector<DictEntry> &dictionary, const std::vector<InflEntry> &inflections, const std::vector<StemRef> &stems, std::string_view line);
}