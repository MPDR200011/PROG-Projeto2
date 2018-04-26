#include <algorithm>
#include "wordUtils.h"

using namespace std;

void pw::readString(string &var) {
	//Funcao expecificamente para ler strings
	bool validInput;
	do {
		validInput = false;
		getline(cin, var);
		if (cin.fail()) {
			validInput = false;
			cout << "Invalid input, try again." << endl;
			cin.clear();
			cin.ignore(1000, '\n');
		} else {
			validInput = true;
		}
	} while (!validInput);
}

bool pw::isWordPartOfSet(string word, vector<char> set) {
	//Verifica se uma palavra e construida so com letras de um conjunto das mesmas
	//ATENCAO: retorna falso se a palavra letras iguais a mais, ex:
	//	conjunto : C O E R R
	//	palavra : CORRER (palavra usa um R a mais)
	for (char c : word) {
		auto iter = find(set.begin(), set.end(), c);
		if (iter != set.end()) {
			set.erase(iter);
		} else {
			return false;
		}
	}

	return true;
}

bool pw::wildcardMatch(const char *str, const char *strWild) {
	// We have a special case where string is empty ("") and the mask is "*".
	// We need to handle this too. So we can't test on !*str here.
	// The loop breaks when the match string is exhausted.
	while (*strWild) {
		// Single wildcard character
		if (*strWild == '?') {
			// Matches any character except empty string
			if (!*str)
				return false;
			// OK next
			++str;
			++strWild;
		} else if (*strWild == '*') {
			// Need to do some tricks.
			// 1. The wildcard * is ignored.
			// So just an empty string matches. This is done by recursion.
			// Because we eat one character from the match string,
			// the recursion will stop.
			if (wildcardMatch(str, strWild + 1))
				// we have a match and the * replaces no other character
				return true;
			// 2. Chance we eat the next character and try it again,
			// with a wildcard * match. This is done by recursion.
			// Because we eat one character from the string,
			// the recursion will stop.
			if (*str && wildcardMatch(str + 1, strWild))
				return true;
			// Nothing worked with this wildcard.
			return false;
		} else {
			// Standard compare of 2 chars. Note that *str might be 0 here,
			// but then we never get a match on *strWild
			// that has always a value while inside this loop.
			if (toupper(*str++) != toupper(*strWild++))
				return false;
		}
	}
	// Have a match? Only if both are at the end...
	return !*str && !*strWild;
}

bool pw::isWordMember(string word, vector<string> list) {

	for (const string &s: list) {
		if (word == s) {
			return true;
		}
	}
	return false;
}

bool pw::isCharMember(char ch, string word) {
	for (char c : word) {
		if (ch == c) {
			return true;
		}
	}
	return false;
}

string pw::trim(string s) {
	//remove o espaco branco no inicio e no fim da string
	const auto sBegin = s.find_first_not_of(" \t\n\v\f\r");

	if (sBegin == string::npos)
		return "";//caso esteja vazia

	const auto sEnd = s.find_last_not_of(" \t\n\v\f\r");
	const auto range = sEnd - sBegin;

	return s.substr(sBegin, range + 1);
}

string pw::makeUpper(string s) {
	string temp;
	for (char &c : s) {
		temp.push_back((char) toupper(c));
	}

	return temp;
}

string pw::scramble(string word) {
	string scramb = word;
	for (unsigned i = 0; i < scramb.length(); i++) {
		unsigned j = rand() % scramb.length();
		swap(scramb.at(i), scramb.at(j));
	}
	return scramb;
}

void pw::endGame() {
	cout << endl << "Press Enter to finnish." << endl;
	getchar();
}

