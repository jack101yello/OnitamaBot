#ifndef __matrixbot_H
#define __matrixbot_H

#include <iostream>
#include <fstream>
#include "../Bot.h"

class MatrixBot : public Bot {
    private:
        int num_offspring;
        std::vector<std::vector<float>> transition_matrix;
        std::vector<float> get_input_vector();
        std::vector<float> get_output_vector();
        move get_move_from_index(long unsigned int index);
        Piece* get_piece_from_index(long unsigned int index);
        
        public:
        MatrixBot(int index_i);
        MatrixBot(int index_i, std::vector<std::vector<float>> transition_matrix_i);
        MatrixBot(int index_i, const std::string& filename);
        ~MatrixBot();
        Card* make_move(Board* board, SDL_Renderer* renderer);
        MatrixBot* produce_offspring();
        void save_data(const std::string& filename);
        std::vector<std::vector<float>> read_data(const std::string& filename);
};

#endif