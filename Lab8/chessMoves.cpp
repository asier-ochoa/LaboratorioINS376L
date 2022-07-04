//ENUNCIADO: Dadas 2 torres enemigas y una reina, mostrar cuales casillas son movimientos válidos para la reina
//PARTICIPANTES: 1101331 Asier Ochoa; Yeuris Terrero | 1099399; Carlos Garcia | 1101629; Miguel Angel | 1100685
//FECHA: 4/07/22

#include <iostream>
#include <string>
typedef std::string string;

//draw the board



class chessPiece
{
private:
    string color;
    string type;

public:
    chessPiece(string color, string type)
    {

    }

    ~chessPiece() {}
};


int main()
{
    std::string tablero[8][8] = {
        {"a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8"},
        {"a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7"},
        {"a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6"},
        {"a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5"},
        {"a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4"},
        {"a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3"},
        {"a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2"},
        {"a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1"},
    };

    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            std::cout << tablero[i][j] << " ";
            
        }
        std::cout << "\n";
    }
    

    return 0;
}