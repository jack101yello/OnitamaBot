#ifndef __button_H
#define __button_H

#include "../../modes.h"

#ifdef VISUAL_MODE
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#endif

#include "../Textbox/textbox.h"

class Button {
    #ifdef VISUAL_MODE
    private:
        Textbox* textbox;

    public:
        Button(int x_i, int y_i, int w_i, int h_i, const char* message_i);
        ~Button();
        void draw(SDL_Renderer* renderer);
        bool in_click_range(int click_x, int click_y);
    #endif
};

#endif