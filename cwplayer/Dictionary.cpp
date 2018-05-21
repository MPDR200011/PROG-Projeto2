#include "Dictionary.h"
#include "wordUtils.h"

void line_Separate(string line, string &word, vector<string> &synonyms) {
    //funcao para separar todas as palavras e metelas onde devidamente pertencem
    unsigned int index_start = 0;
    for (unsigned i = 0; i < line.length(); i++) {
        if (line[i] == ':') {
            //condicao para separar a palavra principal
            word = line.substr(index_start, i - index_start);
            index_start = i + 2;
        }
        else if (line[i] == ',') {
            //condicao para separar sinonimos
            synonyms.push_back(line.substr(index_start, i - index_start));
            index_start = i + 2;
        }
        else if (i == line.length() - 1) {
            synonyms.push_back(line.substr(index_start, i - index_start));
        }
    }
}

Dictionary::Dictionary(ifstream &dict_file) {
    string line;
    while (getline(dict_file, line)) {
        string headWord;
        vector<string> synonyms;

        headWord = pw::makeUpper(line.substr(0, line.find_first_of(':')));

        synonyms = pw::splitLine(line.substr(line.find_first_of(':')+1), ',');
        for (string &word: synonyms){
            word = pw::makeUpper(word);
        }

        dict_map.insert(pair<string, vector<string>>(headWord, synonyms));
    }
}

vector<string> Dictionary::getHeadWords() {
    vector<string> headWordList;
    for (auto word : dict_map) {
        string head;
        head = word.first;
        headWordList.push_back(head);
    }
    return headWordList;
}

vector<string> Dictionary::getSynonyms(string mainWord) {
    vector<string> synonyms = dict_map.at(mainWord);
    return synonyms;
}