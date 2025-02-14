#ifndef __human_player_H
#define __human_player_H

#include <SDL2/SDL.h>
#include "../Player/player.h"
#include "../../Gameplay/Board/board.h"
#include "../../Graphics/Textbox/textbox.h"
#include "../../Graphics/Button/button.h"

class Human_Player : public Player {
    private:

    public:
        Human_Player(int index_i);
        ~Human_Player();
        Card* make_move(Board* board, SDL_Renderer* renderer);
};

#endif