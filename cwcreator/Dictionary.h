#ifndef PROG_PROJETO_2_DICTIONARY_H
#define PROG_PROJETO_2_DICTIONARY_H
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

class Dictionary {
public:
    Dictionary() = default;
    Dictionary(ifstream &dict_file);
    vector<string> getHeadWords();
    vector<string> getSynonyms(string mainWord);
private:
    map<string, vector<string>> dict_map;
};


#endif //PROG_PROJETO_2_DICTIONARY_H
