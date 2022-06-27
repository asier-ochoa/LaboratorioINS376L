//ENUNCIADO: Simulador de torres de Hanoi
//PARTICIPANTES: 1101331 Asier Ochoa; Yeuris Terrero | 1099399; Carlos Garcia | 1101629; Miguel Angel | 1100685
//FECHA: 26/06/22

//ESTA INCORRECTO, UN DISCO MAS GRANDE NO PUEDE IR ENCIMA DE UN MAS PEQUEÑO

#ifdef WIN32
#include <conio.h>
#endif
#include <iostream>
using namespace std;

void torres_hanoi(int disk, int one, int two, int three);

int main()
{

	int a;

	cout << "Torres de Hanoi\n\n" << endl;

	cout << "Ingresa el numero de discos: ";

	cin >> a;

	torres_hanoi(a, 1, 3, 2);

    #ifdef WIN32
    _getch(); //reads every character but donsnt display them on screen.
    #endif

}

// main function
void torres_hanoi(int disk, int one, int two, int three) 
{

	if (disk == 1) 
	{
		cout << "\n";
		cout << "Disco " << disk << " del poste " << one << " al poste " << three << endl;
		#ifdef WIN32
        _getch();
        #endif

	}
	else 
	{

		torres_hanoi(disk - 1, one, two, three); // Recursion is used and we also subtract 1 from the disk
		cout << "Disco " << disk << " del poste " << one << " al poste " << three << endl;
		cout << "\n";
		#ifdef WIN32
        _getch();
        #endif

		torres_hanoi(disk - 1, two, three, one);
		// this serves as the route
	}

}

