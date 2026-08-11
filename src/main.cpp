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
    string fileName = "data/DICTLINE.GEN";

    dictionary = loadDictionary(fileName, dictionary, stemList);

    cout << "Loaded " << dictionary.size() << " entries" << endl;
    cout << "Built " << stemList.size() << " stem refs" << endl;

    printDictionary(cout, dictionary);
    printStemList(cout, stemList);

    return 0;
}
