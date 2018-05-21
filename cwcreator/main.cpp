#include <iostream>
#include <string>
#include <algorithm>
#include "cwcreator.h"
#include "Board.h"
#include "wordUtils.h"

using namespace std;

int main() {

    /*ifstream omg("sinwin.txt");
    Dictionary dict(omg);

    for (string word: dict.getHeadWords()) {
        cout << word << ": ";
        for (string w: dict.getSynonyms(word)){
            cout << w << " ";
        }
        cout << endl;
    }*/

    cout << "CROSS WORDS PUZZLE CREATOR" << endl;
    cout << "===============================================" << endl;
    cout << endl;

    //Instrucoes acerca do construtor de tabelas
    cout << "INSTRUCTIONS: " << endl;
    cout << "Position ( LCD / CTRL-Z = stop)" << endl;
    cout << "   LCD stand for Line Column and Direction (Horizontal or Vertical, ex: AaH)" << endl;

    cout << "-----------------------------------------------" << endl;

    cout << "OPTIONS:" << endl;
    cout << "1 - Create New Puzzle" << endl;
    cout << "2 - Resume Puzzle" << endl;
    cout << "0 - Exit" << endl;
    cout << endl;
    cout << "Option ? ";

    unsigned int option;
    bool validOption;
    do {
        pw::takeInput(option);
        if(option > 2){
            validOption = false;
            cout << "Invalid choice, try again." << endl;
        } else {
            validOption = true;
        }
    } while (!validOption);

    if (option == 1) {
        cwcreator creator;
    } else if (option == 2) {

        cout << "Save file ? ";

        ifstream saveFile;
        string fileName;
        bool validInput;
        do {
            pw::readString(fileName);
            saveFile.open(fileName);
            if (saveFile.is_open()) {
                validInput = true;
            } else {
                cout << "File not found, try again." << endl;
                validInput = false;
            }
        } while (!validInput);

        cwcreator creator(saveFile, fileName);

    }

    return 0;
}