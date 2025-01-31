#include "human_player.h"

Human_Player::Human_Player() {

}

Human_Player::~Human_Player() {

}

Card* Human_Player::make_move() {
    bool waiting_for_move = true;
    while(waiting_for_move) {
        SDL_Event event;
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_MOUSEBUTTONDOWN:
                waiting_for_move = false;
                break;
            case SDL_QUIT:
                SDL_Quit();
                break;
        }
    }
    return my_cards.at(0);
}