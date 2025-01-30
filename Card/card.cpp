#include "card.h"

Card::Card(int index_i, const char* name_i, card_color color_i, const char* image_path_i) {
    index = index_i;
    name = name_i;
    color = color_i;
    card_image_surface = SDL_LoadBMP(image_path_i);
}

Card::~Card() {
    
}

void Card::add_move(move new_move) {
    moves.push_back(new_move);
}