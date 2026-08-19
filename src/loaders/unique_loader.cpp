#include <whitaker/enums.hpp>
#include <whitaker/types.hpp>
#include <whitaker/utils.hpp>
#include <fstream>
#include <vector>
#include <iostream>
#include <cctype>



namespace words{

    void loadUniques(std::string &fileName, std::vector<UniqueEntry> &uniques){
        std::ifstream file(fileName);
        // std::vector<DictEntry> entries;

        if (!file.is_open()){
            std::cerr << "ERROR: FILE COULD NOT BE OPENED" << std::endl;
            return;
        }

        std::string line;
        UniqueEntry unq;



        while (std::getline(file, line)){
            if (line.empty() || line[0] == '-' || line[0] == ' ' || line[0] == '\r') 
                continue;


            line = trim(trim_trailing_comm(line));
            unq.stem = line;

            if (!std::getline(file, line))
                std::cerr << "ERROR: LOADING A GRAMMAR LINE FROM UNIQUES" << std::endl;
            
            auto tokens = tokenize_sv(line, SIZE_MAX);
            unq.pos = parse_enum<PartOfSpeech>(tokens[0]);

            size_t skip = 1;
            std::string_view temp;
            
            switch (unq.pos)
            {
                case PartOfSpeech::NOUN:
                    vtonum(tokens[1], unq.quality.noun.decl);
                    vtonum(tokens[2], unq.quality.noun.var);
                    unq.quality.noun.case_ = parse_enum<Case>(tokens[3]);
                    unq.quality.noun.number = parse_enum<Number>(tokens[4]);
                    unq.quality.noun.gender = parse_enum<Gender>(tokens[5]);
                    //Weird formatting error in raw text
                    {
                        std::string bruh (1, static_cast<char>(std::toupper(static_cast<unsigned char>(tokens[6].front())))); //this sucks, I could switch instead.
                        temp = bruh;
                        unq.kind.noun = parse_enum<NounKind>(temp);
                    }
                    skip += 6;
                    break;
                
                case PartOfSpeech::VERB:
                    vtonum(tokens[1], unq.quality.verb.decl);
                    vtonum(tokens[2], unq.quality.verb.var);
                    unq.quality.verb.tvm.tense = parse_enum<Tense>(tokens[3]);
                    unq.quality.verb.tvm.voice = parse_enum<Voice>(tokens[4]);
                    unq.quality.verb.tvm.mood = parse_enum<Mood>(tokens[5]);
                    vtonum(tokens[6], unq.quality.verb.person); //Can error check here?
                    unq.quality.verb.number = parse_enum<Number>(tokens[7]);
                    unq.kind.verb = parse_enum<VerbKind>(tokens[8]);
                    skip += 8;
                    break;
                
                case PartOfSpeech::PRONOUN:
                    vtonum(tokens[1], unq.quality.pronoun.decl);
                    vtonum(tokens[2], unq.quality.pronoun.var);
                    unq.quality.pronoun.case_ = parse_enum<Case>(tokens[3]);
                    unq.quality.pronoun.number = parse_enum<Number>(tokens[4]);
                    unq.quality.pronoun.gender = parse_enum<Gender>(tokens[5]);
                    unq.kind.pronoun = parse_enum<PronounKind>(tokens[6]);
                    skip += 6;
                    break;
                
                case PartOfSpeech::ADJECTIVE:
                    vtonum(tokens[1], unq.quality.adjective.decl);
                    vtonum(tokens[2], unq.quality.adjective.var);
                    unq.quality.adjective.case_ = parse_enum<Case>(tokens[3]);
                    unq.quality.adjective.number = parse_enum<Number>(tokens[4]);
                    unq.quality.adjective.gender = parse_enum<Gender>(tokens[5]);
                    unq.quality.adjective.param = parse_enum<Comparison>(tokens[6]);
                    skip += 6;
                    break;
            
            }


            unq.flags.age = parse_enum<Age>(tokens[skip++]);
            unq.flags.area = parse_enum<Area>(tokens[skip++]);
            unq.flags.geo = parse_enum<Geography>(tokens[skip++]);
            unq.flags.freq = parse_enum<Frequency>(tokens[skip++]);
            unq.flags.source = parse_enum<Source>(tokens[skip++]);
            // std::cout << line << std::endl;

            
            if (!std::getline(file, line))
                std::cerr << "ERROR: LOADING A MEANING LINE FROM UNIQUES" << std::endl;
            line = trim(trim_trailing_comm(line));
            unq.meaning = line;

            uniques.push_back(unq);

        }

        file.close();

        return;
    }

    std::ostream& operator<<(std::ostream& os, const UniqueEntry& entry){
        os << "(" << enum_name(entry.pos) << ") ";
        switch (entry.pos)
        {
            case PartOfSpeech::NOUN:
                os << "decl=" << +entry.quality.noun.decl
                   << " var=" << +entry.quality.noun.var
                   << " case=" << enum_name(entry.quality.noun.case_)
                   << " number=" << enum_name(entry.quality.noun.number)
                   << " gender=" << enum_name(entry.quality.noun.gender)
                   << " kind=" << enum_name(entry.kind.noun);

                break;

            case PartOfSpeech::PRONOUN:
                os << "decl=" << +entry.quality.pronoun.decl
                   << " var=" << +entry.quality.pronoun.var
                   << " case=" << enum_name(entry.quality.pronoun.case_)
                   << " number=" << enum_name(entry.quality.pronoun.number)
                   << " gender=" << enum_name(entry.quality.pronoun.gender)
                   << " kind=" << enum_name(entry.kind.pronoun);


                break;
            
            case PartOfSpeech::ADJECTIVE:
                os << "decl=" << +entry.quality.adjective.decl
                   << " var=" << +entry.quality.adjective.var
                   << " case=" << enum_name(entry.quality.adjective.case_)
                   << " number=" << enum_name(entry.quality.adjective.number)
                   << " gender=" << enum_name(entry.quality.adjective.gender)
                   << " comparison=" << enum_name(entry.quality.adjective.param);
                break;

            case PartOfSpeech::VERB:
                os << "decl=" << +entry.quality.verb.decl
                   << " var=" << +entry.quality.verb.var
                   << " tense=" << enum_name(entry.quality.verb.tvm.tense)
                   << " voice=" << enum_name(entry.quality.verb.tvm.voice)
                   << " mood=" << enum_name(entry.quality.verb.tvm.mood)
                   << " person=" << +entry.quality.verb.person
                   << " number=" << enum_name(entry.quality.verb.number)
                   << " kind=" << enum_name(entry.kind.verb);

                break;
            
            default:
                break;
        }

        os << " age=" << enum_name(entry.flags.age)
            << " area=" << enum_name(entry.flags.area)
            << " geo=" << enum_name(entry.flags.geo)
            << " freq=" << enum_name(entry.flags.freq)
            << " source=" << enum_name(entry.flags.source);
        
        os << " meaning=" << entry.meaning;


        


        return os;
    }


    void printUniques(std::ostream& os, const std::vector<UniqueEntry>& uniques){
        for (size_t i = 0; i < uniques.size(); ++i){
            os << "[" << i << "] " << uniques[i] << "\n";
        }
    }


}