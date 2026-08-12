#include <whitaker/loaders.hpp>
#include <whitaker/types.hpp>
#include <whitaker/enums.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace words;

int main(){

    vector<DictEntry> dictionary = {};
    vector<StemRef> stemList = {};
    vector<InflEntry> inflections = {};
    string dictfileName = "data/DICTLINE.GEN";
    string inflfileName = "data/INFLECTS.LAT";


    loadDictionary(dictfileName, dictionary, stemList);

    //TODO: gotta probably sort stems
    //TODO: Bucket these by length probably. Good for now. 
    loadInflections(inflfileName, inflections);

    cout << "Loaded " << dictionary.size() << " entries" << endl;
    cout << "Built " << stemList.size() << " stem refs" << endl;

    // printDictionary(cout, dictionary);
    // printStemList(cout, stemList);

    return 0;
}
