//ENUNCIADO: Cadena mas larga
//PARTICIPANTES: 1101629 Carlos Ismael Garcia 
//FECHA:

#include <iostream>
#include <cstdlib>
#include <cstring>

int main()
{
int num, cadena[99]={0}, resultado;
                 
for (int i = 1; i <99; i++)
{
    num = i;  
    
        do
    {
        if((num%2) == 0)
        {
            num = num/2; // si el numero es par se divide entre 2
        }
        else
        {
          num = (num*3)+1 ; // si el numero es impar multiplique por 3 y al resultado sumale 1
        }
        cadena[i]++;
    }while (num !=4); //repetir mientras el numero no sea 4
 
}

for (size_t n = 0; n < 99; n++)
{
 std::cout<<n<<""<<cadena[n]<<"\n";    //mostrar todas las cadenas
}

for (size_t i = 0; i < 99; i++)
{
    if(cadena[0] < cadena[i])
    {
        cadena[0] = cadena[i];
        resultado = i;
    }
}

std::cout<<"cadena mas larga:"<< cadena[0]<<"\n"<< "numero:"<< resultado; // muestra la cadena mas larga y el numero que la produce


return 0;
 }


 