#include <whitaker/enums.hpp>
#include <whitaker/types.hpp>
#include <whitaker/utils.hpp>
#include <fstream>
#include <vector>
#include <iostream>


namespace words{


    void parseLine(std::string_view line, InflEntry &entry){

        //Not fixed width like dictline bruh

        auto tokens = tokenize_sv(line, SIZE_MAX);

        // std::cout << "[";
        // for (auto i : tokens){
        //     std::cout << i << ","; 
        // }
        // std::cout << "]" << std::endl;
        // std::cout << tokens.size()<< std::endl;


        entry.pos = parse_enum<PartOfSpeech>(tokens[0]);

        size_t skip = 1;
        switch (entry.pos)
        {

        //Can collapse some of these cases
        case PartOfSpeech::NOUN:
            vtonum(tokens[1], entry.quality.noun.decl);
            vtonum(tokens[2], entry.quality.noun.var);
            entry.quality.noun.case_ = parse_enum<Case>(tokens[3]);
            entry.quality.noun.number = parse_enum<Number>(tokens[4]);
            entry.quality.noun.gender = parse_enum<Gender>(tokens[5]);
            skip += 5;
            break;

        case PartOfSpeech::PRONOUN:
            vtonum(tokens[1], entry.quality.pronoun.decl);
            vtonum(tokens[2], entry.quality.pronoun.var);
            entry.quality.pronoun.case_ = parse_enum<Case>(tokens[3]);
            entry.quality.pronoun.number = parse_enum<Number>(tokens[4]);
            entry.quality.pronoun.gender = parse_enum<Gender>(tokens[5]);
            skip += 5;
            break;
        
        case PartOfSpeech::PACKON:
            vtonum(tokens[1], entry.quality.propack.decl);
            vtonum(tokens[2], entry.quality.propack.var);
            entry.quality.propack.case_ = parse_enum<Case>(tokens[3]);
            entry.quality.propack.number = parse_enum<Number>(tokens[4]);
            entry.quality.propack.gender = parse_enum<Gender>(tokens[5]);
            skip += 5;
            break;

        case PartOfSpeech::ADJECTIVE:
            vtonum(tokens[1], entry.quality.adjective.decl);
            vtonum(tokens[2], entry.quality.adjective.var);
            entry.quality.adjective.case_ = parse_enum<Case>(tokens[3]);
            entry.quality.adjective.number = parse_enum<Number>(tokens[4]);
            entry.quality.adjective.gender = parse_enum<Gender>(tokens[5]);
            entry.quality.adjective.param = parse_enum<Comparison>(tokens[6]);
            skip += 6;
            break;
        
        case PartOfSpeech::NUMERAL:
            vtonum(tokens[1], entry.quality.numeral.decl);
            vtonum(tokens[2], entry.quality.numeral.var);
            entry.quality.numeral.case_ = parse_enum<Case>(tokens[3]);
            entry.quality.numeral.number = parse_enum<Number>(tokens[4]);
            entry.quality.numeral.gender = parse_enum<Gender>(tokens[5]);
            entry.quality.numeral.sort = parse_enum<NumeralSort>(tokens[6]);
            skip += 6;
            break;
        
        case PartOfSpeech::ADVERB:
            entry.quality.adverb.param = parse_enum<Comparison>(tokens[1]);
            skip += 1;
            break;

        case PartOfSpeech::VERB:
            vtonum(tokens[1], entry.quality.verb.decl);
            vtonum(tokens[2], entry.quality.verb.var);
            entry.quality.verb.tvm.tense = parse_enum<Tense>(tokens[3]);
            entry.quality.verb.tvm.voice = parse_enum<Voice>(tokens[4]);
            entry.quality.verb.tvm.mood = parse_enum<Mood>(tokens[5]);
            vtonum(tokens[6], entry.quality.verb.person); //Can error check here?
            entry.quality.verb.number = parse_enum<Number>(tokens[7]);
            skip += 7;
            break;
        
        case PartOfSpeech::VPARTICIPLE:
            vtonum(tokens[1], entry.quality.vpar.decl);
            vtonum(tokens[2], entry.quality.vpar.var);            
            entry.quality.vpar.case_ = parse_enum<Case>(tokens[3]);
            entry.quality.vpar.number = parse_enum<Number>(tokens[4]);
            entry.quality.vpar.gender = parse_enum<Gender>(tokens[5]);
            entry.quality.vpar.tvm.tense = parse_enum<Tense>(tokens[6]);
            entry.quality.vpar.tvm.voice = parse_enum<Voice>(tokens[7]);
            entry.quality.vpar.tvm.mood = parse_enum<Mood>(tokens[8]);
            skip += 8;
            break;

        case PartOfSpeech::SUPINE:
            vtonum(tokens[1], entry.quality.supine.decl);
            vtonum(tokens[2], entry.quality.supine.var);
            entry.quality.supine.case_ = parse_enum<Case>(tokens[3]);
            entry.quality.supine.number = parse_enum<Number>(tokens[4]);
            entry.quality.supine.gender = parse_enum<Gender>(tokens[5]);
            skip += 5;
            break;
        
        case PartOfSpeech::PREPOSITION:
            entry.quality.preposition.case_ = parse_enum<Case>(tokens[1]);
            skip += 1;
            break;

        case PartOfSpeech::CONJUNCTION:
        case PartOfSpeech::INTERJECTION:
            break;

        
        default:
            std::cerr << "NOT YET IMPLEMENTED POS: " << tokens[0] << std::endl;
            break;
        }

        //stem key
        vtonum(tokens[skip++], entry.stemKey);

        //ending
        vtonum(tokens[skip++], entry.ending.ending_size);
        if (entry.ending.ending_size == 0)
            entry.ending.ending = "";
        else
            entry.ending.ending = tokens[skip++];

        //flags
        entry.age = parse_enum<Age>(tokens[skip++]);
        entry.freq = parse_enum<Frequency>(tokens[skip]);

        return;
    }



    void loadInflections(std::string &fileName, std::vector<InflEntry> &inflections){
        std::ifstream file(fileName);
        // std::vector<DictEntry> entries;

        if (!file.is_open()){
            std::cerr << "ERROR: FILE COULD NOT BE OPENED" << std::endl;
            return;
        }

        std::string line;
        InflEntry infl;



        while (std::getline(file, line)){
            if (line.empty() || line[0] == '-' || line[0] == ' ' || line[0] == '\r') 
                continue;
            line = trim(trim_trailing_comm(line));

            // std::cout << line << std::endl;

            parseLine(line, infl);
            // std::cout << infl << std::endl;
            inflections.push_back(infl);

        }

        file.close();

        return;

    }


    std::ostream& operator<<(std::ostream& os, const InflEntry& entry){
        os << "(" << enum_name(entry.pos) << ") ";

        switch (entry.pos)
        {
            case PartOfSpeech::NOUN:
                os << "decl=" << +entry.quality.noun.decl
                   << " var=" << +entry.quality.noun.var
                   << " case=" << enum_name(entry.quality.noun.case_)
                   << " number=" << enum_name(entry.quality.noun.number)
                   << " gender=" << enum_name(entry.quality.noun.gender);
                break;

            case PartOfSpeech::PRONOUN:
                os << "decl=" << +entry.quality.pronoun.decl
                   << " var=" << +entry.quality.pronoun.var
                   << " case=" << enum_name(entry.quality.pronoun.case_)
                   << " number=" << enum_name(entry.quality.pronoun.number)
                   << " gender=" << enum_name(entry.quality.pronoun.gender);
                break;

            case PartOfSpeech::PACKON:
                os << "decl=" << +entry.quality.propack.decl
                   << " var=" << +entry.quality.propack.var
                   << " case=" << enum_name(entry.quality.propack.case_)
                   << " number=" << enum_name(entry.quality.propack.number)
                   << " gender=" << enum_name(entry.quality.propack.gender);
                break;

            case PartOfSpeech::ADJECTIVE:
                os << "decl=" << +entry.quality.adjective.decl
                   << " var=" << +entry.quality.adjective.var
                   << " case=" << enum_name(entry.quality.adjective.case_)
                   << " number=" << enum_name(entry.quality.adjective.number)
                   << " gender=" << enum_name(entry.quality.adjective.gender)
                   << " comparison=" << enum_name(entry.quality.adjective.param);
                break;

            case PartOfSpeech::NUMERAL:
                os << "decl=" << +entry.quality.numeral.decl
                   << " var=" << +entry.quality.numeral.var
                   << " case=" << enum_name(entry.quality.numeral.case_)
                   << " number=" << enum_name(entry.quality.numeral.number)
                   << " sort=" << enum_name(entry.quality.numeral.sort);
                break;

            case PartOfSpeech::ADVERB:
                os << "comparison=" << enum_name(entry.quality.adverb.param);
                break;

            case PartOfSpeech::VERB:
                os << "decl=" << +entry.quality.verb.decl
                   << " var=" << +entry.quality.verb.var
                   << " tense=" << enum_name(entry.quality.verb.tvm.tense)
                   << " voice=" << enum_name(entry.quality.verb.tvm.voice)
                   << " mood=" << enum_name(entry.quality.verb.tvm.mood)
                   << " person=" << +entry.quality.verb.person
                   << " number=" << enum_name(entry.quality.verb.number);
                break;

            case PartOfSpeech::VPARTICIPLE:
                os << "decl=" << +entry.quality.vpar.decl
                   << " var=" << +entry.quality.vpar.var
                   << " case=" << enum_name(entry.quality.vpar.case_)
                   << " number=" << enum_name(entry.quality.vpar.number)
                   << " gender=" << enum_name(entry.quality.vpar.gender)
                   << " tense=" << enum_name(entry.quality.vpar.tvm.tense)
                   << " voice=" << enum_name(entry.quality.vpar.tvm.voice)
                   << " mood=" << enum_name(entry.quality.vpar.tvm.mood);
                break;

            case PartOfSpeech::SUPINE:
                os << "decl=" << +entry.quality.supine.decl
                   << " var=" << +entry.quality.supine.var
                   << " case=" << enum_name(entry.quality.supine.case_)
                   << " number=" << enum_name(entry.quality.supine.number)
                   << " gender=" << enum_name(entry.quality.supine.gender);
                break;

            case PartOfSpeech::PREPOSITION:
                os << "case=" << enum_name(entry.quality.preposition.case_);
                break;

            default:
                break;
        }

        os << " stemKey=" << entry.stemKey
           << " ending=\"" << entry.ending.ending << "\""
           << " age=" << enum_name(entry.age)
           << " freq=" << enum_name(entry.freq);

        return os;
    }


}