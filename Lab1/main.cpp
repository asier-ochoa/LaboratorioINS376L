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
        void makeHint(round cmp);
        bool checkDupe(const char* buf);

    public:
        round();
        ~round() {delete[] raw; delete[] hint;}
        T* raw;
        char* hint;
};

template<typename T, size_t S>
round<T, S>::round()
    :raw(new T[S]), hint(new char[S])
{
    input();
}

template<typename T, size_t S>
void round<T, S>::input() {
    char buf[S];
    while (true){
        std::cin >> std::setw(S) >> buf;
        if (checkDupe(buf) )
            break;
        std::cout << "Input invalid, please try again: ";
    }
}

template<typename T, size_t S>
bool round<T, S>::checkDupe(const char* buf) {
    for (int i = 0; i < S; ++i) {
        if (buf[i] < '1' || buf[i] > '6') //Is not valid if input is not between 1 and 6
            return false;
        for (int j = 0; j < S; ++j) {
            if (buf[i] == buf[j] && j != i)
                return false;
        }
    }
    return true;
}

template<typename T, size_t S>
void round<T, S>::makeHint(round<T, S> cmp) {
    for (int i = 0; i < S; ++i) {
        if ()
    }
}

int main(){
    round<int, 4> play;
    //std::vector<round<int, 4>> Board;


    return 0;
}