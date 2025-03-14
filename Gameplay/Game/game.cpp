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

/*
Output the game telemetry from all perspectives.
Modes:
1 - Card Data
2 - Piece Data
3 - Card & Piece Data
*/
void Game::telemetry_dump(int mode) {
    if(mode & 1) {
        printf("Card Data\n");
        printf("Player 1 Data:\n");
        printf(" Cards: %d and %d\n", player1 -> get_my_cards().at(0) -> get_index(), player1 -> get_my_cards().at(1) -> get_index());
        printf("Player 2 Data\n");
        printf(" Cards: %d and %d\n", player2 -> get_my_cards().at(0) -> get_index(), player2 -> get_my_cards().at(1) -> get_index());
        printf("Board Data:\n");
        printf(" P1 Cards: %d and %d\n", board -> get_player1_cards().at(0) -> get_index(), board -> get_player1_cards().at(1) -> get_index());
        printf(" P2 Cards: %d and %d\n", board -> get_player2_cards().at(0) -> get_index(), board -> get_player2_cards().at(1) -> get_index());
        printf(" N Card: %d\n", board -> get_neutral_card() -> get_index());
    }
    if(mode & 2) {
        printf("Piece Data\n");
        printf("Player 1 Data:\n");
    }
}

// Update the players' cards to what the board tells them they are
void Game::update_cards() {
    /* 
    This method could be done away with if the players and the board instead dealt with
    pointers to vectors of their cards and pieces. This may make things easier, but it
    seems a little inelegant and would require quite a few changes. Perhaps try it later
    once things are working better, but it isn't a priority.
    */
    player1 -> set_my_cards(board -> get_player1_cards());
    player1 -> set_enemy_cards(board -> get_player2_cards());
    player2 -> set_my_cards(board -> get_player2_cards());
    player2 -> set_enemy_cards(board -> get_player1_cards());
}

// Play one round of Onitama
int Game::play_round() {
    Player* current_player = turn ? player1 : player2; // Whose turn is it?
    Card* selected_card = current_player -> make_move(board, renderer); // Figure out that player's move
    board -> swap_cards(selected_card); // Exchange their played card for the neutral card
    update_cards();
    turn = !turn; // Reverse the turn for next time
    board -> set_turn(turn); // Tell the board that we've switched sides

    return board -> get_game_status(); // Check if someone has won
}

// Play a full game of Onitama
Player* Game::play_game() {
    int maximum_number_of_rounds = -1;
    int number_of_rounds = 0;

    while(true) {
        if(SDL_QuitRequested()) {
            SDL_Quit();
        }
        if(visual_mode) {
            SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
            SDL_RenderClear(renderer);
            board -> draw(renderer);
            SDL_RenderPresent(renderer);
        }

        int round_result = play_round(); // Play another round
        switch(round_result) {
            case 0:
                break;
            case -1:
                return player1;
                break;
            case 1:
                return player2;
                break;
        }
        ++number_of_rounds;
        if(maximum_number_of_rounds >= 0 && number_of_rounds > maximum_number_of_rounds) { // Ensure that the game does not go on forever
            return player1;
        }
    }
    return nullptr;
}