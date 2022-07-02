//ENUNCIADO: Dadas 2 torres enemigas y una reina, mostrar cuales casillas son movimientos válidos para la reina
//PARTICIPANTES: 1101331 Asier Ochoa; Yeuris Terrero | 1099399; Carlos Garcia | 1101629; Miguel Angel | 1100685
//FECHA: 4/07/22

#include <array>

class Piece {
    public:
        Piece(int posX, int posY, std::array<std::array<Piece*, 8>, 8>& board): posX(posX), posY(posY), board(board) {}
        virtual void draw() = 0;
        virtual bool canMoveTo(int x, int y) = 0;
    protected:
        std::array<std::array<Piece*, 8>, 8>& board;
        int posX, posY;
};

class Queen : public Piece {
    public:
        Queen(int posX, int posY, std::array<std::array<Piece*, 8>, 8>& board): Piece(posX, posY, board) {};
        bool canMoveTo(int x, int y) override;
        void draw() override;
};


class Tower : public Piece {
    public:
        Tower(int posX, int posY, std::array<std::array<Piece*, 8>, 8>& board): Piece(posX, posY, board) {};
        bool canMoveTo(int x, int y) override;
        void draw() override;
};

bool Queen::canMoveTo(int x, int y) {
    int j = posY;
    for (int i = 0; i < board.size(); ++i) {
        if (i == x && j == y )
            return true;
    }
    int i = posX;
    for (j = 0; j < board[i].size(); ++j) {
        if (i == x && j == y)
            return true;
    }
    return false;
}

bool Tower::canMoveTo(int x, int y) {
    int j = posY;
    for (int i = 0; i < board.size(); ++i) {
        if (i == x && j == y )
            return true;
    }
    int i = posX;
    for (j = 0; j < board[i].size(); ++j) {
        if (i == x && j == y)
            return true;
    }
    return false;
}
