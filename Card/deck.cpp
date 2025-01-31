#include "deck.h"

Deck::Deck() {
    // Add all of the cards and all of their parameters
    /* Need to implement move sets
    */
    // Ox
    Card* ox = new Card(0, "Ox", BLUE, "Data/Cards/BMP/Ox.bmp");
    ox -> add_move({0, -1});
    ox -> add_move({1, 0});
    ox -> add_move({0, 1});
    cards.push_back(ox);
    Card* crab = new Card(1, "Crab", BLUE, "Data/Cards/BMP/Crab.bmp");
    crab -> add_move({-2, 0});
    crab -> add_move({0, -1});
    crab -> add_move({2, 0});
    cards.push_back(crab);
    Card* horse = new Card(2, "Horse", RED, "Data/Cards/BMP/Horse.bmp");
    horse -> add_move({-1, 0});
    horse -> add_move({0, -1});
    horse -> add_move({0, 1});
    cards.push_back(horse);
    Card* cobra = new Card(3, "Cobra", RED, "Data/Cards/BMP/Cobra.bmp");
    cobra -> add_move({-1, 0});
    cobra -> add_move({1, -1});
    cobra -> add_move({1, 1});
    cards.push_back(cobra);
    Card* rabbit = new Card(4, "Rabbit", BLUE, "Data/Cards/BMP/Rabbit.bmp");
    rabbit -> add_move({-1, 1});
    rabbit -> add_move({1, -1});
    rabbit -> add_move({2, 0});
    cards.push_back(rabbit);
}

Deck::~Deck() {
    for(Card* c : cards) {
        delete c;
    }
    cards.clear();
}

// Shuffle the deck
void Deck::shuffle() {
    auto rd = std::random_device {};
    auto rng = std::default_random_engine { rd() };
    std::shuffle(std::begin(cards), std::end(cards), rng);
}

std::vector<Card*> Deck::deal() {
    shuffle();
    std::vector<Card*> resulting_cards;
    for(long unsigned int i = 0; i < 5; i++) {
        if(i >= cards.size()) {
            break;
        }
        resulting_cards.push_back(cards.at(i));
    }
    return resulting_cards;
}