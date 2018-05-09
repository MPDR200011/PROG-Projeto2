#include "cwcreator.h"
#include "wordUtils.h"

using namespace std;

//Construtor usado caso utilizador queira construir um puzzle novo
cwcreator::cwcreator() {
    isTableLoadedFromSave = false;

    cout << "-----------------------------------------------" << endl;
    cout << "CREATE PUZZLE" << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "Dictionary file name ? ";

    //Fase de criacao do dicionario//
    //Pedido do nome do ficheiro
    bool validInput;
    ifstream dictionaryFile;
    do {
        string fileName;
        pw::readString(fileName);
        dictionaryFile.open(fileName);
        if (dictionaryFile.is_open()){
            //nome do ficheiro do dicionario e guardado pois sera util no processo
            //de guardar a tabela
            dictionaryName = fileName;

            validInput = true;
        } else {
            validInput = false;
            cout << "File not found. Try again.";
        }
    } while (!validInput);

    //Criacao do dicionario
    dict = Dictionary(dictionaryFile);
    dictionaryFile.close();

    //Solicitacao das dimensoes da tabela. Sao feitas uma a uma
    //pois a funcao em wordUtils nao funciona com multiplas variaveis
    size_t nCols, nLines;
    cout << "Board Columns (max: 26) ? ";
    nCols = boardSizeInput();
    cout << "Board Lines (max: 26) ? ";
    nLines = boardSizeInput();

    //Inicializacao da class Board
    board = Board(nLines, nCols);

    buildLoop();
}

//Construtor usado caso utilizador queira continuar a criar um puzzle que tenha deixado a meio
//ficheiro introduzido segue modelo proposto no enunciado do trabalho
cwcreator::cwcreator(std::ifstream &saveFile, const std::string &name) {

    isTableLoadedFromSave = true;
    this->saveFileName = name;

    string temp;

    //Inicializacao do dicinoario
    getline(saveFile, dictionaryName);
    ifstream dictionaryFile(dictionaryName);
    while (!dictionaryFile.is_open()) {
        cout << "Dictionary in the directory does not exist, input valid name." << endl;
        pw::readString(dictionaryName);
        dictionaryFile.open(dictionaryName);
    }

    dict = Dictionary(dictionaryFile);
    dictionaryFile.close();

    //Ignorar linha vazia
    getline(saveFile, temp);

    size_t nCols = 0;
    size_t nLines = 0;

    //Iterar pelas linhas da tabela e extrair dimensões da tabela.
    getline(saveFile, temp);
    nCols = temp.length();

    while (!temp.empty()) {
        ++nLines;
        getline(saveFile, temp);
    }

    //Inicializacao da class Board
    board = Board(nLines, nCols);

    //Adicionar palavras a tabela
    while (getline(saveFile, temp)) {
        size_t x = (unsigned int) temp.at(1) - 97;
        size_t y = (unsigned int) temp.at(0) - 65;
        char orientation = temp.at(2);
        string word = temp.substr(4, string::npos);

        board.addWord(word, x, y, orientation);
    }

    saveFile.close();

    buildLoop();
}

//Ciclo de construcao principal
void cwcreator::buildLoop() {

    bool anotherInput;
    do {

        anotherInput = true;

        //Imprimir tabela com caracteres coloridos
        cout << endl;
        cout << board;

        bool validWord;
        do{

            validWord = true;

            cout << "Position ( LCD / write \"exit\" to stop ) ? ";
            string position = takePosition();

            //Caso o utilizador escreva "exit" no campo da posicao, o programa encerra
            if (position == "exit") {
                anotherInput = false;
                exitProcess();
                break;
            }

            //Processamento da posicao introduzida
            size_t x = (unsigned int) position.at(1) - 97;
            size_t y = (unsigned int) position.at(0) - 65;
            char orientation = position.at(2) == 'V' ? 'V' : 'H';

            //Quando o utilizador escreve "?" o programa mostra sugestoes e pede para instroduzir
            string word;
            do {
                cout << "Word (- = remove / ? = help) ? ";
                pw::readString(word);
                word = pw::makeUpper(word);
                word = pw::trim(word);

                if (word == "?") {
                    help(x,y,orientation);
                    validWord = false;
                    break;
                }

                //verificacao se a palavra
                vector<string> dictWords = dict.getHeadWords();
                auto iter = find(dictWords.begin(), dictWords.end(), word);
                if (iter == dictWords.end()){
                    cout << "Word is not in dictionary." << endl;
                    validWord = false;
                    break;
                }

            } while (word == "?");

            //Caso o utilizador escreva "-" o programa elimina a palavra na posicao dada
            if (word == "-"){
                board.deleteWord(x,y,orientation);
                continue;
            }

            //se a palavra nao se mostre valida nao vale a pena correr o switch em baixo
            //entao, passa-se diretamente para a prxima iteracao
            if (!validWord) continue;

            //Gestao de erros e palavras invalidas (caso sejam) e alertamento ao utilizador
            //acerca do porque da sua palavra ser invalida
            switch (board.addWord(word, x, y, orientation)) {
                case 1: {
                    cout << "Word does not fit, try again." << endl << endl;
                    validWord = false;
                    break;
                }
                case 2: {
                    cout << "Word is already in table, try again." << endl << endl;
                    validWord = false;
                    break;
                }
                case 3: {
                    cout << "Word will corrupt table, try again." << endl << endl;
                    validWord = false;
                    break;
                }
                default:
                    validWord = true;
            }

        } while (!validWord);

    } while (anotherInput);
}

//Funcao de extracao de input da posicao com verificacao de formato
std::string cwcreator::takePosition() {
    bool validInput;
    string position;
    do {
        pw::readString(position);

        //Se o utilizador introduzio "exit" o programa retorna isso mesmo
        if (position == "exit"){
            return position;
        }

        //remover espacos a frente e atras
        position = pw::trim(position);

        //Posicao deve ter 3 e so 3 letras
        if (position.length() != 3) {
            validInput = false;
            cout << "Invalid input, try again." << endl;
        } else {
            //Deve seguir o formato de uma Maiuscula seguida de uma minuscula, seguidas de um "V" ou um "H"
            if (isupper(position.at(0))
                && islower(position.at(1))
                && (position.at(2) == 'V' || position.at(2) == 'H')) {
                //Por fim deve nao estar fora da tabela
                if (validatePosition(position)) {
                    validInput = true;
                } else {
                    validInput = false;
                    cout << "Invalid input, try again." << endl;
                }
            } else {
                validInput = false;
                cout << "Invalid input, try again." << endl;
            }
        }
    } while (!validInput);

    return position;
}

//Funcao de verificacao que testa se a posicao fica fora da tabela ou nao
bool cwcreator::validatePosition(std::string pos) {
    if (pos.at(0) - 65 > board.getNLines() - 1) {
        return false;
    }

    return pos.at(1) - 97 <= board.getNCol() - 1;
}

//Funcao feita para retornar uma unsigned int introduzida pelo utilizador
//(criada para extrair as dimencoes da tabela)
size_t cwcreator::boardSizeInput() {
    size_t value;
    bool validInput;
    do {
        pw::takeInput(value);
        if (value > 26) {
            validInput = false;
            cout << "Too Big, try again." << endl;
        } else {
            validInput = true;
        }
    } while(!validInput);

    return value;
}

//Funcao que imprime as plavras que se podem introduzir no espaco indicado pelo jogador
void cwcreator::help(size_t x, size_t y, char orientation) {
    vector<string> wildcardVector;
    set<string> suggestions;
    vector<vector<char>> matrix = board.getMatrix();

    //varrer o espaco dispnivel para adicionar uma palavra
    if (orientation == 'V') {
        string temp;
        for (size_t i = y; i < board.getNLines() - y; i++) {
            char c = matrix.at(i).at(x);
            if ( c == '#') {
                break;
            } else if (c == '.') {
                temp += '?';
                try {
                    if (!isalnum(matrix.at(i+1).at(x))) {
                        wildcardVector.push_back(temp);
                    }
                } catch (out_of_range) {
                    wildcardVector.push_back(temp);
                }
            } else {
                temp += c;
                try {
                    if (!isalnum(matrix.at(i+1).at(x))) {
                        wildcardVector.push_back(temp);
                    }
                } catch (out_of_range) {
                    wildcardVector.push_back(temp);
                }
            }
        }
    } else {
        string temp;
        for (size_t i = x; i < board.getNLines() - x; i++) {
            char c = matrix.at(y).at(i);
            if ( c == '#') {
                break;
            } else if (c == '.') {
                temp += '?';
                try {
                    if (!isalnum(matrix.at(y).at(i+1))) {
                        wildcardVector.push_back(temp);
                    }
                } catch (out_of_range) {
                    wildcardVector.push_back(temp);
                }
            } else {
                temp += c;
                try {
                    if (!isalnum(matrix.at(y).at(i+1))) {
                        wildcardVector.push_back(temp);
                    }
                } catch (out_of_range) {
                    wildcardVector.push_back(temp);
                }
            }
        }
    }

    for (const string &wcWord : wildcardVector) {
        for (const string &word: dict.getHeadWords()) {
            if (pw::wildcardMatch(word.c_str(), wcWord.c_str())){
                suggestions.insert(word);
            }
        }
    }

    if (suggestions.empty()){
        cout << "There are no words you can put in this position." << endl;
    } else {
        cout << "You can put the following: " << endl;
        for (string word: suggestions){
            cout << word << endl;
        }
    }
}

//Funcao com responsabilidade de encerrar o programa, pergunatando ao utilizador se quer guardar
void cwcreator::exitProcess() {
    cout << endl << "Do you want to save the board (y/n)? ";
    bool validChoice;
    char choice;
    do {
        pw::takeInput(choice);
        choice = (char) toupper(choice);
        if (choice == 'Y' || choice == 'N') {
            validChoice = true;
        } else {
            cout << "Invalid choice, try again. ";
            validChoice = false;
        }
    } while (!validChoice);

    if (choice == 'N'){
        return;
    } else {
        saveProgress();
    }
}

//Funcao encarregue de guardar
void cwcreator::saveProgress() {

    ofstream outputFile;
    //Caso a tabela seja carregada de um save, sera guardada no mesmo ficheiro
    string fileName = isTableLoadedFromSave ? saveFileName : createSaveFileName();
    outputFile.open(fileName);

    //nome do ficheiro de dicionario na primeira linha
    outputFile << dictionaryName << endl << endl;

    //Tabela do jogo a partir da terceira
    for (vector<char> v: board.getMatrix()){
        for (char c : v){
            outputFile << c;
        }
        outputFile << endl;
    }

    //Deixando um linha em branco a seguir a tabela
    //Sao imprimidas as posicaoes das palavras bem como as respetivas palavras
    for (BoardWord word: board.getWordVector()){
        outputFile << endl;
        auto x = (char) (word.x + 97);
        auto y = (char) (word.y + 65);
        char orientation = word.orientation == HORIZONTAL ? 'H' : 'V';
        outputFile << y << x << orientation << " " << word.word;
    }

    outputFile.close();

}

//Gerador de nomes para os ficheiros para guardar a tabela
std::string cwcreator::createSaveFileName() {
    //criar um vetor de nomes de ficheiros com tabelas guardadas
    DIR *dir;
    struct dirent *ent;
    vector<string> existingFiles;
    if ((dir = opendir (pw::getWorkingDirectory().c_str())) != nullptr) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != nullptr) {
            string name = ent->d_name;
            if (pw::wildcardMatch(name.c_str(), "b???.txt")) {
                existingFiles.push_back(name);
            }
        }
        closedir (dir);
    } else {
        /* could not open directory */
        perror ("");
        return "default.txt";
    }

    //procura maior numero
    size_t biggestNumber = 0;
    for (const string &s : existingFiles) {
        size_t temp = (size_t) stoi(s.substr(1,3));
        if (temp > biggestNumber) {
            biggestNumber = temp;
        }
    }

    string number = to_string(biggestNumber+1);

    while (number.length() < 3) {
        number = "0" + number;
    }

    //devolve nome do ficheiro
    return "b" + number + ".txt";

}


