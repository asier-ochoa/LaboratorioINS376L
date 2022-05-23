//ENUNCIADO: Cadena mas larga
//PARTICIPANTES: 1100685 Miguelangel
//FECHA: 22/5/22

#include <iostream>
using namespace std;

int main(){

printf("Bienvenido_al_juego_de_las_cadenas");
int numero, cadena[5] = {0}, resultado;
for (int i = 1; i < 5; i++) //Co
    {
        numero = i; //uses the iterator number withot affecting th loop

        do
        {
            if ((numero%2) == 0)
            {
                numero = numero/2; //Si el numero es par se divide
            }
            else
            {
                numero = (numero * 3) + 1; //Si el numero es impar se multiplica por 3 y se le suma uno
            }

            cadena[i]++; 
        } while (numero != 4);
        
    }
    
    for (size_t j = 0; j < 99; j++)
    {
       std::cout << j << " " << cadena[j] << "\n"; //Imprime todas las cadenas
    }

    for (size_t i = 0; i < 5; i++) //finds longest chain
    {
        if (cadena[0] < cadena[i])
        {
            cadena[0] = cadena[i]; //finds de VALUE of the longest chain
            resultado = i; //stores the NUMBER that produces the longest chain
        }
    }

    std::cout << "Longest chain: " << cadena[0] << "\n" << "Number: " << resultado; //prints longest chaing and number that produces it
    


    return 0;}