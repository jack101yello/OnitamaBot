#ifndef __player_H
#define __player_H

#include <vector>
#include "../Piece/piece.h"
#include "../Card/card.h"
#include "../Board/board.h"

class Player {
    private:
        int index;
        std::vector<Piece*> my_pieces;
        std::vector<Piece*> enemy_pieces;
        std::vector<Card*> my_cards;
        std::vector<Card*> enemy_cards;
        Card* neutral_card;

    public:
        Player(int index_i);
        virtual ~Player() {}
        // The setters are to be used by the Game to inform us of the current board state
        void set_my_pieces(std::vector<Piece*> my_pieces_i) { my_pieces = my_pieces_i; }
        void set_enemy_pieces(std::vector<Piece*> enemy_pieces_i) { enemy_pieces = enemy_pieces_i; }
        void set_my_cards(std::vector<Card*> my_cards_i) { my_cards = my_cards_i; }
        void set_enemy_cards(std::vector<Card*> enemy_cards_i) { enemy_cards = enemy_cards_i; }
        void set_neutral_card(Card* neutral_card_i) { neutral_card = neutral_card_i; }
        virtual Card* make_move(Board* board, SDL_Renderer* renderer);
        std::vector<Piece*> get_my_pieces() { return my_pieces; }
        std::vector<Card*> get_my_cards() { return my_cards; }
        bool is_legal_move(Card* c, Piece* p, move m);
        void check_kill(Piece* p);
        int get_index() { return index; }

    friend class Human_Player;
};

#endif