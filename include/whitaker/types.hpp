#pragma once

#include <whitaker/enums.hpp>
#include <array>
#include <string>
#include <cstdint>
#include <iosfwd>
#include <vector>

// https://mk270.github.io/whitakers-words/user_modifications.html
namespace words{

struct NounType{
    uint8_t decl = 0;
    uint8_t var = 0;
    Gender gender = Gender::UNKNOWN;
    NounKind kind = NounKind::UNKNOWN;
};

struct VerbType{
    uint8_t decl = 0;
    uint8_t var = 0;
    VerbKind kind = VerbKind::UNKNOWN;

};

struct PronounType{
    uint8_t decl = 0;
    uint8_t var = 0;
    PronounKind kind = PronounKind::UNKNOWN;

};


struct NumeralType{
    uint8_t decl = 0;
    uint8_t var = 0;
    NumeralSort sort = NumeralSort::UNKNOWN;
    uint8_t value = 0;

};

struct PackType{
    uint8_t decl = 0;
    uint8_t var = 0;
    PronounKind kind = PronounKind::UNKNOWN;
};


struct AdjectiveType{
    uint8_t decl = 0;
    uint8_t var = 0;
    Comparison param = Comparison::UNKNOWN;
};

struct AdverbType{
    Comparison param = Comparison::UNKNOWN;
};


struct PrepositionType{
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
        NounType noun;
        VerbType verb;
        PronounType pronoun;
        NumeralType numeral;
        AdjectiveType adjective;
        AdverbType adverb;
        PrepositionType preposition;
        PackType packon;
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
    size_t prin;

};

std::ostream& operator<<(std::ostream& os, const DictEntry& entry);
std::ostream& operator<<(std::ostream& os, const StemRef& ref);

void printDictionary(std::ostream& os, const std::vector<DictEntry>& entries);
void printStemList(std::ostream& os, const std::vector<StemRef>& stemList);

}