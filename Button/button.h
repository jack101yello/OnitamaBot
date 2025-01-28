#ifndef __button_H
#define __button_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../Textbox/textbox.h"

class Button {
    private:
        Textbox* textbox;

    public:
        Button(int x_i, int y_i, int w_i, int h_i, const char* message_i, TTF_Font* font);
        ~Button();
        void draw(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font);
        bool in_click_range(int click_x, int click_y);
};

#endif