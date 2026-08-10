#include <enums.hpp>
#include <types.hpp>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>


namespace words{

    std::vector<DictEntry> loadDictionary(std::string fileName){
        
        std::ifstream file(fileName);
        std::vector<DictEntry> entries;

        if (!file.is_open()){
            std::cerr << "ERROR: FILE COULD NOT BE OPENED" << std::endl;
            return entries;
        }

        std::string line;


        while (std::getline(file, line)){
            std::cout << line << std::endl;
        }

        file.close();

        return entries;

    }

}
