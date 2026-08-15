#include <whitaker/engine.hpp>
#include <algorithm>
#include <iostream>

namespace words{
    size_t MAX_INFLECTION_SIZE = 7;


    StemRange find_stems(const std::vector<StemRef> &stems, std::string_view target){
        auto cmp_lo = [](const StemRef &a, std::string_view b) {return a.stem < b;};
        auto cmp_hi = [](std::string_view a, const StemRef &b) {return a < b.stem;};

        auto lo = std::lower_bound(stems.begin(), stems.end(), target, cmp_lo);
        auto hi = std::upper_bound(stems.begin(), stems.end(), target, cmp_hi);

        return {&*lo, &*hi};

    }


    bool is_consistent(const DictEntry &entry, const InflEntry &infl){
        if (infl.pos != entry.pos) return false;
        // if (infl. != dict.which) return false;

        return true;
    }

    std::vector<Candidate> run_inflections(const std::vector<DictEntry> dictionary, const std::vector<InflEntry> &inflections, const std::vector<StemRef> &stems, std::string_view &line){
        std::vector<Candidate> candidates;

        size_t max_len = std::min(MAX_INFLECTION_SIZE, line.size());
        for (size_t k = 0; k <= max_len; ++k){
            size_t i = line.size() - k;
            std::string_view ending = line.substr(i);
            std::string_view stem = line.substr(0, i);

            // std::cout << stem << " + " << ending << std::endl; 

            auto [lo, hi] = find_stems(stems, stem);
            // for (auto it = lo; it != hi; ++it) 
            //    

            for (auto it = lo; it != hi; ++it) {
               
                // std::cout << "stems: " << it->stem << std::endl;
                //There is a max_stem_size. Should incorporate
                DictEntry dict = dictionary[it->idx];
                for (const auto &i : inflections){
                    if (i.ending.ending == it->stem){
                        // std::cout << it->stem << " + " << ending << std::endl; 
                        if (is_consistent(dict, i))
                            candidates.push_back((Candidate){.stem = it->stem, .inflection = i});
                    }
                }

            }

            
        }
        return candidates;
    }

    //Maybe bundle params into a "corpus"
    void parse_latin(const std::vector<DictEntry> &dictionary, const std::vector<InflEntry> &inflections, const std::vector<StemRef> &stems, std::string_view line){

        std::vector<Candidate> candidates = run_inflections(dictionary, inflections, stems, line);

        std::cout << "size of candidates: " << candidates.size() << std::endl;
    }
}