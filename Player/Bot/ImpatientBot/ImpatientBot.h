#ifndef __impatientbot_H
#define __impatientbot_H

#include "../../Player/player.h"
#include "../Bot.h"

class ImpatientBot : public Bot {
    public:
        ImpatientBot(int index_i);
        ~ImpatientBot();
        Card* make_move(Board* board, SDL_Renderer* renderer);
};

#endif