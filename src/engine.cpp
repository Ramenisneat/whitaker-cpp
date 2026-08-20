#include <whitaker/engine.hpp>
#include <whitaker/utils.hpp>
#include <algorithm>
#include <iostream>

namespace words{


    StemRange find_stems(const std::vector<StemRef> &stems, std::string_view target){
        auto cmp_lo = [](const StemRef &a, std::string_view b) {return a.stem < b;};
        auto cmp_hi = [](std::string_view a, const StemRef &b) {return a < b.stem;};

        auto lo = std::lower_bound(stems.begin(), stems.end(), target, cmp_lo);
        auto hi = std::upper_bound(stems.begin(), stems.end(), target, cmp_hi);

        return {stems.data() + (lo - stems.begin()),
                stems.data() + (hi - stems.begin())};

    }


    bool is_consistent(const DictEntry &entry, const InflEntry &infl, const StemRef &stem){
        // if (infl.pos != entry.pos) return false;
        // if (infl. != dict.which) return false;

        /* My own scratch notes from og
         function "<=" (Left, Right : Stem_Key_Type)   return Boolean is
         begin
            if Right = Left or else Right = 0 then
               return True;
            else
               return False;
            end if;
         end "<=";


         ((Pdl_Key <= Sl (I).IR.Key))  or else
                    ((Pdl_Key = 0)  and then
                    (X and then
                    Y)
                     )  and then   --  and KEY
                    (Pdl_Part.Pofs  = Eff_Part (Sl (I).IR.Qual.Pofs))
        */


        //The parse record/scratch record is being built here. gonna just return all parts and construct at display time. 
        if ((stem.key == infl.stemKey || infl.stemKey == 0) || 
            (stem.key == 0 && (entry.pos == PartOfSpeech::NOUN || entry.pos == PartOfSpeech::ADJECTIVE || entry.pos == PartOfSpeech::VERB) && (infl.stemKey == 1 || infl.stemKey == 2))
        ){
            if (entry.pos == infl.pos || (entry.pos == PartOfSpeech::VERB && (infl.pos == PartOfSpeech::VPARTICIPLE || infl.pos == PartOfSpeech::SUPINE))){
                switch (entry.pos)
                {
                case PartOfSpeech::NOUN:
                    return cmp_decn(entry.type.noun.decl, entry.type.noun.var, infl.quality.noun.decl, infl.quality.noun.var) && 
                        cmp_gender(entry.type.noun.gender, infl.quality.noun.gender);
                
                case PartOfSpeech::PRONOUN:
                    return cmp_decn(entry.type.pronoun.decl, entry.type.pronoun.var, infl.quality.pronoun.decl, infl.quality.pronoun.var);
                    
                case PartOfSpeech::ADJECTIVE:
                    return cmp_decn(entry.type.adjective.decl, entry.type.adjective.var, infl.quality.adjective.decl, infl.quality.adjective.var) && 
                        ((infl.quality.adjective.param == entry.type.adjective.param || entry.type.adjective.param == Comparison::UNKNOWN) ||
                         infl.quality.adjective.param == Comparison::UNKNOWN ||
                         entry.type.adjective.param == Comparison::UNKNOWN
                        );
                
                case PartOfSpeech::NUMERAL:
                    return cmp_decn(entry.type.numeral.decl, entry.type.numeral.var, infl.quality.numeral.decl, infl.quality.numeral.var) &&
                        stem.key == infl.stemKey;
                
                case PartOfSpeech::ADVERB:
                    return (infl.quality.adverb.param == entry.type.adverb.param || infl.quality.adverb.param == Comparison::UNKNOWN) ||
                         infl.quality.adverb.param == Comparison::UNKNOWN ||
                         entry.type.adverb.param == Comparison::UNKNOWN;

                case PartOfSpeech::VERB:
                    if (infl.pos == PartOfSpeech::VERB)
                        return cmp_decn(entry.type.verb.decl, entry.type.verb.var, infl.quality.verb.decl, infl.quality.verb.var);
                    else if (infl.pos == PartOfSpeech::VPARTICIPLE)
                        return cmp_decn(entry.type.verb.decl, entry.type.verb.var, infl.quality.vpar.decl, infl.quality.vpar.var);
                    else if (infl.pos == PartOfSpeech::SUPINE)
                        return cmp_decn(entry.type.verb.decl, entry.type.verb.var, infl.quality.supine.decl, infl.quality.supine.var);
                    return false; //Should I error check?
                
                case PartOfSpeech::PREPOSITION:
                    return entry.type.preposition.case_ == infl.quality.preposition.case_;
                
                case PartOfSpeech::INTERJECTION:
                case PartOfSpeech::CONJUNCTION:
                    return true;

                    
                default:
                    std::cerr << "NOT REACHABLE. POS not used" << std::endl;
                }
            }  
        }

        return false;
    }

    void run_inflections(const Corpus& corpus, std::string_view &line, std::vector<Candidate> &candidates){

        size_t max_len = std::min(MAX_INFLECTION_SIZE, line.size());
        for (size_t k = 0; k <= max_len; ++k){
            size_t i = line.size() - k;
            std::string_view ending = line.substr(i);
            std::string_view stem = line.substr(0, i);

            // std::cout << stem << " + " << ending << std::endl; 

            auto [lo, hi] = find_stems(corpus.stemlist, stem);

            //Might want to switch nested loop order: inflections then stems
            for (auto it = lo; it != hi; ++it) {
                //There is a max_stem_size. Should incorporate
                const DictEntry &dict = corpus.dictionary[it->idx];
                for (const auto &i : corpus.inflections){
                    if (i.ending.ending == ending){
                        // std::cout << it->stem << " + " << ending << std::endl; 
                        if (is_consistent(dict, i, *it))
                            candidates.push_back((Candidate){.stem = it->stem, .inflection = i, .entry = dict});
                    }
                }

            }

            
        }
    }


    void try_uniques(const Corpus &corpus, std::string_view &line, std::vector<Candidate> &candidates){
        
        for (auto &unique : corpus.uniques){
            if (line == unique.stem){
                candidates.push_back((Candidate){.unique = unique});
            }
        }


    }

    //Maybe bundle params into a "corpus"
    std::vector<Candidate> parse_latin(const Corpus &corpus, std::string_view line){

        std::vector<Candidate> candidates;

        //Need to normalize for u and v (QVAE kludge)
        line = trim(line);
        
        try_uniques(corpus, line, candidates);
        run_inflections(corpus, line, candidates);

        std::cout << "size of candidates: " << candidates.size() << std::endl;

        return candidates;
    }


    void printCandidates(std::ostream& os, const std::vector<Candidate>& candidates){
        for (size_t i = 0; i < candidates.size(); ++i){
            os << "[" << i << "] " << candidates[i] << "\n";
        }
    }

    std::ostream& operator<<(std::ostream& os, const Candidate& candidate){
        os << "dict: " << candidate.entry << std::endl << "infl: " << candidate.inflection << std::endl << "stem: " << candidate.stem << std::endl << "unq: " << candidate.unique << std::endl;
        return os;
    }
}