#include "deck.h"

Deck::Deck() {
    // Add all of the cards and all of their parameters
    /* Need to implement move sets
    */
    // Ox
    Card* ox = new Card(0, "Ox", BLUE, "Data/Cards/BMP/Ox.bmp");
    cards.push_back(ox);
    Card* crab = new Card(1, "Crab", BLUE, "Data/Cards/BMP/Crab.bmp");
    cards.push_back(crab);
    Card* horse = new Card(2, "Horse", RED, "Data/Cards/BMP/Horse.bmp");
    cards.push_back(horse);
    Card* cobra = new Card(3, "Cobra", RED, "Data/Cards/BMP/Cobra.bmp");
    cards.push_back(cobra);
    Card* rabbit = new Card(4, "Rabbit", BLUE, "Data/Cards/BMP/Rabbit.bmp");
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
    // Implement this (there's probably a nice method for this)
}

std::vector<Card*> Deck::deal() {
    shuffle();
    std::vector<Card*> resulting_cards;
    for(int i = 0; i < 5; i++) {
        if(i >= cards.size()) {
            break;
        }
        resulting_cards.push_back(cards.at(i));
    }
    return resulting_cards;
}