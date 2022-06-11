//ENUNCIADO: Buscar el único número entero de solo dos dígitos cuyo número persistente es mayor que 3
//PARTICIPANTES: 1101331 Asier Ochoa ; Yeuris Terrero | 1099399 ; Carlos Garcia | 1101629 ; Miguel Angel | 1100685
//FECHA: 10/06/22

#include <iostream>

int multiplyDigits(int x);
int getMax(const int x[], size_t len);

int multiplyDigits(int x) {
    int ret = 1;
    for (int i = x; i > 0 ; i /= 10) {
        ret *= i % 10;
    }
    return ret;
}

int getMax(const int x[], size_t len){
    int max = 0;
    for (int i = 0; i < len; ++i) {
        if (x[i] > x[max])
            max = i;
    }
    return max;
}

int main() {
    int persistence[90];
    for (int i = 10; i < 100; ++i) {
        int n = i;
        int iter = 0;
        std::cout << i << ':';
        while (n > 9) {
            n = multiplyDigits(n);
            std::cout << n << " > ";
            iter++;
        }
        persistence[i - 10] = iter;
        std::cout << "\b\b\b; [" << iter << "]\n";
    }
    std::cout << "-------------\n";
    std::cout << "Max = " << getMax(persistence, 89) + 10 << ", Persistence = ";
    std::cout << persistence[getMax(persistence, 89)] << '\n';
    return 0;
}