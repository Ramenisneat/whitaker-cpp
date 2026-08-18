#include <whitaker/loaders.hpp>
#include <whitaker/types.hpp>
#include <whitaker/enums.hpp>
#include <whitaker/engine.hpp>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using namespace words;

int main(){

    vector<DictEntry> dictionary = {};
    vector<StemRef> stemList = {};
    vector<InflEntry> inflections = {};
    string dictfileName = "data/DICTLINE.GEN";
    string inflfileName = "data/INFLECTS.LAT";


    loadDictionary(dictfileName, dictionary, stemList);

    std::sort(stemList.begin(), stemList.end(), [](const StemRef &a, const StemRef &b){
        return a.stem < b.stem;

    });

    //TODO: Bucket these by length probably. Good for now. 
    loadInflections(inflfileName, inflections);

    std::cout << "Loaded " << dictionary.size() << " entries" << endl;
    std::cout << "Built " << stemList.size() << " stem refs" << endl;
    std::cout << "Loaded " << inflections.size() << " inflection refs" << endl;

    // printInflections(cout, inflections);
    std::vector<Candidate> candidates = parse_latin(dictionary, inflections, stemList, "femina");
    printCandidates(cout, candidates);

    // std::string input;
    // std::cout << "whitakers words test:" << std::endl;

    // while (true){
    //     std::cout << "> ";

    //     if (!std::getline(std::cin, input)) {
    //         break; 
    //     }
    //     //should normalize
    //     std::vector<Candidate> candidates = parse_latin(dictionary, inflections, stemList, input);

    //     printCandidates(cout, candidates);
    // }

    // printDictionary(cout, dictionary);
    // printStemList(cout, stemList);


    //parse steps (1 word)
    //Do QVAE KLUDGE
    // 

    return 0;
}
