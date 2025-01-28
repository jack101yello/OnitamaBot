#include "piece.h"

// Piece constructor
Piece::Piece(int x_i, int y_i, int square_size_i, bool king, bool side_i) {
    x = x_i;
    y = y_i;
    square_size = square_size_i;
    is_king = king;
    side = side_i;
    is_alive = true;
}

// Piece destructor
Piece::~Piece() {

}

// Draw the piece to the screen
void Piece::draw(SDL_Renderer* renderer) {
    if(!is_alive) {
        return;
    }
    SDL_SetRenderDrawColor(renderer, (is_king) ? 0xff : 0x00, (side) ? 0xff : 0x00, (side) ? 0x00 : 0xff, 0xff);
    int X = (side) ? ((x+0.5) * square_size) : ((4 - x + 0.5) * square_size);
    int Y = (side) ? ((y+0.5) * square_size) : ((4 - y + 0.5) * square_size);
    SDL_Rect piece_rect = {X, Y, (int)(square_size * 0.5), (int)(square_size * 0.5)};
    SDL_RenderFillRect(renderer, &piece_rect);
}

// Check if a point is in the piece
bool Piece::in_click_range(int click_x, int click_y) {
    int X = (side) ? ((x+0.5) * square_size) : ((4 - x + 0.5) * square_size);
    int Y = (side) ? ((y+0.5) * square_size) : ((4 - y + 0.5) * square_size);

    return click_x > X && click_x < (X + 0.5*square_size) && click_y > Y && click_y < (Y + 0.5*square_size);
}