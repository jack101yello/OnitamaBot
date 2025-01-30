#ifndef __deck_H
#define __deck_H

#include <vector>
#include "card.h"
#include "../Types/types.h"

class Deck {
    private:
        std::vector<Card*> cards;
    
    public:
        Deck();
        ~Deck();
        void shuffle();
        std::vector<Card*> deal();
};

#endif