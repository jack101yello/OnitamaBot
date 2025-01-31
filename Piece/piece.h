#ifndef __piece_H
#define __piece_H

#include <SDL2/SDL.h>

class Piece {
    private:
        int x;
        int y;
        int square_size;
        bool is_king;
        bool side;
        bool is_alive;
        int board_x;
        int board_y;
        int get_screen_x(bool current_player);
        int get_screen_y(bool current_player);

    public:
        Piece(int x_i, int y_i, int square_size_i, bool king, bool side_i, int board_x_i, int board_y_i);
        ~Piece();
        void draw(SDL_Renderer* renderer, bool current_player);
};

#endif