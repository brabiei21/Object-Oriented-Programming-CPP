
#ifndef Hand_hpp
#define Hand_hpp

#include <stdio.h>
#include "Card.hpp"
#include "Deck.hpp"
#include <vector>
#include <algorithm>


namespace ECE17 {
  
  enum class HandTypes {
    unknown=0, high_card=1, one_pair=2, two_pair=3, three_kind=4, straight=5,
    flush=6, full_house=7, four_kind=8, straight_flush=9, royal_flush=10
  };


    class Hand {
    public:

        Hand();
        Hand(const Hand &aCopy);

        ~Hand();
        Hand& operator=(const Hand &aCopy);

        Hand&      add(const Card& aCard);
        bool        discard(const Card &aCard);


        bool        RoyalFlush() const;
        bool        StraightFlush() const;
        bool        FourOfAKind() const;
        bool        FullHouse() const;
        bool        Flush() const;
        bool        Straight() const;
        bool        ThreeOfAKind() const;
        bool        TwoPair() const;
        bool        OnePair() const;
        bool        HighCard() const;


        bool        isSameSuit() const
        {
            Suits firstSuit = ourHand[0].getSuit();
            for (int i = 0; i < ourHand.size(); i++)
            {
                if (ourHand[i].getSuit() != firstSuit)
                    return false;
            }
            return true;

        }  //This checks if you hand has all the same suits

        bool        isSequence() const
        {
            std::vector <int> temp;
            int holder;
            for(int i = 0; i < ourHand.size(); i++)
            {
                temp.push_back(static_cast <int> (ourHand[i].getFace()));
            }
            std::sort (temp.begin(), temp.end());
            holder = temp[0];
            int dif;
            for (int i = 1; i < temp.size(); i++)
            {
                dif = temp[i] - holder;
                if(1 < dif || 0 == dif)
                    return false;
                holder = temp[i];
            }
            return true;

        }

        HandTypes   determineRank() const; //what type hand is this?

        bool        operator>(const Hand &aHand) const;

        size_t      count();

        void        show(std::ostream &anOutput) const;

        std::vector <Card> ourHand;
    protected:

        //Deck someDeck;
    };

}


#endif /* Hand_hpp */
