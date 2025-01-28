#include "board.h"


// Board constructor
Board::Board() {
    square_size = 100;
    board_x = 25;
    board_y = 25;

    player1_pieces.push_back(new Piece(2, 0, square_size, true, false));
    player1_pieces.push_back(new Piece(0, 0, square_size, false, false));
    player1_pieces.push_back(new Piece(1, 0, square_size, false, false));
    player1_pieces.push_back(new Piece(3, 0, square_size, false, false));
    player1_pieces.push_back(new Piece(4, 0, square_size, false, false));
    player2_pieces.push_back(new Piece(2, 0, square_size, true, true));
    player2_pieces.push_back(new Piece(0, 0, square_size, false, true));
    player2_pieces.push_back(new Piece(1, 0, square_size, false, true));
    player2_pieces.push_back(new Piece(3, 0, square_size, false, true));
    player2_pieces.push_back(new Piece(4, 0, square_size, false, true));
}

// Board destructor
Board::~Board() {
    for(Piece* p : player1_pieces) {
        delete p;
    }
    player1_pieces.clear();
    for(Piece* p : player2_pieces) {
        delete p;
    }
    player2_pieces.clear();
}

// Draw the board to the screen
void Board::draw(SDL_Renderer* renderer) {
    // Draw board
    SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0xff);
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            SDL_Rect square_rect = {i * square_size + board_x, j * square_size + board_y, square_size, square_size};
            SDL_RenderDrawRect(renderer, &square_rect);
        }
    }

    // Draw pieces
    for(long unsigned int i = 0; i < player1_pieces.size(); i++) {
        player1_pieces.at(i) -> draw(renderer);
        player2_pieces.at(i) -> draw(renderer);
    }
}