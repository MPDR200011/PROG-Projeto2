#pragma once

#include <iostream>
#include <string>
#include <vector>
#ifdef __linux__
#include <unistd.h>
#define GetCurrentDir getcwd
#else
#include <direct.h>
#define GetCurrentDir _getcwd
#endif

//playwords namespace
namespace pw {

	void readString(std::string &var);
	bool readStringEOF(std::string &var);

	template <class T>
	void takeInput(T &var) {
		//Funcao generica para receber input validado  
		//para qualquer tipo de variavel, exceto strings.
		//Para strings recomenda-se usar readString()
		bool validInput = false;
		do {
			validInput = false;
			std::cin >> var;
			if (std::cin.fail()) {
				validInput = false;
				std::cout << "Invalid input, try again." << std::endl;
				std::cin.clear();
				std::cin.ignore(10000, '\n');
			} else {
				validInput = true;
				std::cin.ignore(1000, '\n');
			}
		} while (!validInput);
	}

	template <class T>
	bool takeInputEOF(T &var) {
		//Faz o mesmo que takeInput mas
		//retorna true se for laventada 
		//a flag EOF
		bool validInput = false;
		do {
			validInput = false;
			std::cin >> var;
			if (std::cin.fail()) {
				if (std::cin.eof()) {
					std::cin.clear();
					return true;
				}
				validInput = false;
				std::cout << "Invalid input, try again." << std::endl;
				std::cin.clear();
				std::cin.ignore(10000, '\n');
			} else {
				validInput = true;
				std::cin.ignore(1000, '\n');
			}
		} while (!validInput);

		return false;
	}

    std::vector<std::string> splitLine(std::string line, const char splitter);

	bool isWordPartOfSet(std::string word, std::vector<char> set);

	bool wildcardMatch(const char *str, const char *strWild);

	bool isWordMember(std::string word, std::vector<std::string> list);

	bool isCharMember(char ch, std::string word);

	std::string trim(std::string s);

	std::string makeUpper(std::string s);

	std::string scramble(std::string word);

	std::string getWorkingDirectory();

	void endGame();

}