#ifndef __human_player_H
#define __human_player_H

#include "player.h"
#include <SDL2/SDL.h>

class Human_Player : public Player {
    private:

    public:
        Human_Player();
        ~Human_Player();
        Card* make_move();
};

#endif