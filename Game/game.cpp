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

int Game::play_round() {
    if(visual_mode) {
        board -> draw(renderer);
    }
    Player* current_player = turn ? player1 : player2;
    Card* selected_card = current_player -> make_move();
    board -> swap_cards(selected_card);
    turn = !turn;
    board -> set_turn(turn);
    return board -> get_game_status();
}

Player* Game::play_game() {
    play_round();
    return nullptr;
}