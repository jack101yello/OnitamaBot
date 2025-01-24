#ifndef __board_H
#define __board_H

#include <SDL2/SDL.h>
#include "../Piece/piece.h"
#include <vector>

class Board {
    private:
        int square_size;
        int board_x;
        int board_y;
        std::vector<Piece> player1_pieces;
        std::vector<Piece> player2_pieces;

    public:
        Board();
        ~Board();
        void draw(SDL_Renderer* renderer);
};

#endif