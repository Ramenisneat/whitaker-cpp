#pragma once

#include <enums.hpp>
#include <array>
#include <string>
#include <cstdint>

// https://mk270.github.io/whitakers-words/user_modifications.html
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


//TODO
struct NumeralType{
    uint8_t decl = 0;
    uint8_t var = 0;

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
    union{
        NounType noun;
        VerbType verb;
        PronounType pronoun;
        NumeralType numeral;
        AdjectiveType adjective;
        AdverbType adverb;
        PrepositionType preposition;
    };

    //Translation 
    //Meaning
    //TODO: WILL ENUMERATE o7
    std::string rest;


};

}