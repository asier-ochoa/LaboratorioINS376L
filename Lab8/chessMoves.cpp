//ENUNCIADO: Dadas 2 torres enemigas y una reina, mostrar cuales casillas son movimientos válidos para la reina
//PARTICIPANTES: 1101331 Asier Ochoa; Yeuris Terrero | 1099399; Carlos Garcia | 1101629; Miguel Angel | 1100685
//FECHA: 4/07/22

#include <vector>
#include <iostream>
#include "raylib.h"
#include "raymath.h"

bool reDraw = true;

//Coordinates origin is at top left. +Y is down and +X is right.
class Piece {
    public:
        Piece(int posX, int posY, std::vector<Piece*>& activePieces): posX(posX), posY(posY), activePieces(activePieces) {}
        virtual void draw() = 0;
        virtual bool canMoveTo(int x, int y) = 0;
    protected:
        std::vector<Piece*>& activePieces;
        int posX, posY;
};

class Queen : public Piece {
    public:
        Queen(int posX, int posY, std::vector<Piece*>& board): Piece(posX, posY, board) {};
        bool canMoveTo(int x, int y) override;
        void draw() override {}
};

class Tower : public Piece {
    public:
        Tower(int posX, int posY, std::vector<Piece*>& board): Piece(posX, posY, board) {};
        bool canMoveTo(int x, int y) override;
        void draw() override {}
};

bool Queen::canMoveTo(int x, int y) {
    for (int i = 0, j = posY; i < 8; ++i) {
        if (i == x && j == y )
            return true;
    }
    for (int j = 0, i = posX; j < 8; ++j) {
        if (i == x && j == y)
            return true;
    }
    for (int i = posX, j = posY; i < 8 && j < 8; i++, j++) { //bottom right
        if (i == x && j == y)
            return true;
    }
    for (int i = posX, j = posY; i < 8 && j > -1; i++, j--) { //top right
        if (i == x && j == y)
            return true;
    }
    for (int i = posX, j = posY; i > -1 && j < 8; i--, j++) { //bottom left
        if (i == x && j == y)
            return true;
    }
    for (int i = posX, j = posY; i > -1 && j > -1; i--, j--) { //top left
        if (i == x && j == y)
            return true;
    }
    return false;
}

bool Tower::canMoveTo(int x, int y) {
    for (int i = 0, j = posY; i < 8; ++i) {
        if (i == x && j == y )
            return true;
    }
    for (int j = 0, i = posX; j < 8; ++j) {
        if (i == x && j == y)
            return true;
    }
    return false;
}

int main() {
    InitWindow(800, 950, "Chess Move Sim");
    SetTargetFPS(60);
    LoadTextureFromImage(LoadImage("queen.png"));
    LoadTextureFromImage(LoadImage("tower.png"));
    RenderTexture framebuffer = LoadRenderTexture(800, 800);
    std::vector<Piece*> pieces;
    pieces.emplace_back(new Queen(3, 6, pieces));
    pieces.emplace_back(new Tower(1, 1, pieces));

    while (!WindowShouldClose()){
        ClearBackground(BLACK);
        if (reDraw){
            BeginTextureMode(framebuffer);
            ClearBackground(WHITE);
            // Draw board
            for (int i = 0; i < 8; ++i) {
                for (int j = 0; j < 8; ++j) {
                    Rectangle a = {(float)i * 100, (float)j * 100, 100, 100};
                    if (j % 2 == 0)
                        DrawRectangleRec(a, (i % 2 == 0 ? Color{249, 246, 187, 255} : Color{127, 76, 31, 255}));
                    else
                        DrawRectangleRec(a, (i % 2 != 0 ? Color{249, 246, 187, 255} : Color{127, 76, 31, 255}));

                }
            }
            //Draw pieces
            for (int i = 0; i < pieces.size(); ++i) {

            }
            EndTextureMode();
        }
        BeginDrawing();
        DrawTexturePro(framebuffer.texture, Rectangle{0, 0, 800, -800}, Rectangle{0, 150, 800, 800},Vector2{0,0},0,WHITE);
        EndDrawing();
        reDraw = false;
    }

    Piece& q_ref = *pieces[0];
    Piece& t_ref = *pieces[1];

    std::cout << "Queen:\n";
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            std::cout << q_ref.canMoveTo(i, j);
        }
        std::cout << '\n';
    }

    std::cout << "Tower:\n";
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            std::cout << t_ref.canMoveTo(i, j);
        }
        std::cout << '\n';
    }
    return 0;
}