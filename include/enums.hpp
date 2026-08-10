#pragma once

namespace words{
    //TODO
    enum class DictionaryKind{
        //TODO
    };

    enum class PartOfSpeech{
        UNKNOWN, NOUN, VERB, ADVERB, ADJECTIVE, PREPOSITION, CONJUNCTION,  INTERJECTION, PRONOUN, PACKON, NUMERAL, VPARTICIPLE, SUPINE, TACKON, PREFIX, SUFFIX
    };

    enum class Gender{
        UNKNOWN, MALE, FEMALE, NEUTER, COMMON
    };


    //NOUNS
    enum class NounKind{
        UNKNOWN, SINGULAR, MULTIPLE, ABSTRACT, GROUP, PROPER, PERSON, THING, LOCALE, WHERE
    };

    //VERBS
    enum class VerbKind{
        UNKNOWN, TO_BE, TO_BEING, GENITIVE, DATIVE, ABLATIVE, TRANSITIVE, INTRANSITIVE, IMPERSONAL, DEPONENT, SEMIDEPONENT, PERFDEFINITE
    };

    //PREPOSITIONS
    enum class Case{
        UNKNOWN, NOMINATIVE, VOCATIVE, GENITIVE, LOCATIVE, DATIVE, ABLATIVE, ACCUSITIVE
    };

    //ADVERBS and ADJECTIVES
    enum class Comparison{
        UNKNOWN, POSITIVE, COMPARITIVE, SUPERLATIVE
    };

    //PRONOUNS
    enum class PronounKind{
        UNKNOWN, PERSONAL, RELATIVE, REFLEXIVE, DEMONSTRATIVE, INTERROGATIVE, INDEFINITE, ADJECTIVAL
    };


    enum class Number{
        UNKNOWN, SINGULAR, PLURAL
    };

    enum class NumeralSort{
        UNKNOWN, CARDINAL, ORDINAL, DISTRIBUTIVE, ADVERB

    };

    enum class Tense{
        UNKNOWN, PRESENT, IMPERFECT, FUTURE, PERFECT, PLUPERFECT, FUTPERF
    };

    enum class Voice{
        UNKNOWN, ACTIVE, PASSIVE
    };

    enum class Mood{
        UNKNOWN, INDICATIVE, SUBJUNCTIVE, IMPERATIVE, INFINITIVE, PARTICIPLE
    };


}