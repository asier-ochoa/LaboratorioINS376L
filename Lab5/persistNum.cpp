//ENUNCIADO: Buscar el único número entero de solo dos dígitos cuyo número persistente es mayor que 3
//PARTICIPANTES: 1101331 Asier Ochoa ; Yeuris Terrero | 1099399 ; Carlos Garcia | 1101629 ; Miguel Angel | 1100685
//FECHA:

/*Multiplicando los números de un número entero y continuando 
el proceso, nos encontramos con el sorprendente resultado de 
que la secuencia de productos llega siempre a un numero de un 
solo digito. Por ejemplo 

715 >  35 >  15 > 5 
88 > 64 > 24 > 8 
27 > 14 > 4

Al numero de productos necesarios para alcazar un solo dígito 
se le llama persistencia de ese numero entero. Es decir, 715 y 88 
tienen persistencia 3, mientras que 27 tiene persistencia 2. 
Cuál es el único numero entero de solo dos dígitos cuyo numero 
persistente es mayor que 3?*/

#include <iostream>

int getMultDigits(int num)
{
	int digit = 0, digit2 = 0, result = 10, prst = 0;

	while (result > 9)
	{
		digit = num % 10;
		//std::cout << digit << " * ";
		num /= 10;
		//std::cout << num << " = ";
		result = digit * num;
		//std::cout << result << "\n";
		num = result;
		prst++;
	}


	return prst;
}

int main()
{
    for (size_t i = 10; i < 99; i++)
	{
		//std::cout << i << ":"<< "\n";
		//std::cout << getMultDigits(i) << "\n";

		int prst = getMultDigits(i);

		if (prst > 3)
		{
			std::cout << i << "\n";
		}
		
	}
}