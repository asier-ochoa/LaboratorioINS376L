//ENUNCIADO: Simulador de torres de Hanoi
//PARTICIPANTES: 1101331 Asier Ochoa; Yeuris Terrero | 1099399; Carlos Garcia | 1101629; Miguel Angel | 1100685
//FECHA: 26/06/22

#include <iostream>

int moveDiscs(int discs, char a, char b, char c )
{
    static int mov = 0;
    if (discs == 1)
    {
        std::cout << "Se ha movido el disco " << discs << " de la barra " << a << " hasta la " << c << "\n"; //si solo tiene un disco, se mueve a la torre C
        mov++;
    }
    else
    {
        moveDiscs(discs - 1, a, c, b ); //llamada recursiva hasta que se pasa el disco 1 como argumentom en dado caso es movido
        std::cout << "Se ha movido el disco " << discs << " de la barra " << a << " hasta la " << c << "\n";
        mov++;
        moveDiscs(discs - 1, b, a, c); //llamada recursiva que mueve
    }

    return mov;
}

int main()
{
    int discs, mov;
    std::cout << "Ingresa el numero de discos: ";
    std::cin >> discs;
    mov = moveDiscs(discs,'A','B','C');
    std::cout << "\nNumero de movimientos total = " << mov;
    return 0;
}