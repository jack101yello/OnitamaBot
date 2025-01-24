#include "piece.h"

Piece::Piece(int x_i, int y_i, int square_size_i, bool king, bool side_i) {
    x = x_i;
    y = y_i;
    square_size = square_size_i;
    is_king = king;
    side = side_i;
    is_alive = true;
}

Piece::~Piece() {

}

void Piece::draw(SDL_Renderer* renderer) {
    if(!is_alive) {
        return;
    }
    SDL_SetRenderDrawColor(renderer, (is_king) ? 0xff : 0x00, (side) ? 0xff : 0x00, (side) ? 0x00 : 0xff, 0xff);
    SDL_Rect piece_rect = {(int)(x * square_size + square_size * 0.5), (int)(y * square_size + square_size * 0.5), (int)(square_size * 0.5), (int)(square_size * 0.5)};
    SDL_RenderFillRect(renderer, &piece_rect);
}