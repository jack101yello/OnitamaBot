#ifndef __tournament_H
#define __tournament_H

#include <SDL2/SDL.h>
#include "../Game/game.h"
#include <vector>
#include <algorithm>
#include "../../Player/Bot/Bot.h"
#include "../../Player/Bot/MatrixBot/MatrixBot.h"

class Tournament {
    private:
        std::vector<MatrixBot*> scoreboard;

    public:
        Tournament(long unsigned int number_combatants);
        Tournament(long unsigned int number_combatants, long unsigned int number_saved, const std::string& data_dir);
        ~Tournament();
        void play_round(SDL_Renderer* renderer);
        void cull_losers();
        void repopulate_scoreboard();
};

#endif