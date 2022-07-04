//ENUNCIADO: Dadas 2 torres enemigas y una reina, mostrar cuales casillas son movimientos válidos para la reina
//PARTICIPANTES: 1101331 Asier Ochoa; Yeuris Terrero | 1099399; Carlos Garcia | 1101629; Miguel Angel | 1100685
//FECHA: 4/07/22

#include <vector>
#include <iostream>
#include "raylib.h"
#include "raymath.h"

bool reDraw = true;
Texture queenSprite;
Texture towerSprite;

//Coordinates origin is at top left. +Y is down and +X is right.
class Piece {
    public:
        Piece(int posX, int posY, std::vector<Piece*>& activePieces): posX(posX), posY(posY), activePieces(activePieces) {}
        virtual void draw() = 0;
        virtual bool canMoveTo(int x, int y) = 0;
        int team;
    protected:
        std::vector<Piece*>& activePieces;
        int posX, posY;
};

class Queen : public Piece {
    public:
        Queen(int posX, int posY, std::vector<Piece*>& board): Piece(posX, posY, board) {team = 0;};
        bool canMoveTo(int x, int y) override;
        void draw() override { DrawTexture(queenSprite, posX * 100, posY * 100, WHITE);}
};

class Tower : public Piece {
    public:
        Tower(int posX, int posY, std::vector<Piece*>& board): Piece(posX, posY, board) {team = 1;};
        bool canMoveTo(int x, int y) override;
        void draw() override { DrawTexture(towerSprite, posX * 100, posY * 100, WHITE);}
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
    queenSprite = LoadTextureFromImage(LoadImage("queen.png"));
    towerSprite = LoadTextureFromImage(LoadImage("tower.png"));
    RenderTexture framebuffer = LoadRenderTexture(800, 800);
    std::vector<Piece*> pieces;
    pieces.emplace_back(new Queen(4, 6, pieces));
    Piece& q_ref = *pieces.back();
    pieces.emplace_back(new Tower(1, 1, pieces));
    pieces.emplace_back(new Tower(3, 1, pieces));

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
                        DrawRectangleRec(a, (i % 2 == 0 ? Color{227, 191, 159, 255} : Color{82, 55, 33, 255}));
                    else
                        DrawRectangleRec(a, (i % 2 != 0 ? Color{227, 191, 159, 255} : Color{82, 55, 33, 255}));

                }
            }
            //Draw pieces
            for (int i = 0; i < pieces.size(); ++i) {
                pieces[i]->draw();
            }
            //Draw possible moves
            for (int i = 0; i < 8; ++i) {
                for (int j = 0; j < 8; ++j) {
                    if (q_ref.canMoveTo(i, j)){
                        bool blocked = false;
                        Rectangle a = {(float)i * 100, (float)j * 100, 100, 100};
                        for (int k = 0; k < pieces.size(); ++k) {
                            if (pieces[k]->team != 0){
                                if (pieces[k]->canMoveTo(i, j)){
                                    DrawRectangleRec(a, Color{255, 0, 0, 127});
                                    blocked = true;
                                    break;
                                }
                            }
                        }
                        if (!blocked)
                            DrawRectangleRec(a, Color{0, 255, 0, 127});
                    }
                }
                std::cout << '\n';
            }
            EndTextureMode();
        }
        BeginDrawing();
        DrawTexturePro(framebuffer.texture, Rectangle{0, 0, 800, -800}, Rectangle{0, 150, 800, 800},Vector2{0,0},0,WHITE);
        EndDrawing();
        reDraw = false;
    }

    Piece& t_ref = *pieces[1];

    std::cout << "Tower:\n";
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            std::cout << t_ref.canMoveTo(i, j);
        }
        std::cout << '\n';
    }
    return 0;
}