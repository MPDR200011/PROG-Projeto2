#include <iostream>
#include <string>
#include <algorithm>
#include "cwplayer.h"
#include "Board.h"
#include "wordUtils.h"
#include "Player.h"
#include <fstream>

using namespace std;


int main() {
    cout << "_________                               __      __                .___      " << endl;
    cout << "\\_   ___ \\_______  ____  ______ ______ /  \\    /  \\___________  __| _/______" << endl;
    cout << "/    \\  \\/\\_  __ \\/  _ \\/  ___//  ___/ \\   \\/\\/   /  _ \\_  __ \\/ __ |/  ___/" << endl;
    cout << "\\     \\____|  | \\(  <_> )___ \\ \\___ \\   \\        (  <_> )  | \\/ /_/ |\\___ \\ " << endl;
    cout << " \\______  /|__|   \\____/____  >____  >   \\__/\\  / \\____/|__|  \\____ /____  >" << endl;
    cout << "        \\/                  \\/     \\/         \\/                   \\/    \\/ " << endl;
    cout << "                  __________.__                                             " << endl;
    cout << "                  \\______   \\  | _____  ___.__. ___________                 " << endl;
    cout << "                   |     ___/  | \\__  \\<   |  |/ __ \\_  __ \\                " << endl;
    cout << "                   |    |   |  |__/ __ \\\\___  \\  ___/|  | \\/                " << endl;
    cout << "                   |____|   |____(____  / ____|\\___  >__|                   " << endl;
    cout << "                                      \\/\\/         \\/                       " << endl;
    cout << endl;



    cout << "==============================================================================" << endl;
    cout << endl << endl;

    //Instrucoes acerca do construtor de tabelas
    cout << "INSTRUCTIONS: " << endl;
    cout << "Position ( LCD / write \"check\" to stop)" << endl;
    cout << "   LCD stands for Line Column and Direction (Horizontal or Vertical, ex: AaH)" << endl;
    cout << endl <<
         "After inputting the position there are a few options you can take:" << endl <<
         "   - Write the word you want to put in the table." << endl <<
         "   - Write \"?\" to get another synonym of the selected word." << endl <<
         "   - Write \"-\" to delete the word in said position." << endl;

    cout << "------------------------------------------------------------------------------" << endl << endl;

    cout << "Puzzle File Name? ";

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


    cwplayer player(saveFile, fileName);
}