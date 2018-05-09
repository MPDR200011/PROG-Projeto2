#include <iomanip>
#include <iostream>
#include "Board.h"


using namespace std;

Board::Board(size_t nLine, size_t nCol) {
    this->nLines = nLine;
    this->nCol = nCol;
    matrix = vector<vector<char>>(nLine, vector<char>(nCol, '.'));
}

void Board::setSize(size_t nLines, size_t nCols) {
    this->nLines = nLines;
    this->nCol = nCols;
    matrix = vector<vector<char>>(nLines, vector<char>(nCols, '.'));
}

int Board::addWord(std::string word, size_t x, size_t y, char orientation) {
    //retorna 1 se a palavra não couver dentro da tabela
    //retorna 2 se a palavra ja estiver na tabela
    //retorna 3 se a palavra dada se sobrepor a outra, alterando o seu conteudo

    //funcao confia no facto de orientation ser V ou H de partida, ou seja, a validacao
    //do input sera feita por quem chama a funcao

    //o codigo usado para inserir os asteriscos antes e depois das palavras estao envolvidos
    //em blocos try/catch pois as extremidades das palavras podem estar nas extremidades da tabela

    for (BoardWord toCompare: wordVector){
        if (toCompare.word == word){
            return 2;
        }
    }

    BoardWord wordStruct = {
            x,
            y,
            word,
            orientation == 'V' ? VERTICAL : HORIZONTAL
    };

    wordVector.push_back(wordStruct);

    if (orientation == 'V') {
        //verificacao para ver se a palavra cabe
        if (y + word.length() > nLines) {
            return 1;
        }

        //asterisco antes da palavra
        try {
            char matrixChar = matrix.at(y-1).at(x);
            if (matrixChar == '.' || matrixChar == '#') {
                matrix.at(y-1).at(x) = '#';
            } else {
                deleteWord(x,y,orientation);
                return 3;
            }
        } catch (out_of_range &e) {}

        //preencher coluna a partir da posicao dada
        for (size_t i = 0; i < word.length(); ++i) {
            char matrixChar = matrix.at(y+i).at(x);
            char wordChar =word.at(i);
            if (matrixChar == '.'){
                matrix.at(y+i).at(x) = wordChar;
            } else {
                if (matrixChar != wordChar) {
                    deleteWord(x,y,orientation);
                    return 3;
                }
            }
        }

        //asterisco depois da palavra
        try {
            char matrixChar = matrix.at(y+word.length()).at(x);
            if (matrixChar == '.' || matrixChar == '#'){
                matrix.at(y+word.length()).at(x) = '#';
            } else {
                deleteWord(x,y,orientation);
                return 3;
            }
        } catch (out_of_range &e) {}


    } else {
        //verificacao para ver se a palavra cabe
        if (x + word.length() > nCol) {
            return 1;
        }

        //asterisco antes da palavra
        try {
            char matrixChar = matrix.at(y).at(x-1);
            if (matrixChar == '.' || matrixChar == '#') {
                matrix.at(y).at(x-1) = '#';
            } else {
                deleteWord(x,y,orientation);
                return 3;
            }
        } catch (out_of_range &e) {}

        //preencher linha a partir da posicao dada
        for (size_t i = 0; i < word.length(); ++i) {
            char matrixChar = matrix.at(y).at(x+i);
            char wordChar = word.at(i);
            if (matrixChar == '.'){
                matrix.at(y).at(x+i) = wordChar;
            } else {
                if (matrixChar != wordChar){
                    deleteWord(x,y,orientation);
                    return 3;
                }
            }
        }

        //asterisco depois da palavra
        try {
            char matrixChar = matrix.at(y).at(x + word.length());
            if (matrixChar == '.' || matrixChar == '#'){
                matrix.at(y).at(x + word.length()) = '#';
            } else {
                deleteWord(x,y,orientation);
                return 3;
            }
        } catch (out_of_range &e) {}

    }

    return 0;

}

void Board::deleteWord(size_t x, size_t y, char orientation) {
    auto iter = wordVector.begin();

    Orientation direction = orientation == 'V' ? VERTICAL : HORIZONTAL;

    //encontra o apontador para a struct com a palavra a eliminar
    while (iter != wordVector.end()){
        //encontrar
        if (iter->x == x && iter->y == y && iter->orientation == direction){
            break;
        }

        iter++;
    }

    if (iter == wordVector.end()) {
        return;
    }

    BoardWord toDelete = *iter;
    string word = toDelete.word;

    if (toDelete.orientation == VERTICAL) {
        try {
            matrix.at(toDelete.y-1).at(toDelete.x) = '.';
        } catch (out_of_range &e) {}

        for (size_t i = 0; i < word.length(); ++i) {
            matrix.at(toDelete.y+i).at(toDelete.x) = '.';
        }

        try {
            matrix.at(toDelete.y+word.length()).at(toDelete.x) = '.';
        } catch (out_of_range &e) {}
    } else {
        try {
            matrix.at(toDelete.y).at(toDelete.x-1) = '.';
        } catch (out_of_range &e) {}

        for (size_t i = 0; i < word.length(); ++i) {
            matrix.at(toDelete.y).at(toDelete.x+i) = '.';
        }

        try {
            matrix.at(toDelete.y).at(toDelete.x+word.length()) = '.';
        } catch (out_of_range &e) {}
    }

    wordVector.erase(iter);

    checkIntegrity();

}

std::ostream& operator<<(std::ostream &out, Board &board) {

    setcolor(RED);

    out << "  ";

    for (int i = 0; i < board.nCol; ++i) {
        out << (char) (97 + i) << " ";
    }

    cout << endl;

    size_t i = 0;
    for (vector<char> v: board.matrix){
        setcolor(RED);
        out << (char) (65+i++);
        setcolor(BLACK, WHITE_B);
        out << " ";
        for(char c: v){
            if (c == '#') {
                setcolor(WHITE, BLACK_B);
            }

            out << c;

            if (c == '#') {
                setcolor(BLACK, WHITE_B);
            }

            out << " ";
        }

        setcolor(WHITE, BLACK_B);

        out << endl;
    }

    setcolor(WHITE, BLACK_B);

    return out;
}

void Board::checkIntegrity() {
    //verifica se as palavras nao foram currompidas por um eliminacao, e se foram, reconstroi-as
    for (BoardWord word: wordVector){
        if (word.orientation == VERTICAL){
            try {
                matrix.at(word.y-1).at(word.x) = '#';
            } catch (out_of_range &e) {}

            for (size_t i = 0; i < word.word.length(); ++i) {
                matrix.at(word.y+i).at(word.x) = word.word.at(i);
            }

            try {
                matrix.at(word.y+word.word.length()).at(word.x) = '#';
            } catch (out_of_range &e) {}

        } else {

            try {
                matrix.at(word.y).at(word.x-1) = '#';
            } catch (out_of_range &e) {}

            for (size_t i = 0; i < word.word.length(); ++i) {
                matrix.at(word.y).at(word.x+i) = word.word.at(i);
            }

            try {
                matrix.at(word.y).at(word.x+word.word.length()) = '#';
            } catch (out_of_range &e) {}

        }
    }
}

//////////////  GETTERS AND SETTERS //////////////////////
size_t Board::getNCol() const {
    return nCol;
}

void Board::setNCol(size_t nCol) {
    Board::nCol = nCol;
}

size_t Board::getNLines() const {
    return nLines;
}

void Board::setNLines(size_t nLines) {
    Board::nLines = nLines;
}

const vector<BoardWord> &Board::getWordVector() const {
    return wordVector;
}

void Board::setWordVector(const vector<BoardWord> &wordVector) {
    Board::wordVector = wordVector;
}

const vector<vector<char>> &Board::getMatrix() const {
    return matrix;
}

void Board::setMatrix(const vector<vector<char>> &matrix) {
    Board::matrix = matrix;
}
