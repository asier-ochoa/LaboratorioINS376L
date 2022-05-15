//ENUNCIADO: Hacer juego de mastermind
//PARTICIPANTES: 1101331 Asier Ochoa
//FECHA:
#include <iostream>
#include <vector>
#include <iomanip>

template <typename T, size_t S>
class round{
    private:
        void input();
        void makeHint(round<T, S>& cmp);
        bool valid(const char* buf);
        bool checkDupe(const char* buf);

    public:
        round();
        round(round<T, S>& cmp);
        ~round() {delete[] raw; delete[] hint;}
        T* raw;
        char* hint;
};

template<typename T, size_t S>
round<T, S>::round()
    :raw(new T[S]), hint(new char[S + 1]) {
    input();
}

template<typename T, size_t S>
round<T, S>::round(round<T, S> &cmp)
    :raw(new T[S]), hint(new char[S + 1]) {
    input();
    makeHint(cmp);
}

template<typename T, size_t S>
void round<T, S>::input() {
    char buf[S + 1];
    while (true){
        std::cin >> std::setw(S + 1) >> buf;
        if (!checkDupe(buf) && valid(buf))
            break;
        std::cout << "Input invalid, please try again: ";
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

int main(){
    round<int, 4> play;
    //std::vector<round<int, 4>> Board;
    round<int, 4> test(play);

    return 0;
}