#include "MatrixBot.h"

MatrixBot::MatrixBot(int index_i) : Bot(index_i) {
    num_offspring = 0;
    std::vector<std::vector<float>> transition_matrix_i;

    for(int i = 0; i < 125; i++) {
        std::vector<float> row;
        for(int j = 0; j < 20; j++) {
            row.push_back((float)rand() / RAND_MAX); // Make random number between 0 and 1
        }
        transition_matrix_i.push_back(row);
    }

    transition_matrix = transition_matrix_i;
}

MatrixBot::MatrixBot(int index_i, std::vector<std::vector<float>> transition_matrix_i) : Bot(index_i) {
    num_offspring = 0;
    transition_matrix = transition_matrix_i;
}

MatrixBot::~MatrixBot() {

}

/*
This bot's input vector has the following archetecture:
x-position of my king
y-position of my king
x-position of my piece 1
y-position of my piece 1
x-position of my piece 2
y-position of my piece 2
x-position of my piece 3
y-position of my piece 3
x-position of my piece 4
y-position of my piece 5
x-position of enemy king
y-position of enemy king
x-position of enemy piece 1
y-position of enemy piece 1
x-position of enemy piece 2
y-position of enemy piece 2
x-position of enemy piece 3
y-position of enemy piece 3
x-position of enemy piece 4
y-position of enemy piece 5
*/

// Assemble the input vector from the board layout
std::vector<float> MatrixBot::get_input_vector() {
    std::vector<float> input_vector;

    // Piece data
    for(Piece* p : my_pieces) {
        if(!p->get_is_king()) {
            continue;
        }
        input_vector.push_back((float)p -> get_x());
        input_vector.push_back((float)p -> get_y());
        break;
    }
    for(Piece* p : my_pieces) {
        if(p -> get_is_king()) {
            continue;
        }
        input_vector.push_back((float)p -> get_x());
        input_vector.push_back((float)p -> get_y());
    }
    for(Piece* p : enemy_pieces) {
        if(!p->get_is_king()) {
            continue;
        }
        input_vector.push_back((float)p -> get_x());
        input_vector.push_back((float)p -> get_y());
        break;
    }
    for(Piece* p : enemy_pieces) {
        if(p -> get_is_king()) {
            continue;
        }
        input_vector.push_back((float)p -> get_x());
        input_vector.push_back((float)p -> get_y());
    }

    return input_vector;
}

// Multiply the input vector by the transition matrix
std::vector<float> MatrixBot::get_output_vector() {
    std::vector<float> input_vector = get_input_vector();
    std::vector<float> output_vector;
    if(transition_matrix.size() == 0 || input_vector.size() != transition_matrix.at(0).size()) {
        printf("Invalid matrix size.\n");
        return output_vector;
    }
    for(long unsigned int i = 0; i < transition_matrix.size(); i++) { // This is simple matrix multiplication
        output_vector.push_back(0);
        for(long unsigned int j = 0; j < transition_matrix.at(i).size(); j++) {
            output_vector.at(i) += input_vector.at(j) * transition_matrix.at(i).at(j);
        }
    }
    
    return output_vector;
}


Piece* MatrixBot::get_piece_from_index(long unsigned int index) {
    return my_pieces.at(index/25);
}

move MatrixBot::get_move_from_index(long unsigned int index) {
    int x = (index%25)/5 - get_piece_from_index(index)->get_x();
    int y = index%5 - get_piece_from_index(index)->get_y();
    return {x, y};
}

/*
This bot decides the optimal move by taking stock of the board
and running this data through a transition matrix to find the
relative weight of all possible moves, then picks the highest-
weighted legal move.
*/
Card* MatrixBot::make_move(Board* board, SDL_Renderer* renderer) {
    wait(2000);

    SDL_Event e;
    SDL_PollEvent(&e);
    if(e.type == SDL_QUIT) {
        SDL_Quit();
    }

    // Find the highest-weight legal move
    std::vector<float> weights = get_output_vector();
    float w = -100;
    Card* c;
    Piece* p;
    move m;

    for(long unsigned int i = 0; i < weights.size(); i++) {
        if(weights.at(i) <= w) {
            continue;
        }
        for(Card* card : my_cards) {
            if(is_legal_move(card, get_piece_from_index(i), get_move_from_index(i))) {
                w = weights.at(i);
                c = card;
                p = get_piece_from_index(i);
                m = get_move_from_index(i);
            }
        }
    }

    p -> make_move(m); // Move the piece
    check_kill(p); // Check if the piece has killed something

    return c;
}

MatrixBot* MatrixBot::produce_offspring() {
    float randomization_margin = 0.125;
    std::vector<std::vector<float>> new_transition_matrix;
    for(long unsigned int i = 0; i < transition_matrix.size(); i++) {
        std::vector<float> row;
        for(long unsigned int j = 0; j < transition_matrix.at(i).size(); j++) {
            int val = transition_matrix.at(i).at(j); // Get current value
            val += (2*((float)rand()/RAND_MAX) - 1) * randomization_margin; // Randomize a little
            row.push_back(val);
        }
        new_transition_matrix.push_back(row);
    }
    num_offspring++;
    return new MatrixBot(index * num_offspring, new_transition_matrix);
}