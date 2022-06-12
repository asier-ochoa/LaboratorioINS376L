//ENUNCIADO: Buscar el hora del día del problema
//PARTICIPANTES: 1101331 Asier Ochoa ; Yeuris Terrero | 1099399 ; Carlos Garcia | 1101629 ; Miguel Angel | 1100685
//FECHA: 11/06/22

#include <iostream>

int main(){
    for (int i = 0; i < 24; ++i) {
        for (int j = 0; j < 60; ++j) {
            if (i * 100 + j == i * i + j * j)
                std::cout << i << ':' << j << '\n';
        }
    }
    return 0;
}