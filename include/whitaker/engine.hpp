#pragma once

#include <whitaker/types.hpp>
#include <string>
#include <vector>


namespace words{

    constexpr size_t MAX_INFLECTION_SIZE = 7;


    struct StemRange{
        const StemRef *begin;
        const StemRef *end;

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

    
    
    std::vector<Candidate> parse_latin(const Corpus &corpus, std::string_view line);
}