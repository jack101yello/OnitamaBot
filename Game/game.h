#ifndef __game_H
#define __game_H

#include <SDL2/SDL.h>
#include "../Player/player.h"
#include "../Board/board.h"

class Game {
    private:
        Player* player1;
        Player* player2;
        Board* board;
        bool turn;
        bool visual_mode;
        SDL_Renderer* renderer;

    public:
        Game(Player* player1_i, Player* player2_i, int square_size, SDL_Renderer* renderer_i);
        ~Game();
        int play_round();
        Player* play_game();
        void set_visual_mode(bool visual_mode_i) {visual_mode = visual_mode_i; };
        void telemetry_dump(int mode);
        void update_cards();
};

#endif