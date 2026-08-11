#include <whitaker/enums.hpp>
#include <whitaker/types.hpp>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <charconv>



namespace words{

    //Derived from DICTLINE.GEN from mk270's repo
    constexpr size_t STEM_WIDTH = 19;
    constexpr size_t NUM_STEMS = 4;
    constexpr size_t POS_START = 76;
    constexpr size_t TYPE_START = 83;
    constexpr size_t FLAGS_START = 100;
    constexpr size_t MEANINGS_START = 110;


    //Taken from https://mobiarch.wordpress.com/2022/12/12/string-to-number-conversion-in-modern-c/
    template <typename T>
    bool vtonum(const std::string_view &view, T& value) {
        if (view.empty()) {
            return false;
        }
        
        const char* first = view.data();
        const char* last = view.data() + view.length();
        
        std::from_chars_result res = std::from_chars(first, last, value);
        
        if (res.ec != std::errc()) {
            return false;
        }
        
        if (res.ptr != last) {
            return false;
        }
        
        return true;
    }


    //AI SLOP
    std::string_view rtrim(std::string_view s) {
        while (!s.empty() && (s.back() == ' ' || s.back() == '\t' || s.back() == '\r')) {
            s.remove_suffix(1);
        }
        return s;
    }

    std::string_view ltrim(std::string_view s) {
        while (!s.empty() && (s.front() == ' ' || s.front() == '\t')) {
            s.remove_prefix(1);
        }
        return s;
    }

    std::string_view trim(std::string_view s) { return rtrim(ltrim(s)); }

    void parseLine(std::string_view line, DictEntry &entry){

        //STEMS
        for (size_t i = 0; i < NUM_STEMS; i++){
            auto stem = trim(line.substr(i * STEM_WIDTH, STEM_WIDTH));
            // std::cout << stem << " "; 
            entry.stems[i] = stem;
        }


        //POS
        auto POS_raw = trim(line.substr(POS_START, TYPE_START-POS_START));
        // std::cout << POS_raw << " ";
        entry.pos = parse_enum<PartOfSpeech>(POS_raw);

        //TYPE
        auto type_raw = trim(line.substr(TYPE_START, FLAGS_START-TYPE_START));

        //split params into array for easy parsing
        std::string_view split_type[4] = {};
        size_t index = 0;
        size_t start = 0;

        while (index < std::size(split_type)) {
            while (start < type_raw.size() && type_raw[start] == ' ') start++;
            if (start >= type_raw.size()) break;

            size_t end = type_raw.find(" ", start);
            if (end == std::string_view::npos) end = type_raw.size();

            split_type[index++] = type_raw.substr(start, end - start);
            start = end;
        }

        // std::cout << "[ ";
        // for (const auto& s : split_type) std::cout << "\"" << s << "\" ";
        // std::cout << "]\n";

        switch (entry.pos)
        {
            case PartOfSpeech::NOUN:
                vtonum(split_type[0], entry.type.noun.decl);
                vtonum(split_type[1], entry.type.noun.var);
                entry.type.noun.gender = parse_enum<Gender>(split_type[2]);
                entry.type.noun.kind = parse_enum<NounKind>(split_type[3]);                
                break;

            case PartOfSpeech::VERB:
                vtonum(split_type[0], entry.type.verb.decl);
                vtonum(split_type[1], entry.type.verb.var);
                entry.type.verb.kind = parse_enum<VerbKind>(split_type[2]);                
                break;

            case PartOfSpeech::PRONOUN:
                vtonum(split_type[0], entry.type.pronoun.decl);
                vtonum(split_type[1], entry.type.pronoun.var);
                entry.type.pronoun.kind = parse_enum<PronounKind>(split_type[2]);
                break;
            
            case PartOfSpeech::NUMERAL:
                vtonum(split_type[0], entry.type.numeral.decl);
                vtonum(split_type[1], entry.type.numeral.var);
                entry.type.numeral.sort = parse_enum<NumeralSort>(split_type[2]);
                vtonum(split_type[3], entry.type.numeral.value);
                break;

            case PartOfSpeech::ADJECTIVE:
                vtonum(split_type[0], entry.type.adjective.decl);
                vtonum(split_type[1], entry.type.adjective.var);
                entry.type.adjective.param = parse_enum<Comparison>(split_type[2]);
                break;


            case PartOfSpeech::ADVERB:
                entry.type.adverb.param = parse_enum<Comparison>(split_type[0]);
                break;
            
            case PartOfSpeech::PREPOSITION:
                entry.type.preposition.case_ = parse_enum<Case>(split_type[0]);
                break;


            case PartOfSpeech::PACKON:
                vtonum(split_type[0], entry.type.packon.decl);
                vtonum(split_type[1], entry.type.packon.var);
                entry.type.packon.kind = parse_enum<PronounKind>(split_type[2]);
                break;

            case PartOfSpeech::INTERJECTION:
            case PartOfSpeech::CONJUNCTION:
                break;
            
            
            default:
                std::cerr << "NOT YET IMPLEMENTED POS: " << POS_raw << std::endl;
                break;
        }
        // std::cout << type_raw << " ";

        //FLAGS
        auto flags_raw = trim(line.substr(FLAGS_START, MEANINGS_START-FLAGS_START));
        // std::cout << flags_raw << std::endl;

        std::string_view split_flags[5] = {};
        index = 0;
        start = 0;

        while (index < std::size(split_flags)) {
            while (start < flags_raw.size() && flags_raw[start] == ' ') start++;
            if (start >= flags_raw.size()) break;

            size_t end = flags_raw.find(" ", start);
            if (end == std::string_view::npos) end = flags_raw.size();

            split_flags[index++] = flags_raw.substr(start, end - start);
            start = end;
        }


        //  std::cout << "[";
        // for (int i = 0; i < 5; i++) {
        //     std::cout << split_flags[i];
        //     if (i < 5 - 1) {
        //         std::cout << ", ";
        //     }
        // }
        // std::cout << "]" << std::endl;


        entry.flags.age = parse_enum<Age>(split_flags[0]);
        entry.flags.area = parse_enum<Area>(split_flags[1]);
        entry.flags.geo = parse_enum<Geography>(split_flags[2]);
        entry.flags.freq = parse_enum<Frequency>(split_flags[3]);
        entry.flags.source = parse_enum<Source>(split_flags[4]);

        //MEANING
        auto meaning_raw = trim(line.substr(MEANINGS_START));
        entry.meaning = std::string(meaning_raw);

    }


    void buildStemRef(DictEntry &entry, std::vector<StemRef> &stemList, size_t idx){

        //principal stems are 1 based, because 0 can appear as a wildcard
        if (entry.pos == PartOfSpeech::NOUN && entry.stems[0] == entry.stems[1] && entry.stems[0] != "zzz" && !entry.stems[0].empty()){
            stemList.push_back((StemRef){entry.stems[0], idx, 0});
        }
        else if (entry.pos == PartOfSpeech::ADJECTIVE && entry.stems[0] == entry.stems[1] && entry.stems[0] != "zzz" && !entry.stems[0].empty()){
            stemList.push_back((StemRef){entry.stems[0], idx, 0});
            if (!entry.stems[2].empty() && entry.stems[2] != "zzz"){
                stemList.push_back((StemRef){entry.stems[2], idx, 3});
                

            }
            if (!entry.stems[3].empty() && entry.stems[3] != "zzz"){
                stemList.push_back((StemRef){entry.stems[3], idx, 4});
            }
        }
        else if (entry.pos == PartOfSpeech::ADJECTIVE && entry.type.adjective.param == Comparison::COMPARATIVE){
            stemList.push_back((StemRef){entry.stems[0], idx, 3});
        }
        else if (entry.pos == PartOfSpeech::ADJECTIVE && entry.type.adjective.param == Comparison::SUPERLATIVE){
            stemList.push_back((StemRef){entry.stems[0], idx, 4});
        }
        else if (entry.pos == PartOfSpeech::ADVERB && entry.type.adverb.param == Comparison::COMPARATIVE){
            stemList.push_back((StemRef){entry.stems[0], idx, 2});
        }
        else if (entry.pos == PartOfSpeech::ADVERB && entry.type.adverb.param == Comparison::SUPERLATIVE){
            stemList.push_back((StemRef){entry.stems[0], idx, 3});
        }
        else if (entry.pos == PartOfSpeech::VERB && entry.stems[0] == entry.stems[1] && entry.stems[0] != "zzz" && !entry.stems[0].empty()){
            stemList.push_back((StemRef){entry.stems[0], idx, 0});
            if (!entry.stems[2].empty() && entry.stems[2] != "zzz"){
                stemList.push_back((StemRef){entry.stems[2], idx, 3});
            }
            if (!entry.stems[3].empty() && entry.stems[3] != "zzz"){
                stemList.push_back((StemRef){entry.stems[3], idx, 4});
            }
        }
        else if (entry.pos == PartOfSpeech::NUMERAL && entry.type.numeral.sort == NumeralSort::CARDINAL){
            stemList.push_back((StemRef){entry.stems[0], idx, 1});
        }
        else if (entry.pos == PartOfSpeech::NUMERAL && entry.type.numeral.sort == NumeralSort::ORDINAL){
            stemList.push_back((StemRef){entry.stems[0], idx, 2});
        }
        else if (entry.pos == PartOfSpeech::NUMERAL && entry.type.numeral.sort == NumeralSort::DISTRIBUTIVE){
            stemList.push_back((StemRef){entry.stems[0], idx, 3});
        }
        else if (entry.pos == PartOfSpeech::NUMERAL && entry.type.numeral.sort == NumeralSort::ADVERB){
            stemList.push_back((StemRef){entry.stems[0], idx, 4});
        }
        else{
            for (uint8_t i = 0 ; i < 4; ++i){
                if (!entry.stems[i].empty() && entry.stems[i] != "zzz")
                    stemList.push_back((StemRef){entry.stems[i], idx, i+1});
            }
        }

    }


    std::vector<DictEntry> loadDictionary(std::string &fileName, std::vector<DictEntry> entries, std::vector<StemRef> &stemList){
        
        std::ifstream file(fileName);
        // std::vector<DictEntry> entries;

        if (!file.is_open()){
            std::cerr << "ERROR: FILE COULD NOT BE OPENED" << std::endl;
            return entries;
        }

        std::string line;
        DictEntry entry;

        size_t idx = 0;

        while (std::getline(file, line)){
            // std::cout << line << std::endl;
            //error handling
            parseLine(line, entry);
            entries.push_back(entry);
            //TODO, build stemList
            buildStemRef(entry, stemList, idx);
            ++idx;

            //Theres a case where if the dictionary kind is general it constructs and ESSE? See lines 282 https://github.com/mk270/whitakers-words/blob/master/src/commands/makedict_main.adb

        }

        file.close();

        return entries;

    }

    //AI SLOP
    std::ostream& operator<<(std::ostream& os, const DictEntry& entry){
        os << "[";
        bool first = true;
        for (const auto& stem : entry.stems){
            if (stem.empty()) continue;
            if (!first) os << ", ";
            os << stem;
            first = false;
        }
        os << "] (" << enum_name(entry.pos) << ") ";

        switch (entry.pos)
        {
            case PartOfSpeech::NOUN:
                os << "decl=" << +entry.type.noun.decl
                   << " var=" << +entry.type.noun.var
                   << " gender=" << enum_name(entry.type.noun.gender)
                   << " kind=" << enum_name(entry.type.noun.kind);
                break;

            case PartOfSpeech::VERB:
                os << "decl=" << +entry.type.verb.decl
                   << " var=" << +entry.type.verb.var
                   << " kind=" << enum_name(entry.type.verb.kind);
                break;

            case PartOfSpeech::PRONOUN:
                os << "decl=" << +entry.type.pronoun.decl
                   << " var=" << +entry.type.pronoun.var
                   << " kind=" << enum_name(entry.type.pronoun.kind);
                break;

            case PartOfSpeech::NUMERAL:
                os << "decl=" << +entry.type.numeral.decl
                   << " var=" << +entry.type.numeral.var
                   << " sort=" << enum_name(entry.type.numeral.sort)
                   << " value=" << +entry.type.numeral.value;
                break;

            case PartOfSpeech::ADJECTIVE:
                os << "decl=" << +entry.type.adjective.decl
                   << " var=" << +entry.type.adjective.var
                   << " comparison=" << enum_name(entry.type.adjective.param);
                break;

            case PartOfSpeech::ADVERB:
                os << "comparison=" << enum_name(entry.type.adverb.param);
                break;

            case PartOfSpeech::PREPOSITION:
                os << "case=" << enum_name(entry.type.preposition.case_);
                break;

            case PartOfSpeech::PACKON:
                os << "decl=" << +entry.type.packon.decl
                   << " var=" << +entry.type.packon.var
                   << " kind=" << enum_name(entry.type.packon.kind);
                break;

            default:
                break;
        }

        os << " age=" << enum_name(entry.flags.age)
           << " area=" << enum_name(entry.flags.area)
           << " geo=" << enum_name(entry.flags.geo)
           << " freq=" << enum_name(entry.flags.freq)
           << " source=" << enum_name(entry.flags.source);

        // if (!entry.rest.empty()) os << " -- " << entry.rest;

        return os;
    }

    std::ostream& operator<<(std::ostream& os, const StemRef& ref){
        os << "\"" << ref.stem << "\" (idx=" << ref.idx << ", prin=" << ref.prin << ")";
        return os;
    }

    void printDictionary(std::ostream& os, const std::vector<DictEntry>& entries){
        for (size_t i = 0; i < entries.size(); ++i){
            os << "[" << i << "] " << entries[i] << "\n";
        }
    }

    void printStemList(std::ostream& os, const std::vector<StemRef>& stemList){
        for (const auto& ref : stemList){
            os << ref << "\n";
        }
    }

}
