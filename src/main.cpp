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

    cout << "Loaded " << dictionary.size() << " entries" << endl;
    cout << "Built " << stemList.size() << " stem refs" << endl;
    cout << "Loaded " << inflections.size() << " inflection refs" << endl;



    //should normalize
    parse_latin(dictionary, inflections, stemList, "amos");


    // printDictionary(cout, dictionary);
    // printStemList(cout, stemList);


    //parse steps (1 word)
    //Do QVAE KLUDGE
    // 

    return 0;
}
