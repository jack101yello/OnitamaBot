#ifndef __textbox_H
#define __textbox_H

#include "../../modes.h"

#ifdef VISUAL_MODE
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#endif

class Textbox {
    #ifdef VISUAL_MODE
    private:
        SDL_Rect rect;
        SDL_Color box_color;
        SDL_Color text_color;
        const char* message;
        TTF_Font* font;
    
    public:
        Textbox(int x_i, int y_i, int w_i, int h_i, unsigned char r_i, unsigned char g_i, unsigned char b_i, unsigned char tr_i, unsigned char tg_i, unsigned char tb_i, const char* message_i);
        ~Textbox();
        void draw(SDL_Renderer* renderer);
        int get_x() { return rect.x; }
        int get_y() { return rect.y; }
        int get_w() { return rect.w; }
        int get_h() { return rect.h; }
        void change_message(const char* message_i) { message = message_i; }
    #endif
};

#endif