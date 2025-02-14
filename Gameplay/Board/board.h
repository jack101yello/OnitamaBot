#ifndef __board_H
#define __board_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "../../Gameplay/Piece/piece.h"
#include "../../Gameplay/Card/card.h"
#include "../../Gameplay/Card/deck.h"
#include "../../Types/types.h"

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
        bool card_clicked(int MouseX, int MouseY, bool left_card);
        move get_square_from_mouse(int MouseX, int MouseY);
        move get_move_from_mouse(int piece_x, int piece_y, int MouseX, int MouseY);
        int get_board_x() { return board_x; }
        int get_board_y() { return board_y; }
        int get_square_size() { return square_size; }
};

#endif