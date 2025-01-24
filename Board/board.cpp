#include "board.h"

Board::Board() {
    square_size = 100;
    board_x = 25;
    board_y = 25;

    player1_pieces.push_back(Piece(2, 0, square_size, true, false));
    player1_pieces.push_back(Piece(0, 0, square_size, false, false));
    player1_pieces.push_back(Piece(1, 0, square_size, false, false));
    player1_pieces.push_back(Piece(3, 0, square_size, false, false));
    player1_pieces.push_back(Piece(4, 0, square_size, false, false));
    player2_pieces.push_back(Piece(2, 4, square_size, true, true));
    player2_pieces.push_back(Piece(0, 4, square_size, false, true));
    player2_pieces.push_back(Piece(1, 4, square_size, false, true));
    player2_pieces.push_back(Piece(3, 4, square_size, false, true));
    player2_pieces.push_back(Piece(4, 4, square_size, false, true));
}

Board::~Board() {

}

void Board::draw(SDL_Renderer* renderer) {
    // Draw board
    SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0xff);
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            SDL_Rect square_rect = {i * square_size + board_x, j * square_size + board_y, square_size, square_size};
            SDL_RenderDrawRect(renderer, &square_rect);
        }
    }

    // Draw player 1's pieces
    for(long unsigned int i = 0; i < player1_pieces.size(); i++) {
        player1_pieces.at(i).draw(renderer);
    }

    // Draw player 2's pieces
    for(long unsigned int i = 0; i < player2_pieces.size(); i++) {
        player2_pieces.at(i).draw(renderer);
    }
}