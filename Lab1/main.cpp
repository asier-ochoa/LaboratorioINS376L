//ENUNCIADO: Hacer juego de mastermind
//PARTICIPANTES: 1101331 Asier Ochoa
//FECHA: 4/15/22
#include <iostream>
#include <vector>
#include <iomanip>

#define PLAYS 10
#define DIGITS 4
#ifdef UNIX
    #define CLEAR std::system("clear")
#endif
#ifdef WIN32
    #define CLEAR std::system("cls")
#endif

template <typename T, size_t S>
class round{
    private:
        void input();
        void makeHint(round<T, S>& cmp);
        bool valid(const char* buf);
        bool checkDupe(const char* buf);

    public:
        round();
        round(round<T, S>* cmp);
        void printHint();
        void printNums();
        T* raw;
        char* hint;

        bool operator==(const round &rhs) const;
};

template<typename T, size_t S>
round<T, S>::round()
    :raw(new T[S]), hint(new char[S + 1]) {
    input();
}

template<typename T, size_t S>
round<T, S>::round(round<T, S>* cmp)
    :raw(new T[S]), hint(new char[S + 1]) {
    input();
    makeHint(*cmp);
}

template<typename T, size_t S>
void round<T, S>::input() {
    char buf[S + 1];
    while (true){
        std::cin >> std::setw(S + 1) >> buf;
        if (!checkDupe(buf) && valid(buf))
            break;
        std::cout << "Input invalid, please try again:" << std::endl;
    }
    for (int i = 0; i < S; ++i) {
        raw[i] = buf[i] - 48; //Convert from ascii to int
    }
}

template<typename T, size_t S>
bool round<T, S>::checkDupe(const char* buf) {
    for (int i = 0; i < S; ++i) {
        for (int j = 0; j < S; ++j) {
            if (buf[i] == buf[j] && j != i)
                return true;
        }
    }
    return false;
}

template<typename T, size_t S>
void round<T, S>::makeHint(round<T, S>& cmp) {
    for (int i = 0; i < S; ++i) {
        if (raw[i] == cmp.raw[i])
            hint[i] = 'C';
        else {
            int j;
            for (j = 0; j < S; ++j) {
                if (raw[i] == cmp.raw[j] && i != j) {
                    hint[i] = 'F';
                    break;
                }
            }
            if (j > S - 1)
                hint[i] = 'X';
        }
    }
    hint[S] = '\0';
}

template<typename T, size_t S>
bool round<T, S>::valid(const char* buf) {
    for (int i = 0; i < S; ++i) {
        if (buf[i] < '1' || buf[i] > '6')
            return false;
    }
    return true;
}

template<typename T, size_t S>
void round<T, S>::printHint() {
    std::cout << hint << std::endl;
}

template<typename T, size_t S>
void round<T, S>::printNums() {
    for (int i = 0; i < S; ++i)
        std::cout << raw[i];
    std::cout << std::endl;
}

template<typename T, size_t S>
bool round<T, S>::operator==(const round &rhs) const {
    for (int i = 0; i < S; ++i) {
        if (raw[i] != rhs.raw[i])
            return false;
    }
    return true;
}


int main(){
    std::cout << "Type your key: ";
    round<int, DIGITS> key;
    CLEAR;
    std::vector<round<int, DIGITS>> board;
    for (int i = 0; i < PLAYS; ++i) {
        std::cout << "Input your sequence:" << std::endl; //Added a linebreak so hints and numbers would line up nicely
        board.emplace_back(&key);
        board[i].printHint();
        if (board.back() == key){
            std::cout << std::endl << "You Win!" << std::endl;
            break;
        }
    }

    key.printNums();
    std::cout << "--PLAYS--" << std::endl;
    for (int i = 0; i < PLAYS; ++i) {
        if (i < board.size())
            board[i].printNums();
        else {
            for (int j = 0; j < DIGITS; ++j)
                std::cout << '-';
            std::cout << std::endl;
        }
    }

    while (!board.empty()){ //cleanup, didn't use destructor because of the hassle of adding copy constructors
        delete[] board.back().raw;
        delete[] board.back().hint;
        board.pop_back();
    }
    return 0;
}