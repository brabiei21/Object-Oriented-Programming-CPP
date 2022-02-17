#include "Deck.hpp"

#include <algorithm>
#include <chrono>



 
namespace ECE17 {

    

    Deck::Deck()
    {
        

        Faces aFace;
        Suits aSuit;
        Card temp;

        for(int j = 1; j <= 4; j++)
        {
            for(int k= 2; k <= 14; k++)
            {
                aFace = (Faces) k;  //Type casting
                aSuit = (Suits) j;
                temp.setCard(aFace, aSuit);
                deckofCards.push_back(temp);
            }
        }
    }

    Deck::Deck(const Deck &aDeck)
    {
       

        for(int i = 0; i <52; i++)
        {
            deckofCards[i] = aDeck.deckofCards[i];
        }

    }

    Deck::~Deck()
    {
        
    }

    Deck& Deck::operator=(const Deck &aDeck)
    {
       

        for(int i = 0; i <52; i++)
        {
            deckofCards[i] = aDeck.deckofCards[i];
        }

        return *this;
    }


    void Deck::shuffle()
    {
        int random;
        Card temp;

        //random = rand() % (deckofCards.size() );
        //auto gen = std::default_random_engine(deckofCards.size());
        //std::shuffle(deckofCards.begin(),deckofCards.end(),gen);


        for(int i = 0; i < deckofCards.size(); i++)
        {
            random = rand() % (deckofCards.size() );

            temp = deckofCards[i];
            deckofCards[i] = deckofCards[random];
            deckofCards[random] = temp;
        }
    }

    //get top card on deck
    bool Deck::pop(Card &aCard)
    {
        if(deckofCards.empty())
            return false;

        aCard = deckofCards[deckofCards.size()-1];
        deckofCards.pop_back();
        return true;
    }

    //discard card back to deck...
    bool Deck::push(const Card &aCard)
    {
        if(deckofCards.size()>=52)
            return false;
        for(int i = 0 ; i < deckofCards.size(); i++)

        {
            if (deckofCards[i].getFace() == aCard.getFace() &&
                deckofCards[i].getSuit() == aCard.getSuit())
                return false;
        }

        deckofCards.push_back(aCard);
        return true;
    }

    bool Deck::isEmpty() const
    {
        
        if(deckofCards.empty())
            return true;
        return false;
    }
}
