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

int Piece::get_screen_x(bool current_player) {
    int rel_x = (current_player) ? 4-x : x;
    return (int)(board_x + (rel_x + 0.25) * square_size);
}

int Piece::get_screen_y(bool current_player) {
    int rel_y = (current_player) ? 4-y : y;
    return (int)(board_y + (rel_y + 0.25) * square_size);
}

// Draw the piece to the screen
void Piece::draw(SDL_Renderer* renderer, bool current_player) {
    if(!is_alive) {
        return;
    }
    SDL_SetRenderDrawColor(renderer, (side ? 0x80 : 0x00) + (is_king && side ? 0xff-0x80 : 0x00), is_king ? 0x80 : 0x00, (!side ? 0x80 : 0x00) + (is_king && !side ? 0xff-0x80 : 0x00), 0xff);
    SDL_Rect piece_rect = {get_screen_x(current_player), get_screen_y(current_player), (int)(square_size * 0.5), (int)(square_size * 0.5)};
    SDL_RenderFillRect(renderer, &piece_rect);
}

// Move the piece according to a given move
void Piece::make_move(move m) {
    x += m.x;
    y += m.y;
}