//ENUNCIADO: Cadena mas larga
//PARTICIPANTES: 1101331 Asier Ochoa
//FECHA:

#include <iostream>
#include <cstdlib>


class guest{ // DON'T USE VECTORS, BOY
    private:
        unsigned int num;
        unsigned int* list;
        size_t size;
        size_t elements;

    public:
        guest(): num(), list(new unsigned int[1]), size(1), elements(0) {};
        ~guest() {delete[] list;}
};

int main(){
    std::cout << "HEY\n";
    return 0;
}