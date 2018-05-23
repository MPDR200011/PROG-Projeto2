#include "Player.h"

using namespace std;

Player::Player() {
	cout << "Player Name ? ";
	getline(cin, name);
	cout << '\n';
	numbHints = 0;
	startTime = 0;
	timePlayed = 0;
}

string Player::getName() {
	return name;
}

void Player::updateFileName(string fileName) {
	puzzleFileName = fileName.substr(0, fileName.length() - 4) + "_s.txt";
}

void Player::setStartTime() {
	startTime = (unsigned)time(NULL);
}

void Player::updateTime() {
	timePlayed = (unsigned)time(NULL) - startTime;
}

void Player::incHints() {
	numbHints += 1;
}

void Player::statsPlayer() {
	updateTime();
	ostringstream outputSentence;
	if (numbHints == 1){
		outputSentence << name << " played for " << timePlayed << " seconds and used 1 extra hint." << "\n";
	}
	else{
		outputSentence << name << " played for " << timePlayed << " seconds and used " << numbHints << " extra hints." << "\n";
	}
	string outputString = outputSentence.str();

	ofstream outputFile;
	outputFile.open(puzzleFileName, ios_base::app);
	outputFile << outputString;
	outputFile.close();
	cout << "Stats saved to " << puzzleFileName << ", thank you for playing!\n\n";
}