#include "game.h"

Game::Game(Player* player1_i, Player* player2_i, int square_size, SDL_Renderer* renderer_i) {
    board = new Board(square_size);
    player1 = player1_i;
    player2 = player2_i;

    // Inform the players of the initial conditions
    player1->set_my_pieces(board->get_player1_pieces());
    player2->set_enemy_pieces(board->get_player1_pieces());
    player1->set_enemy_pieces(board->get_player2_pieces());
    player2->set_my_pieces(board->get_player2_pieces());
    player1->set_my_cards(board->get_player1_cards());
    player2->set_enemy_cards(board->get_player1_cards());
    player1->set_enemy_cards(board->get_player2_cards());
    player2->set_my_cards(board->get_player2_cards());

    turn = true;
    renderer = renderer_i;
}

Game::~Game() {
    delete player1;
    delete player2;
    delete board;
}

// Play one round of Onitama
int Game::play_round() {
    if(visual_mode) { // Draw to screen
        board -> draw(renderer);
        SDL_RenderPresent(renderer);
    }
    Player* current_player = turn ? player1 : player2; // Whose turn is it?
    Card* selected_card = current_player -> make_move(); // Figure out that player's move
    board -> swap_cards(selected_card); // Exchange their played card for the neutral card
    turn = !turn; // Reverse the turn for next time
    board -> set_turn(turn); // Tell the board that we've switched sides
    return board -> get_game_status(); // Check if someone has won
}

// Play a full game of Onitama
Player* Game::play_game() {
    play_round();
    return nullptr;
}