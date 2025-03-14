#include "player.h"

Player::Player(int index_i) {
    index = index_i;
}

Card* Player::make_move(Board* board, SDL_Renderer* renderer) {
    return nullptr;
}

// Conduct a series of checks and return if the move is legal
bool Player::is_legal_move(Card* c, Piece* p, move m) {
    // Check that the move is on the selected card
    if(!(c -> is_valid_move(m))) {
        return false;
    }

    // Check that the piece is alive
    if(!(p->get_is_alive())) {
        return false;
    }

    // Check that the move is on the board
    if(m.x + p->get_x() < 0 || m.x + p->get_x() > 4 || m.y + p->get_y() < 0 || m.y + p->get_y() > 4) {
        return false;
    }

    // Check that are aren't intersecting our own piece
    for(Piece* other : my_pieces) {
        if(!other->get_is_alive()) { // We shouldn't care about intersecting a dead piece.
            continue;
        }
        if(m.x + p->get_x() == other -> get_x() && m.y + p->get_y() == other -> get_y()) {
            return false;
        }
    }
    return true;
}

void Player::check_kill(Piece* p) {
    for(Piece* enemy : enemy_pieces) {
        if(p -> get_x() == 4 - enemy->get_x() && p -> get_y() == 4 - enemy->get_y()) {
            enemy -> kill();
        }
    }
}