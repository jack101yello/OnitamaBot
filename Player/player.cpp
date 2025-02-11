#include "player.h"

Player::Player() {
    
}

Card* Player::make_move(Board* board, SDL_Renderer* renderer) {
    return nullptr;
}

// Conduct a series of checks and return if the move is legal
bool Player::is_legal_move(Card* c, Piece* p, move m) {
    // Check that the move is on the selected card
    if(!(c -> is_valid_move(m))) {
        printf("Move not on card.\n");
        return false;
    }

    // Check that the move is on the board
    if(m.x + p->get_x() < 0 || m.x + p->get_x() > 4 || m.y + p->get_y() < 0 || m.y + p->get_y() > 4) {
        printf("Move not on board.\n");
        return false;
    }

    // Check that are aren't intersecting our own piece
    for(Piece* other : my_pieces) {
        if(m.x + p->get_x() == other -> get_x() && m.y + p->get_y() == other -> get_y()) {
            printf("Move intersects our own piece.\n");
            return false;
        }
    }
    
    return true;
}