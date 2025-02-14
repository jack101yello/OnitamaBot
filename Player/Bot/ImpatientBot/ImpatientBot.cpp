#include "ImpatientBot.h"

ImpatientBot::ImpatientBot(int index_i) : Bot(index_i) {

}

ImpatientBot::~ImpatientBot() {

}

Card* ImpatientBot::make_move(Board* board, SDL_Renderer* renderer) {
    for(Card* chosen_card : my_cards) {
        for(Piece* chosen_piece : my_pieces) {
            if(!chosen_piece->get_is_alive()) {
                continue;
            }
            for(move chosen_move : chosen_card -> get_moves()) {
                if(!is_legal_move(chosen_card, chosen_piece, chosen_move)) {
                    continue;
                }
                chosen_piece->make_move(chosen_move);
                wait(500);
                return chosen_card;
            }
        }
    }
    printf("No legal moves exist!");
    return nullptr; // This should never occur.
}