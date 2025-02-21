#include "Bot.h"

Bot::Bot(int index_i) : Player(index_i) {

}

Bot::~Bot() {

}

Card* Bot::make_move(Board* board, SDL_Renderer* renderer) {
    return nullptr;
}

// Waits for a certain amount of time in milliseconds
void Bot::wait(int time) {
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
}