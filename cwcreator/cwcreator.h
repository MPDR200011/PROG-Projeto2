#ifndef PROG_PROJETO_2_CWCREATOR_H
#define PROG_PROJETO_2_CWCREATOR_H

#include <iostream>
#include <set>
#include <algorithm>
#include <dirent.h>
#include "Dictionary.h"
#include "Board.h"

class cwcreator {

public:
    cwcreator();
    explicit cwcreator(std::ifstream &saveFile, const std::string &name);

private:
    void buildLoop();

    std::string takePosition(); //toma input da posição de uma palavra.
    bool validatePosition(std::string pos);
    std::string takeWord(); //input da word para por na tabela.
    size_t boardSizeInput(); //funcao para fazer input do tamanho das colunas/linhas

    void help(size_t x, size_t y, char orientation);

    void exitProcess();
    void saveProgress();
    std::string createSaveFileName();

    bool isTableLoadedFromSave;
    std::string saveFileName;
    std::string dictionaryName; //nome do ficheiro do dicionario
    Dictionary dict; //Dicionario de sinónimos
    Board board; //Mesa de jogo

};


#endif //PROG_PROJETO_2_CWCREATOR_H
