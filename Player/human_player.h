#ifndef __human_player_H
#define __human_player_H

#include <SDL2/SDL.h>
#include "player.h"
#include "../Board/board.h"
#include "../Textbox/textbox.h"
#include "../Button/button.h"

class Human_Player : public Player {
    private:

    public:
        Human_Player();
        ~Human_Player();
        Card* make_move(Board* board, SDL_Renderer* renderer);
};

#endif