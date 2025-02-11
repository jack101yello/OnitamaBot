#include "human_player.h"

Human_Player::Human_Player(int index_i) : Player(index_i) {

}

Human_Player::~Human_Player() {

}

/*
All of the logic for making a move.
This method returns a pointer to the card that was selected.
It should also implicitly move the piece that was moved.
*/
Card* Human_Player::make_move(Board* board, SDL_Renderer* renderer) {
    Button restart_turn_button(board->get_board_x()+6*board->get_square_size(), board->get_board_y() + board->get_square_size()*6, 300, 50, "Restart Turn");
    restart_turn_button.draw(renderer);

    bool waiting_for_card = true;
    int MouseX = 0;
    int MouseY = 0;

    Card* chosen_card = nullptr;

    Textbox textbox(board -> get_board_x(), board->get_board_y() + board->get_square_size()*6, 300, 50, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, "Select a Card");
    textbox.draw(renderer);
    SDL_RenderPresent(renderer);

    while(waiting_for_card) {
        SDL_Event event;
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_MOUSEMOTION:
                MouseX = event.motion.x;
                MouseY = event.motion.y;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(restart_turn_button.in_click_range(MouseX, MouseY)) {
                    return make_move(board, renderer); // Start the turn over
                }
                if(board -> card_clicked(MouseX, MouseY, true)) { // Left card clicked
                    chosen_card = my_cards.at(0);
                    waiting_for_card = false;
                }
                else if(board -> card_clicked(MouseX, MouseY, false)) { // Right card clicked
                    chosen_card = my_cards.at(1);
                    waiting_for_card = false;
                }
                break;
            case SDL_QUIT:
                SDL_Quit();
                break;
        }
    }

    bool waiting_for_piece = true;

    Piece* chosen_piece;

    textbox.change_message("Select a Piece");
    textbox.draw(renderer);
    SDL_RenderPresent(renderer);

    while(waiting_for_piece) {
        SDL_Event event;
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_MOUSEMOTION:
                MouseX = event.motion.x;
                MouseY = event.motion.y;
                break;
            case SDL_MOUSEBUTTONDOWN:
            {
                if(restart_turn_button.in_click_range(MouseX, MouseY)) {
                    return make_move(board, renderer); // Start the turn over
                }
                int chosen_x = 4 - (board -> get_square_from_mouse(MouseX, MouseY).x);
                int chosen_y = 4 - (board -> get_square_from_mouse(MouseX, MouseY).y);

                for(Piece* p : my_pieces) { // Iterate through my pieces to see if any have that position
                    if(p -> get_x() == chosen_x && p -> get_y() == chosen_y && p -> get_is_alive()) {
                        chosen_piece = p;
                        waiting_for_piece = false;
                    }
                }
                break;
            }
            case SDL_QUIT:
                SDL_Quit();
                break;
        }
    }

    bool waiting_for_move = true;

    textbox.change_message("Select a Space");
    textbox.draw(renderer);
    SDL_RenderPresent(renderer);

    while(waiting_for_move) {
        SDL_Event event;
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_MOUSEMOTION:
                MouseX = event.motion.x;
                MouseY = event.motion.y;
                break;
            case SDL_MOUSEBUTTONDOWN:
            {
                if(restart_turn_button.in_click_range(MouseX, MouseY)) {
                    return make_move(board, renderer); // Start the turn over
                }
                int chosen_x = 4 - (board -> get_square_from_mouse(MouseX, MouseY).x);
                int chosen_y = 4 - (board -> get_square_from_mouse(MouseX, MouseY).y);

                move m = {chosen_x - chosen_piece->get_x(), chosen_y - chosen_piece->get_y()};

                #ifdef DEBUGGING_MODE
                printf("Move is (%d, %d)\n", m.x, m.y);
                #endif

                // Check that the move is legal
                if(!is_legal_move(chosen_card, chosen_piece, m)) {
                    printf("Invalid move.\n");
                    return make_move(board, renderer); // Start the turn over
                }

                chosen_piece -> make_move(m);
                check_kill(chosen_piece); // Kill any opposing pieces which were there
                waiting_for_move = false;
                break;
            }
            case SDL_QUIT:
                SDL_Quit();
                break;
        }
    }
    return chosen_card;
}