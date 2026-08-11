#pragma once

#include <array>
#include <cstdint>
#include <optional>
#include <string_view>
#include <utility>


namespace words{


    template <typename E>
    struct EnumEntry {
        std::string_view name;
        E value;
    };


    //TODO
    enum class DictionaryKind{
        //TODO
    };

    enum class PartOfSpeech{
        UNKNOWN, NOUN, VERB, ADVERB, ADJECTIVE, PREPOSITION, CONJUNCTION,  INTERJECTION, PRONOUN, PACKON, NUMERAL, VPARTICIPLE, SUPINE, TACKON, PREFIX, SUFFIX
    };

    inline constexpr EnumEntry<PartOfSpeech> pos_table[]= {
        {"X",      PartOfSpeech::UNKNOWN},
        {"N",      PartOfSpeech::NOUN},
        {"V",      PartOfSpeech::VERB},
        {"ADV",    PartOfSpeech::ADVERB},
        {"ADJ",    PartOfSpeech::ADJECTIVE},
        {"PREP",   PartOfSpeech::PREPOSITION},
        {"CONJ",   PartOfSpeech::CONJUNCTION},
        {"INTERJ", PartOfSpeech::INTERJECTION},
        {"PRON",   PartOfSpeech::PRONOUN},
        {"PACK",   PartOfSpeech::PACKON},
        {"NUM",    PartOfSpeech::NUMERAL},
        {"VPAR",   PartOfSpeech::VPARTICIPLE},
        {"SUPINE", PartOfSpeech::SUPINE},
        {"TACKON", PartOfSpeech::TACKON},
        {"PREFIX", PartOfSpeech::PREFIX},
        {"SUFFIX", PartOfSpeech::SUFFIX},
    };

    inline constexpr std::size_t pos_table_size = sizeof(pos_table) / sizeof(pos_table[0]);


    enum class Gender{
        UNKNOWN, MALE, FEMALE, NEUTER, COMMON
    };

    inline constexpr EnumEntry<Gender> gender_table[] = {
        {"X", Gender::UNKNOWN},
        {"M", Gender::MALE},
        {"F", Gender::FEMALE},
        {"N", Gender::NEUTER},
        {"C", Gender::COMMON},
    };

    inline constexpr std::size_t gender_table_size = sizeof(gender_table) / sizeof(gender_table[0]);


    //NOUNS
    enum class NounKind{
        UNKNOWN, SINGULAR, MULTIPLE, ABSTRACT, GROUP, PROPER, PERSON, THING, LOCALE, WHERE
    };

    inline constexpr EnumEntry<NounKind> noun_kind_table[] = {
        {"X", NounKind::UNKNOWN},
        {"S", NounKind::SINGULAR},
        {"M", NounKind::MULTIPLE},
        {"A", NounKind::ABSTRACT},
        {"G", NounKind::GROUP},
        {"N", NounKind::PROPER},
        {"P", NounKind::PERSON},
        {"T", NounKind::THING},
        {"L", NounKind::LOCALE},
        {"W", NounKind::WHERE},
    };

    inline constexpr std::size_t noun_kind_table_size = sizeof(noun_kind_table) / sizeof(noun_kind_table[0]);


    //VERBS
    enum class VerbKind{
        UNKNOWN, TO_BE, TO_BEING, GENITIVE, DATIVE, ABLATIVE, TRANSITIVE, INTRANSITIVE, IMPERSONAL, DEPONENT, SEMIDEPONENT, PERFDEFINITE
    };

    inline constexpr EnumEntry<VerbKind> verb_kind_table[] = {
        {"X",        VerbKind::UNKNOWN},
        {"TO_BE",    VerbKind::TO_BE},
        {"TO_BEING", VerbKind::TO_BEING},
        {"GEN",      VerbKind::GENITIVE},
        {"DAT",      VerbKind::DATIVE},
        {"ABL",      VerbKind::ABLATIVE},
        {"TRANS",    VerbKind::TRANSITIVE},
        {"INTRANS",  VerbKind::INTRANSITIVE},
        {"IMPERS",   VerbKind::IMPERSONAL},
        {"DEP",      VerbKind::DEPONENT},
        {"SEMIDEP",  VerbKind::SEMIDEPONENT},
        {"PERFDEF",  VerbKind::PERFDEFINITE},
    };

    inline constexpr std::size_t verb_kind_table_size = sizeof(verb_kind_table) / sizeof(verb_kind_table[0]);


    //PREPOSITIONS
    enum class Case{
        UNKNOWN, NOMINATIVE, VOCATIVE, GENITIVE, LOCATIVE, DATIVE, ABLATIVE, ACCUSITIVE
    };

    inline constexpr EnumEntry<Case> case_table[] = {
        {"X",   Case::UNKNOWN},
        {"NOM", Case::NOMINATIVE},
        {"VOC", Case::VOCATIVE},
        {"GEN", Case::GENITIVE},
        {"LOC", Case::LOCATIVE},
        {"DAT", Case::DATIVE},
        {"ABL", Case::ABLATIVE},
        {"ACC", Case::ACCUSITIVE},
    };

    inline constexpr std::size_t case_table_size = sizeof(case_table) / sizeof(case_table[0]);


    //ADVERBS and ADJECTIVES
    enum class Comparison{
        UNKNOWN, POSITIVE, COMPARATIVE, SUPERLATIVE
    };

    inline constexpr EnumEntry<Comparison> comparison_table[] = {
        {"X",     Comparison::UNKNOWN},
        {"POS",   Comparison::POSITIVE},
        {"COMP",  Comparison::COMPARATIVE},
        {"SUPER", Comparison::SUPERLATIVE},
    };

    inline constexpr std::size_t comparison_table_size = sizeof(comparison_table) / sizeof(comparison_table[0]);


    //PRONOUNS
    enum class PronounKind{
        UNKNOWN, PERSONAL, RELATIVE, REFLEXIVE, DEMONSTRATIVE, INTERROGATIVE, INDEFINITE, ADJECTIVAL
    };

    inline constexpr EnumEntry<PronounKind> pronoun_kind_table[] = {
        {"X",       PronounKind::UNKNOWN},
        {"PERS",    PronounKind::PERSONAL},
        {"REL",     PronounKind::RELATIVE},
        {"REFLEX",  PronounKind::REFLEXIVE},
        {"DEMONS",  PronounKind::DEMONSTRATIVE},
        {"INTERR",  PronounKind::INTERROGATIVE},
        {"INDEF",   PronounKind::INDEFINITE},
        {"ADJECT",  PronounKind::ADJECTIVAL},
    };

    inline constexpr std::size_t pronoun_kind_table_size = sizeof(pronoun_kind_table) / sizeof(pronoun_kind_table[0]);

    enum class NumeralSort{
        UNKNOWN, CARDINAL, ORDINAL, DISTRIBUTIVE, ADVERB

    };

    inline constexpr EnumEntry<NumeralSort> numeral_sort_table[] = {
        {"X",    NumeralSort::UNKNOWN},
        {"CARD", NumeralSort::CARDINAL},
        {"ORD",  NumeralSort::ORDINAL},
        {"DIST", NumeralSort::DISTRIBUTIVE},
        {"ADVERB", NumeralSort::ADVERB},
    };

    inline constexpr std::size_t numeral_sort_table_size = sizeof(numeral_sort_table) / sizeof(numeral_sort_table[0]);



    //FLAG STUFF

    enum class Age{
        UNKNOWN, ARCHAIC, EARLY, CLASSICAL, LATE, LATER, MEDIEVAL, SCHOLAR, MODERN
    };


    inline constexpr EnumEntry<Age> age_table[] = {
        {"X",    Age::UNKNOWN},
        {"A", Age::ARCHAIC},
        {"B", Age::EARLY},
        {"C", Age::CLASSICAL},
        {"D", Age::LATE},
        {"E", Age::LATER},
        {"F", Age::MEDIEVAL},
        {"G", Age::SCHOLAR},
        {"H", Age::MODERN},


    };

    inline constexpr std::size_t age_table_size = sizeof(age_table) / sizeof(age_table[0]);


    //Should I have a inflections and dictionary version for frequency? For now, I will stupidly make this enum
    enum class Frequency{
        UNKNOWN, A, B, C, D, E, F, I, M, N
    };


    inline constexpr EnumEntry<Frequency> freq_table[] = {
        {"X", Frequency::UNKNOWN},
        {"A", Frequency::A},
        {"B", Frequency::B},
        {"C", Frequency::C},
        {"D", Frequency::D},
        {"E", Frequency::E},
        {"F", Frequency::F},
        {"I", Frequency::I},
        {"M", Frequency::M},
        {"N", Frequency::N},

    };

    inline constexpr std::size_t freq_table_size = sizeof(freq_table) / sizeof(freq_table[0]);


    enum class Geography{
        UNKNOWN, AFRICA, BRITAIN, CHINA, SCAND, EGYPT, FRANCE, GERMANY, GREECE, ITALY, INDIA, BALKAN, NETHER, PERSIA, NEAST, RUSSIA, SPAIN, EEUR
    };


    inline constexpr EnumEntry<Geography> geo_table[] = {
        {"X", Geography::UNKNOWN},
        {"A", Geography::AFRICA},
        {"B", Geography::BRITAIN},
        {"C", Geography::CHINA},
        {"D", Geography::SCAND},
        {"E", Geography::EGYPT},
        {"F", Geography::FRANCE},
        {"G", Geography::GERMANY},
        {"H", Geography::GREECE},
        {"I", Geography::ITALY},
        {"J", Geography::INDIA},
        {"K", Geography::BALKAN},
        {"N", Geography::NETHER},
        {"P", Geography::PERSIA},
        {"Q", Geography::NEAST},
        {"R", Geography::RUSSIA},
        {"S", Geography::SPAIN},
        {"U", Geography::EEUR}
    };

    inline constexpr std::size_t geo_table_size = sizeof(geo_table) / sizeof(geo_table[0]);


    enum class Area{
        UNKNOWN, AGRI, BIO, DRAMA, ECCLE, GRAMM, LEGAL, POETIC, SCIENCE, TECH, WAR, MYTH
    };


    inline constexpr EnumEntry<Area> area_table[] = {
        {"X", Area::UNKNOWN},
        {"A", Area::AGRI},
        {"B", Area::BIO},
        {"D", Area::DRAMA},
        {"E", Area::ECCLE},
        {"G", Area::GRAMM},
        {"L", Area::LEGAL},
        {"P", Area::POETIC},
        {"S", Area::SCIENCE},
        {"T", Area::TECH},
        {"W", Area::WAR},
        {"M", Area::MYTH}
    };

    inline constexpr std::size_t area_table_size = sizeof(area_table) / sizeof(area_table[0]);


    /*
        A,
        B,  --  C.H.Beeson, A Primer of Medieval Latin, 1925 (Bee)
        C,  --  Charles Beard, Cassell's Latin Dictionary 1892 (Cas)
        D,  --  J.N.Adams, Latin Sexual Vocabulary, 1982 (Sex)
        E,  --  L.F.Stelten, Dictionary of Eccles. Latin, 1995 (Ecc)
        F,  --  Roy J. Deferrari, Dictionary of St. Thomas Aquinas, 1960 (DeF)
        G,  --  Gildersleeve + Lodge, Latin Grammar 1895 (G+L)
        H,  --  Collatinus Dictionary by Yves Ouvrard
        I,  --  Leverett, F.P., Lexicon of the Latin Language, Boston 1845
        J,  --  Bracton: De Legibus Et Consuetudinibus Angliae
        K,  --  Calepinus Novus, modern Latin, by Guy Licoppe (Cal)
        L,  --  Lewis, C.S., Elementary Latin Dictionary 1891
        M,  --  Latham, Revised Medieval Word List, 1980 (Latham)
        N,  --  Lynn Nelson, Wordlist (Nel)
        O,  --  Oxford Latin Dictionary, 1982 (OLD)
        P,  --  Souter, A Glossary of Later Latin to 600 A.D.,
            --    Oxford 1949 (Souter)
        Q,  --  Other, cited or unspecified dictionaries
        R,  --  Plater + White, A Grammar of the Vulgate, Oxford 1926 (Plater)
        S,  --  Lewis and Short, A Latin Dictionary, 1879 (L+S)
        T,  --  Found in a translation  --  no dictionary reference
        U,  --
        V,  --  Vademecum in opus Saxonis - Franz Blatt (Saxo)
        W,  --  My personal guess, mostly obvious extrapolation (Whitaker or W)
        Y,  --  Temp special code
        Z   --  Sent by user -- no dictionary reference,
            --    Mostly John White of Blitz Latin

      --  Consulted but used only indirectly
      --  Liddell + Scott Greek-English Lexicon (Lid)
      --  Oxford English Dictionary 2002 (OED)

      --  Consulted but used only occasionally, seperately referenced
      --  D.A. Kidd, Collins Latin Gem Dictionary, 1957 (Col)
      --  Allen + Greenough, New Latin Grammar, 1888 (A+G)
      --  Harrington/Pucci/Elliott, Medieval Latin 2nd Ed 1997 (Harr)
      --  C.C./C.L. Scanlon Latin Grammar/Second Latin, TAN 1976 (SCANLON)
      --  W. M. Lindsay, Short Historical Latin Grammar, 1895 (Lindsay)
      --  Du Cange
      --  Oxford English Dictionary (OED)

      --  NOTE that the WORDS dictionary is not just a copy of source info,
      --  but the indicated SOURCE is a main reference/check point used to
      --  derive the entry*/

    enum class Source{
        UNKNOWN, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z   //I am begining to doubt the usefulness here 
    };


    inline constexpr EnumEntry<Source> source_table[] = {
        {"X", Source::UNKNOWN},
        {"A", Source::A},
        {"B", Source::B},
        {"C", Source::C},
        {"D", Source::D},
        {"E", Source::E},
        {"F", Source::F},
        {"G", Source::G},
        {"H", Source::H},
        {"I", Source::I},
        {"J", Source::J},
        {"K", Source::K},
        {"L", Source::L},
        {"M", Source::M},
        {"N", Source::N},
        {"O", Source::O},
        {"P", Source::P},
        {"Q", Source::Q},
        {"R", Source::R},
        {"S", Source::S},
        {"T", Source::T},
        {"U", Source::U},
        {"V", Source::V},
        {"W", Source::W},
        {"X", Source::X},
        {"Y", Source::Y},
        {"Z", Source::Z} //Definitely regretting this now
    };

    inline constexpr std::size_t source_table_size = sizeof(source_table) / sizeof(source_table[0]);
















    // No clue yet
    enum class Number{
        UNKNOWN, SINGULAR, PLURAL
    };

    inline constexpr EnumEntry<Number> number_table[] = {
        {"X", Number::UNKNOWN},
        {"S", Number::SINGULAR},
        {"P", Number::PLURAL},
    };

    inline constexpr std::size_t number_table_size = sizeof(number_table) / sizeof(number_table[0]);


    enum class Tense{
        UNKNOWN, PRESENT, IMPERFECT, FUTURE, PERFECT, PLUPERFECT, FUTPERF
    };

    inline constexpr EnumEntry<Tense> tense_table[] = {
        {"X",    Tense::UNKNOWN},
        {"PRES", Tense::PRESENT},
        {"IMPF", Tense::IMPERFECT},
        {"FUT",  Tense::FUTURE},
        {"PERF", Tense::PERFECT},
        {"PLUP", Tense::PLUPERFECT},
        {"FUTP", Tense::FUTPERF},
    };

    inline constexpr std::size_t tense_table_size = sizeof(tense_table) / sizeof(tense_table[0]);


    enum class Voice{
        UNKNOWN, ACTIVE, PASSIVE
    };

    inline constexpr EnumEntry<Voice> voice_table[] = {
        {"X",       Voice::UNKNOWN},
        {"ACTIVE",  Voice::ACTIVE},
        {"PASSIVE", Voice::PASSIVE},
    };

    inline constexpr std::size_t voice_table_size = sizeof(voice_table) / sizeof(voice_table[0]);


    enum class Mood{
        UNKNOWN, INDICATIVE, SUBJUNCTIVE, IMPERATIVE, INFINITIVE, PARTICIPLE
    };

    inline constexpr EnumEntry<Mood> mood_table[] = {
        {"X",   Mood::UNKNOWN},
        {"IND", Mood::INDICATIVE},
        {"SUB", Mood::SUBJUNCTIVE},
        {"IMP", Mood::IMPERATIVE},
        {"INF", Mood::INFINITIVE},
        {"PPL", Mood::PARTICIPLE},
    };

    inline constexpr std::size_t mood_table_size = sizeof(mood_table) / sizeof(mood_table[0]);


    template <typename E>
    constexpr std::optional<E> lookup(std::string_view s, const EnumEntry<E>* table, std::size_t n) {
        for (std::size_t i = 0; i < n; ++i) {
            if (table[i].name == s) return table[i].value;
        }
        return std::nullopt;
    }

    //Make a reverse lookup? not needed for now


    template <typename E> struct TableFor;
    
    template <> struct TableFor<PartOfSpeech> {
        static constexpr const EnumEntry<PartOfSpeech>* table() { return pos_table; }
        static constexpr std::size_t size() { return pos_table_size; }
    };

    template <> struct TableFor<Gender> {
        static constexpr const EnumEntry<Gender>* table() { return gender_table; }
        static constexpr std::size_t size() { return gender_table_size; }
    };

    template <> struct TableFor<NounKind> {
        static constexpr const EnumEntry<NounKind>* table() { return noun_kind_table; }
        static constexpr std::size_t size() { return noun_kind_table_size; }
    };

    template <> struct TableFor<VerbKind> {
        static constexpr const EnumEntry<VerbKind>* table() { return verb_kind_table; }
        static constexpr std::size_t size() { return verb_kind_table_size; }
    };

    template <> struct TableFor<Case> {
        static constexpr const EnumEntry<Case>* table() { return case_table; }
        static constexpr std::size_t size() { return case_table_size; }
    };

    template <> struct TableFor<Comparison> {
        static constexpr const EnumEntry<Comparison>* table() { return comparison_table; }
        static constexpr std::size_t size() { return comparison_table_size; }
    };

    template <> struct TableFor<PronounKind> {
        static constexpr const EnumEntry<PronounKind>* table() { return pronoun_kind_table; }
        static constexpr std::size_t size() { return pronoun_kind_table_size; }
    };

    template <> struct TableFor<Number> {
        static constexpr const EnumEntry<Number>* table() { return number_table; }
        static constexpr std::size_t size() { return number_table_size; }
    };

    template <> struct TableFor<NumeralSort> {
        static constexpr const EnumEntry<NumeralSort>* table() { return numeral_sort_table; }
        static constexpr std::size_t size() { return numeral_sort_table_size; }
    };

    template <> struct TableFor<Tense> {
        static constexpr const EnumEntry<Tense>* table() { return tense_table; }
        static constexpr std::size_t size() { return tense_table_size; }
    };

    template <> struct TableFor<Voice> {
        static constexpr const EnumEntry<Voice>* table() { return voice_table; }
        static constexpr std::size_t size() { return voice_table_size; }
    };

    template <> struct TableFor<Mood> {
        static constexpr const EnumEntry<Mood>* table() { return mood_table; }
        static constexpr std::size_t size() { return mood_table_size; }
    };

    template <> struct TableFor<Age> {
        static constexpr const EnumEntry<Age>* table() { return age_table; }
        static constexpr std::size_t size() { return age_table_size; }
    };

    template <> struct TableFor<Frequency> {
        static constexpr const EnumEntry<Frequency>* table() { return freq_table; }
        static constexpr std::size_t size() { return freq_table_size; }
    };

    template <> struct TableFor<Geography> {
        static constexpr const EnumEntry<Geography>* table() { return geo_table; }
        static constexpr std::size_t size() { return geo_table_size; }
    };

    template <> struct TableFor<Area>{
        static constexpr const EnumEntry<Area>* table() { return area_table; }
        static constexpr std::size_t size() { return area_table_size; }
    };

    template <> struct TableFor<Source>{
        static constexpr const EnumEntry<Source>* table() { return source_table; }
        static constexpr std::size_t size() { return source_table_size; }
    };





    template <typename E>
    constexpr E parse_enum(std::string_view s) {
        return lookup<E>(s, TableFor<E>::table(), TableFor<E>::size()).value_or(E::UNKNOWN);
    }

    template <typename E>
    constexpr std::string_view enum_name(E value) {
        const EnumEntry<E>* table = TableFor<E>::table();
        std::size_t n = TableFor<E>::size();
        for (std::size_t i = 0; i < n; ++i) {
            if (table[i].value == value) return table[i].name;
        }
        return "X";
    }


}