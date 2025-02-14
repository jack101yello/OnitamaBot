#ifndef __bot_H
#define __bot_H

#include <chrono>
#include <thread>
#include "../Player/player.h"

class Bot : public Player {
    public:
        Bot(int index_i);
        ~Bot();
        virtual Card* make_move(Board* board, SDL_Renderer* renderer);
        void wait(int time);

    friend class ImpatientBot;
};

#endif