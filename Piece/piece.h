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

    public:
        Piece(int x_i, int y_i, int square_size_i, bool king, bool side_i);
        ~Piece();
        void draw(SDL_Renderer* renderer);
        bool in_click_range(int click_x, int click_y);
};

#endif