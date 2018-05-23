#ifndef PROG_PROJETO_2_CWPLAYER_H
#define PROG_PROJETO_2_CWPLAYER_H

#endif //PROG_PROJETO_2_CWPLAYER_H

#include <iostream>
#include <fstream>
#include <set>
#include <algorithm>
#include <ctime>
#include <dirent.h>
#include "Dictionary.h"
#include "Board.h"
#include "Player.h"

class cwplayer {
public:
    explicit cwplayer(std::ifstream &saveFile, const std::string &name);

    Player jogador;
private:
    void buildLoop();

    std::string takePosition(); //toma input da posição de uma palavra.
    bool validatePosition(std::string pos);
    size_t boardSizeInput(); //funcao para fazer input do tamanho das colunas/linhas

    void help(size_t x, size_t y, char orientation);

    void exitProcess();
    void saveProgress();
    std::string createSaveFileName();

    bool isTableLoadedFromSave;
    std::string saveFileName;
    std::string dictionaryName; //nome do ficheiro do dicionario
    std::vector<std::string> sinonimosUsados;
    Dictionary dict; //Dicionario de sinónimos
    Board board; //Mesa de jogo
};