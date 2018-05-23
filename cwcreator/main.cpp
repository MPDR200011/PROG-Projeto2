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

    cout << "_________                               __      __                .___      " << endl;
    cout << "\\_   ___ \\_______  ____  ______ ______ /  \\    /  \\___________  __| _/______" << endl;
    cout << "/    \\  \\/\\_  __ \\/  _ \\/  ___//  ___/ \\   \\/\\/   /  _ \\_  __ \\/ __ |/  ___/" << endl;
    cout << "\\     \\____|  | \\(  <_> )___ \\ \\___ \\   \\        (  <_> )  | \\/ /_/ |\\___ \\ " << endl;
    cout << " \\______  /|__|   \\____/____  >____  >   \\__/\\  / \\____/|__|  \\____ /____  >" << endl;
    cout << "        \\/                  \\/     \\/         \\/                   \\/    \\/ " << endl;
    cout << "            _________                        __                             " << endl;
    cout << "            \\_   ___ \\_______   ____ _____ _/  |_  ___________              " << endl;
    cout << "            /    \\  \\/\\_  __ \\_/ __ \\\\__  \\\\   __\\/  _ \\_  __ \\             " << endl;
    cout << "            \\     \\____|  | \\/\\  ___/ / __ \\|  | (  <_> )  | \\/             " << endl;
    cout << "             \\______  /|__|    \\___  >____  /__|  \\____/|__|                " << endl;
    cout << "                    \\/             \\/     \\/                                " << endl;
    cout << endl;



    cout << "==============================================================================" << endl;
    cout << endl;

    //Instrucoes acerca do construtor de tabelas
    cout << "INSTRUCTIONS: " << endl;
    cout << "Position ( LCD / write \"exit\" to stop)" << endl;
    cout << "   LCD stands for Line Column and Direction (Horizontal or Vertical, ex: AaH)" << endl;
    cout << endl <<
            "After inputting the position there are a few options you can take:" << endl <<
            "   - Write the word you want to put in the table." << endl <<
            "   - Write \"?\" to get a list of words you can input in said position." << endl <<
            "   - Write \"-\" to delete the word in said position (if there is no word it won't do anything)." << endl;

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