#include <iostream>
#include <whitaker/loaders.hpp>

using namespace std;

int main(){

    auto entries = words::loadDictionary("data/DICTLINE.GEN");

    cout << "Loaded " << entries.size() << " entries" << endl;

    return 0;
}
