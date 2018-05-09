#ifndef PROG_PROJETO_2_BOARD_H
#define PROG_PROJETO_2_BOARD_H

#include <ostream>
#include <map>
#include <vector>
#include <string>

#ifdef __linux__
//Linux
#include "coloredTextLinux.h"
#else
//windows
#include "coloredTextWindows.h"
#endif

enum Orientation {HORIZONTAL, VERTICAL};

struct BoardWord {
    size_t x;
    size_t y;
    std::string word;
    Orientation orientation;
};

class Board {

public:
    Board() = default;
    Board(size_t nLine, size_t nCol);
    void setSize(size_t nLines, size_t nCols);
    int addWord(std::string word, size_t x, size_t y, char orientation);
    void deleteWord(size_t x, size_t y, char orientation);

    friend std::ostream& operator<<(std::ostream &out, Board &board);

private:
    void reconstructWord(BoardWord word);
    void checkIntegrity();

    size_t nCol;
    size_t nLines;

    std::vector<BoardWord> wordVector;
    std::vector<std::vector<char>> matrix;

public:
    size_t getNCol() const;

    void setNCol(size_t nCol);

    size_t getNLines() const;

    void setNLines(size_t nLines);

    const std::vector<BoardWord> &getWordVector() const;

    void setWordVector(const std::vector<BoardWord> &wordVector);

    const std::vector<std::vector<char>> &getMatrix() const;

    void setMatrix(const std::vector<std::vector<char>> &matrix);

};


#endif //PROG_PROJETO_2_BOARD_H
