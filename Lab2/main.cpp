//ENUNCIADO: Cadena mas larga
//PARTICIPANTES: 1101331 Asier Ochoa, 1099399 Yeuris Terrero
//FECHA:

#include <iostream>

int main(){

    int num, chain[99] = {0}, num_result;

    for (int i = 1; i < 99; i++) //checks all numbers between 1-99
    {
        num = i; //uses the iterator number withot affecting th loop

        do
        {
            if ((num%2) == 0)
            {
                num = num/2; //if number is even, divide by 2
            }
            else
            {
                num = (num * 3) + 1; //if number is odd, multiply by 3 and add 1
            }

            chain[i]++; //counts how many operations have been done to the number until the result is 4
        } while (num != 4);
        
    }
    
    /*for (size_t j = 0; j < 99; j++)
    {
       std::cout << j << " " << chain[j] << "\n"; //prints all chains, useless xd
    }*/

    for (size_t i = 0; i < 99; i++) //finds longest chain
    {
        if (chain[0] < chain[i])
        {
            chain[0] = chain[i]; //finds de VALUE of the longest chain
            num_result = i; //stores the NUMBER that produces the longest chain
        }
    }

    std::cout << "Longest chain: " << chain[0] << "\n" << "Number: " << num_result; //prints longest chaing and number that produces it
    

    return 0;
}