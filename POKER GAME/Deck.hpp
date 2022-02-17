
#ifndef Deck_hpp
#define Deck_hpp

#include <stdio.h>
#include "Card.hpp"
#include <vector>
#include <algorithm>


namespace ECE17 {

    class Deck {

    public:

       

        Deck();
        Deck(const Deck &aDeck);
        ~Deck();
        Deck& operator=(const Deck &aDeck);

        bool pop(Card &aCard); //remove card from top of deck
        bool push(const Card &aCard); //add card to bottom of deck
        bool isEmpty() const; //true if the deck contains 0 cards

        void shuffle(); //randomize cards in deck...
        std::vector <Card>  deckofCards;
    protected:

      

    };

}


#endif /* Deck_hpp */
