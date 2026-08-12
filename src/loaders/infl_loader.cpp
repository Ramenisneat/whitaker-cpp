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

        entry.pos = parse_enum<PartOfSpeech>(tokens[0]);


        switch (entry.pos)
        {

        //Can collapse some of these cases
        case PartOfSpeech::NOUN:
            vtonum(tokens[1], entry.quality.noun.decl);
            vtonum(tokens[2], entry.quality.noun.var);
            entry.quality.noun.case_ = parse_enum<Case>(tokens[3]);
            entry.quality.noun.number = parse_enum<Number>(tokens[4]);
            entry.quality.noun.gender = parse_enum<Gender>(tokens[5]);
            break;

        case PartOfSpeech::PRONOUN:
            vtonum(tokens[1], entry.quality.pronoun.decl);
            vtonum(tokens[2], entry.quality.pronoun.var);
            entry.quality.pronoun.case_ = parse_enum<Case>(tokens[3]);
            entry.quality.pronoun.number = parse_enum<Number>(tokens[4]);
            entry.quality.pronoun.gender = parse_enum<Gender>(tokens[5]);
            break;
        
        case PartOfSpeech::PACKON:
            vtonum(tokens[1], entry.quality.propack.decl);
            vtonum(tokens[2], entry.quality.propack.var);
            entry.quality.propack.case_ = parse_enum<Case>(tokens[3]);
            entry.quality.propack.number = parse_enum<Number>(tokens[4]);
            entry.quality.propack.gender = parse_enum<Gender>(tokens[5]);
            break;

        case PartOfSpeech::ADJECTIVE:
            vtonum(tokens[1], entry.quality.adjective.decl);
            vtonum(tokens[2], entry.quality.adjective.var);
            entry.quality.adjective.case_ = parse_enum<Case>(tokens[3]);
            entry.quality.adjective.number = parse_enum<Number>(tokens[4]);
            entry.quality.adjective.gender = parse_enum<Gender>(tokens[5]);
            entry.quality.adjective.param = parse_enum<Comparison>(tokens[6]);
            break;
        
        case PartOfSpeech::NUMERAL:
            vtonum(tokens[1], entry.quality.numeral.decl);
            vtonum(tokens[2], entry.quality.numeral.var);
            entry.quality.numeral.case_ = parse_enum<Case>(tokens[3]);
            entry.quality.numeral.number = parse_enum<Number>(tokens[4]);
            entry.quality.numeral.sort = parse_enum<NumeralSort>(tokens[5]);
            break;
        
        case PartOfSpeech::ADVERB:
            entry.quality.adverb.param = parse_enum<Comparison>(tokens[1]);
        
        case PartOfSpeech::VERB:
            vtonum(tokens[1], entry.quality.verb.decl);
            vtonum(tokens[2], entry.quality.verb.var);
            entry.quality.verb.tvm.tense = parse_enum<Tense>(tokens[3]);
            entry.quality.verb.tvm.voice = parse_enum<Voice>(tokens[4]);
            entry.quality.verb.tvm.mood = parse_enum<Mood>(tokens[5]);
            vtonum(tokens[6], entry.quality.verb.person); //Can error check here?
            entry.quality.verb.number = parse_enum<Number>(tokens[7]);
            break;
        
        case PartOfSpeech::VPARTICIPLE:
        




        
        
        
        default:
            std::cerr << "NOT YET IMPLEMENTED POS: " << tokens[0] << std::endl;
            break;
        }



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


        size_t idx = 0;

        while (std::getline(file, line)){
            if (line.empty() || line[0] == '-' || line[0] == ' ' || line[0] == '\r') 
                continue;
            line = trim(trim_trailing_comm(line));

            // std::cout << line << std::endl;

            parseLine(line, infl);
            inflections.push_back(infl);
            ++idx;
            //Theres a case where if the dictionary kind is general it constructs and ESSE? See lines 282 https://github.com/mk270/whitakers-words/blob/master/src/commands/makedict_main.adb

        }

        file.close();

        return;

    }


}