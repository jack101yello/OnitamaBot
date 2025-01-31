#ifndef __board_H
#define __board_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "../Piece/piece.h"
#include "../Card/card.h"
#include "../Card/deck.h"

class Board {
    private:
        int square_size;
        int board_x;
        int board_y;
        std::vector<Piece *> player1_pieces;
        std::vector<Piece *> player2_pieces;
        std::vector<Card*> player1_cards;
        std::vector<Card*> player2_cards;
        Card* neutral_card;
        Deck* deck;
        bool turn;

    public:
        Board(int square_size_i);
        ~Board();
        void draw(SDL_Renderer* renderer);
        std::vector<Piece*> get_player1_pieces() { return player1_pieces; }
        std::vector<Piece*> get_player2_pieces() { return player2_pieces; }
        std::vector<Card*> get_player1_cards() { return player1_cards; }
        std::vector<Card*> get_player2_cards() { return player2_cards; }
        Card* get_neutral_card() { return neutral_card; }
        void swap_cards(Card* selected_card);
        int get_game_status();
        void set_turn(bool turn_i) { turn = turn_i; }
};

#endif