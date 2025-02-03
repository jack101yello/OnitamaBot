#ifndef __card_H
#define __card_H

#include <vector>
#include <SDL2/SDL.h>
#include "../Types/types.h"

class Card {
    private:
        int index; // Makes referring to a card easier
        const char* name;
        card_color color;
        std::vector<move> moves;
        SDL_Surface* card_image_surface;

    public:
        Card(int index_i, const char* name_i, card_color color_i, const char* image_path_i);
        ~Card();
        SDL_Surface* get_image_surface() { return card_image_surface; }
        void add_move(move new_move);
        bool is_valid_move(move m);
        int get_index() { return index; }
        const char* get_name() { return name; }
        std::vector<move> get_moves() { return moves; }
        bool operator==(const Card& other) const {
            return this -> index == other.index;
        }
};

#endif