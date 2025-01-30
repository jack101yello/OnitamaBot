#include "piece.h"

// Piece constructor
Piece::Piece(int x_i, int y_i, int square_size_i, bool king, bool side_i, int board_x_i, int board_y_i) {
    x = x_i;
    y = y_i;
    square_size = square_size_i;
    is_king = king;
    side = side_i;
    is_alive = true;
    board_x = board_x_i;
    board_y = board_y_i;
}

// Piece destructor
Piece::~Piece() {

}

int Piece::get_screen_x() {
    int rel_x = (!side) ? x : 4-x;
    return (int)(board_x + (rel_x + 0.25) * square_size);
}

int Piece::get_screen_y() {
    int rel_y = (!side) ? y : 4-y;
    return (int)(board_y + (rel_y + 0.25) * square_size);
}

// Draw the piece to the screen
void Piece::draw(SDL_Renderer* renderer) {
    if(!is_alive) {
        return;
    }
    SDL_SetRenderDrawColor(renderer, (is_king) ? 0xff : 0x00, (side) ? 0xff : 0x00, (side) ? 0x00 : 0xff, 0xff);
    SDL_Rect piece_rect = {get_screen_x(), get_screen_y(), (int)(square_size * 0.5), (int)(square_size * 0.5)};
    SDL_RenderFillRect(renderer, &piece_rect);
}

// Check if a point is in the piece
bool Piece::in_click_range(int click_x, int click_y) {
    return click_x > get_screen_x() && click_x < (get_screen_x() + 0.5*square_size) && click_y > get_screen_y() && click_y < (get_screen_y() + 0.5*square_size);
}