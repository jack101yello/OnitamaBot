#include "board.h"


// Board constructor
Board::Board(int square_size_i) {
    square_size = square_size_i;
    board_x = 25;
    board_y = 25;

    player1_pieces.push_back(new Piece(2, 0, square_size, true, false, board_x, board_y));
    player1_pieces.push_back(new Piece(0, 0, square_size, false, false, board_x, board_y));
    player1_pieces.push_back(new Piece(1, 0, square_size, false, false, board_x, board_y));
    player1_pieces.push_back(new Piece(3, 0, square_size, false, false, board_x, board_y));
    player1_pieces.push_back(new Piece(4, 0, square_size, false, false, board_x, board_y));
    player2_pieces.push_back(new Piece(2, 0, square_size, true, true, board_x, board_y));
    player2_pieces.push_back(new Piece(0, 0, square_size, false, true, board_x, board_y));
    player2_pieces.push_back(new Piece(1, 0, square_size, false, true, board_x, board_y));
    player2_pieces.push_back(new Piece(3, 0, square_size, false, true, board_x, board_y));
    player2_pieces.push_back(new Piece(4, 0, square_size, false, true, board_x, board_y));

    deck = new Deck();
    deck -> shuffle();
    std::vector<Card*> active_cards = deck -> deal();
    player1_cards.push_back(active_cards.at(0));
    player1_cards.push_back(active_cards.at(1));
    player2_cards.push_back(active_cards.at(2));
    player2_cards.push_back(active_cards.at(3));
    neutral_card = active_cards.at(4);

    turn = true;
}

// Board destructor
Board::~Board() {
    for(Piece* p : player1_pieces) {
        delete p;
    }
    player1_pieces.clear();
    for(Piece* p : player2_pieces) {
        delete p;
    }
    player2_pieces.clear();
}

// Draw the board to the screen
void Board::draw(SDL_Renderer* renderer) {
    // Draw board
    SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0xff);
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            SDL_Rect square_rect = {i * square_size + board_x, j * square_size + board_y, square_size, square_size};
            SDL_RenderDrawRect(renderer, &square_rect);
        }
    }

    // Draw pieces
    for(long unsigned int i = 0; i < player1_pieces.size(); i++) {
        player1_pieces.at(i) -> draw(renderer, turn);
        player2_pieces.at(i) -> draw(renderer, !turn);
    }

    // Draw the cards
    // P1 card 1
    int card_width = (int)(2 * square_size);
    int card_height = (int)(1.5 * square_size);
    int card_horizontal_gap = (int)(card_width + 0.5 * square_size);
    int card_vertical_gap = (int)(card_height + 0.125 * square_size);
    int card_left_gap = (int)(0.25 * square_size);
    int card_area_start = board_x + 5*square_size;
    SDL_Texture* card_image_texture = SDL_CreateTextureFromSurface(renderer, player1_cards.at(0) -> get_image_surface());
    SDL_Rect r = {card_area_start + card_left_gap, board_y, card_width, card_height};
    SDL_RenderCopy(renderer, card_image_texture, NULL, &r);
    
    // P1 card 2
    card_image_texture = SDL_CreateTextureFromSurface(renderer, player1_cards.at(1) -> get_image_surface());
    r = {card_area_start + card_left_gap + card_horizontal_gap, board_y, card_width, card_height};
    SDL_RenderCopy(renderer, card_image_texture, NULL, &r);

    // P2 card 1
    card_image_texture = SDL_CreateTextureFromSurface(renderer, player2_cards.at(0) -> get_image_surface());
    r = {card_area_start + card_left_gap, board_y + 2 * card_vertical_gap, card_width, card_height};
    SDL_RenderCopy(renderer, card_image_texture, NULL, &r);
    
    // P2 card 2
    card_image_texture = SDL_CreateTextureFromSurface(renderer, player2_cards.at(1) -> get_image_surface());
    r = {card_area_start + card_left_gap + card_horizontal_gap, board_y + 2 * card_vertical_gap, card_width, card_height};
    SDL_RenderCopy(renderer, card_image_texture, NULL, &r);

    // Neutral card
    card_image_texture = SDL_CreateTextureFromSurface(renderer, neutral_card -> get_image_surface());
    r = {card_area_start + card_left_gap + (int)(0.25 * (card_width + card_horizontal_gap)), board_y + card_vertical_gap, card_width, card_height};
    SDL_RenderCopy(renderer, card_image_texture, NULL, &r);
}

// Swap the passed card with the neutral card
void Board::swap_cards(Card* selected_card) {
    Card* temp = neutral_card;
    neutral_card = selected_card;
    if(selected_card == player1_cards.at(0)) {
        player1_cards.at(0) = temp;
    }
    else if(selected_card == player1_cards.at(1)) {
        player1_cards.at(1) = temp;
    }
    else if(selected_card == player2_cards.at(0)) {
        player2_cards.at(0) = temp;
    }
    else if(selected_card == player2_cards.at(1)) {
        player2_cards.at(1) = temp;
    }
    else {
        printf("An error has occurred during the card swap.\n");
    }
}

/*
Return value:
0 - Game continuing
-1 - Player 1 victory
1 - Player 2 victory
*/
int Board::get_game_status() {
    /*
    This method is to be implemented
    */
   return 0;
}