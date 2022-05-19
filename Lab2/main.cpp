//ENUNCIADO: Cadena mas larga
//PARTICIPANTES: 1101331 Asier Ochoa
//FECHA:

#include <iostream>
#include <cstdlib>
#include <cstring>

class guest{ // DON'T USE VECTORS, BOY
    private:
        unsigned int num;
        unsigned int* list;
        size_t size;
        size_t elements;

        void expand();

    public:
        guest(): num(rand() % 99 + 1), list(new unsigned int[1]), size(1), elements(0) {list[0] = num;}
        guest(const guest& other)
                : num(other.num), list(new unsigned int[other.size]), size(other.size), elements(other.elements)
            {memcpy(list, other.list, size);}
        ~guest() {delete[] list;}

        void makeList();
        unsigned int& getNum() {return num;}
};

void guest::expand() {
    auto* tmp = new unsigned int[size * 2];
    memcpy(tmp, list, size);
    size *= 2;
    delete[] list;
    list = tmp;
}

void guest::makeList() {
    while (num != 4){

    }
}

int main(){
    srand(time(nullptr)); //Seed with unix time
    guest party[99](10); //calls constructor on every member (BRUH)
    for (int i = 0; i < 99; ++i) {
        std::cout << party[i].getNum() << ';';
    }
    std::cout << '\n';
    return 0;
}