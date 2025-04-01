#include "textbox.h"

#ifdef VISUAL_MODE

Textbox::Textbox(int x_i, int y_i, int w_i, int h_i, unsigned char r_i, unsigned char g_i, unsigned char b_i, unsigned char tr_i, unsigned char tg_i, unsigned char tb_i, const char* message_i) {
    rect = {x_i, y_i, w_i, h_i};
    box_color = {r_i, g_i, b_i, 0xff};
    text_color = {tr_i, tg_i, tb_i, 0xff};
    message = message_i;

    TTF_Font* f = TTF_OpenFont("Data/Fonts/Times New Roman.ttf", 24);
    font = f;
}

Textbox::~Textbox() {

}

void Textbox::draw(SDL_Renderer* renderer) {
    // Draw box
    SDL_SetRenderDrawColor(renderer, box_color.r, box_color.g, box_color.b, box_color.a);
    SDL_RenderFillRect(renderer, &rect);

    // Draw text
    SDL_Surface* text_surface = TTF_RenderText_Solid(font, message, text_color);
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, text_texture, NULL, &rect);
}

#endif