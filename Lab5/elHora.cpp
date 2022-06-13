//ENUNCIADO: Buscar el hora del día del problema
//PARTICIPANTES: 1101331 Asier Ochoa ; Yeuris Terrero | 1099399 ; Carlos Garcia | 1101629 ; Miguel Angel | 1100685
//FECHA:

/*La profesora Maria Jesus Budria explica a sus alumnos, en clase de matemáticas, 
las intrigantes propiedades de los números enteros. Les mostró como el numero 
8,833 es igual a 88^2 + 33^2 y prosiguió su clase. 

Como es habitual en los alumnos, el avispado Michelena, no prestaba atención a 
las explicaciones de su profesora observando, en su lugar, el reloj digital de la 
pared. Así, advirtió que cuando la Srta. Budria acababa de hablar del numero 
8,833, la hora que marcaba el reloj (tomada como un numero sin coma) tenia la 
misma propiedad. Esto es, el cuadrado de los dígitos que indicaban la hora, mas 
el cuadrado de los que indicaban los minutos, era igual al numero que veía en el 
reloj.

Cuál hora del dia era?*/

#include <iostream>

int getSquareSum(int hour, int minute)
{
    int x = hour * hour;
    int y = minute * minute;

    return x + y;

}

int main()
{
    for (size_t i = 1; i < 24; i++)
    {
        for (size_t j = 1; j < 60; j++)
        {
            std::string hour = std::to_string(i);
            std::string minute = std::to_string(j);
            std::string time = hour + minute;
            int timeInt = std::stoi(time);
            
            int time2 = getSquareSum(i, j);

            if (time2 == timeInt)
            {
                std::cout<< hour << ":" << minute << " Was the time of the day\n";
            }
        }
        
    }
    
}