#include <whitaker/enums.hpp>
#include <whitaker/types.hpp>
#include <whitaker/utils.hpp>
#include <fstream>
#include <vector>
#include <iostream>


namespace words{

    void loadAddons(std::string &fileName){
        std::ifstream file(fileName);

        if (!file.is_open()){
            std::cerr << "ERROR: FILE COULD NOT BE OPENED" << std::endl;
            return;
        }

        std::string line;
        std::string line2;
        std::string line3;
        InflEntry infl;

        /* 
            Tackons  : Tackon_Array (1 .. 20);
            Packons  : Tackon_Array (1 .. 25);
            Tickons  : Prefix_Array (1 .. 10);
            Prefixes : Prefix_Array (1 .. 130);
            Suffixes : Suffix_Array (1 .. 185);
            Means    : Means_Array (1 .. 370);

        */

        while (std::getline(file, line)){
            if (line.empty() || (line[0] == '-' && line[1] == '-') || line[0] == ' ' || line[0] == '\r') 
                continue;

            line = trim(trim_trailing_comm(line));

            std::getline(file, line2);
            line2 = trim(trim_trailing_comm(line2));

            std::getline(file, line3);
            line3 = trim(trim_trailing_comm(line3));


            auto line_tokens = tokenize_sv(line, SIZE_MAX);

            // std::cout << line << std::endl;
            // std::cout << line2 << std::endl;
            // std::cout << line3 << std::endl;




        }

        file.close();

        return;

    }


}