#pragma once

#include <whitaker/enums.hpp>
#include <array>
#include <string>
#include <cstdint>
#include <iosfwd>
#include <vector>

// https://mk270.github.io/whitakers-words/user_modifications.html
namespace words{

struct NounEntry{
    uint8_t decl = 0;
    uint8_t var = 0;
    Gender gender = Gender::UNKNOWN;
    NounKind kind = NounKind::UNKNOWN;
};

struct VerbEntry{
    uint8_t decl = 0;
    uint8_t var = 0;
    VerbKind kind = VerbKind::UNKNOWN;

};

struct PronounEntry{
    uint8_t decl = 0;
    uint8_t var = 0;
    PronounKind kind = PronounKind::UNKNOWN;

};


struct NumeralEntry{
    uint8_t decl = 0;
    uint8_t var = 0;
    NumeralSort sort = NumeralSort::UNKNOWN;
    uint8_t value = 0;

};

struct PropackEntry{
    uint8_t decl = 0;
    uint8_t var = 0;
    PronounKind kind = PronounKind::UNKNOWN;
};


struct AdjectiveEntry{
    uint8_t decl = 0;
    uint8_t var = 0;
    Comparison param = Comparison::UNKNOWN;
};

struct AdverbEntry{
    Comparison param = Comparison::UNKNOWN;
};


struct PrepositionEntry{
    Case case_ = Case::UNKNOWN;
    
};

//IDK if this is needed
// struct ConjunctionType{

// };

// struct InterjectionType{

// };

struct DictEntry{
    std::array<std::string, 4> stems;

    PartOfSpeech pos = PartOfSpeech::UNKNOWN;

    union Type {
        NounEntry noun;
        VerbEntry verb;
        PronounEntry pronoun;
        NumeralEntry numeral;
        AdjectiveEntry adjective;
        AdverbEntry adverb;
        PrepositionEntry preposition;
        PropackEntry propack;
        std::uint8_t raw;
        constexpr Type() : raw(0) {}
    };

    Type type{};

    struct Flags {
        Age age = Age::UNKNOWN;
        Area area = Area::UNKNOWN;
        Geography geo = Geography::UNKNOWN;
        Frequency freq = Frequency::UNKNOWN;
        Source source = Source::UNKNOWN;
    } flags;
    std::string meaning;


};


//May have to add type param
struct StemRef{
    std::string stem;
    size_t idx;
    size_t key;

};


//INFLECTIONS
//Can collapse some of these records
struct NounRecord{
    uint8_t decl = 0;
    uint8_t var = 0;
    Case case_ = Case::UNKNOWN;
    Number number = Number::UNKNOWN;
    Gender gender = Gender::UNKNOWN;

};

struct PronounRecord{
    uint8_t decl = 0;
    uint8_t var = 0;
    Case case_ = Case::UNKNOWN;
    Number number = Number::UNKNOWN;
    Gender gender = Gender::UNKNOWN;

};

struct PropackRecord{
    uint8_t decl = 0;
    uint8_t var = 0;
    Case case_ = Case::UNKNOWN;
    Number number = Number::UNKNOWN;
    Gender gender = Gender::UNKNOWN;

};

struct AdjectiveRecord{
    uint8_t decl = 0;
    uint8_t var = 0;
    Case case_ = Case::UNKNOWN;
    Number number = Number::UNKNOWN;
    Gender gender = Gender::UNKNOWN;
    Comparison param = Comparison::UNKNOWN;

};


struct NumeralRecord{
    uint8_t decl = 0;
    uint8_t var = 0;
    Case case_ = Case::UNKNOWN;
    Number number = Number::UNKNOWN;
    Gender gender = Gender::UNKNOWN;
    NumeralSort sort = NumeralSort::UNKNOWN;

};

struct AdverbRecord{
    Comparison param = Comparison::UNKNOWN;
};


struct TVM{
        Tense tense = Tense::UNKNOWN;
        Voice voice = Voice::UNKNOWN;
        Mood mood = Mood::UNKNOWN;
};

struct VerbRecord{
    uint8_t decl = 0;
    uint8_t var = 0;
    TVM tvm;
    uint8_t person = 0; // 0..3
    Number number = Number::UNKNOWN;
};

struct VparRecord{
    uint8_t decl = 0;
    uint8_t var = 0;
    Case case_ = Case::UNKNOWN;
    Number number = Number::UNKNOWN;
    Gender gender = Gender::UNKNOWN;
    TVM tvm;

};

struct SupineRecord{
    uint8_t decl = 0;
    uint8_t var = 0;
    Case case_ = Case::UNKNOWN;
    Number number = Number::UNKNOWN;
    Gender gender = Gender::UNKNOWN;
};

struct PrepositionRecord{
    Case case_ = Case::UNKNOWN;
};

//Rest are null records no need;

struct InflEntry{

    PartOfSpeech pos = PartOfSpeech::UNKNOWN;

    union Quality {
        NounRecord noun;
        PronounRecord pronoun;
        PropackRecord propack;
        AdjectiveRecord adjective;
        NumeralRecord numeral;
        AdverbRecord adverb;
        VerbRecord verb;
        VparRecord vpar;
        SupineRecord supine;
        PrepositionRecord preposition;
        std::uint8_t raw;
        constexpr Quality() : raw(0) {}
    };

    Quality quality{};

    size_t stemKey = 0;

    struct Ending {
        size_t ending_size = 0; //Max is 7 (line 810 in https://github.com/mk270/whitakers-words/blob/master/src/latin_utils/latin_utils-inflections_package.ads)
        std::string ending;
    } ending;

    Age age = Age::UNKNOWN;
    Frequency freq = Frequency::UNKNOWN;


};

struct Candidate{
    StemRef stem;
    InflEntry inflection;
    DictEntry entry;
};


std::ostream& operator<<(std::ostream& os, const DictEntry& entry);
std::ostream& operator<<(std::ostream& os, const InflEntry& entry);
std::ostream& operator<<(std::ostream& os, const StemRef& ref);
std::ostream& operator<<(std::ostream& os, const Candidate& candidate);

void printDictionary(std::ostream& os, const std::vector<DictEntry>& entries);
void printStemList(std::ostream& os, const std::vector<StemRef>& stemList);
void printInflections(std::ostream& os, const std::vector<InflEntry>& inflections);
void printCandidates(std::ostream& os, const std::vector<Candidate>& candidates);
}