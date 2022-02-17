//
//  Card.cpp
//  assignment7
//
#define SPADE_SYMBOL	"\u2660"
#define CLUB_SYMBOL    "\u2663"
#define HEART_SYMBOL   "\u2665"
#define DIAMOND_SYMBOL "\u2666"

#include "Card.hpp"
#include <iostream>
#include <iomanip>

namespace ECE17 {

    Card::Card(Suits aSuit, Faces aFace) : suit(aSuit), face(aFace){}
    Card::Card(const Card &aCard) : suit(aCard.suit), face(aCard.face){}

    Card& Card::operator=(const Card &aCard) {
        //implement me...
        suit = aCard.getSuit();
        face = aCard.getFace();

        return *this;
    }
    Card::~Card() {
        //implement me..
    }
    bool Card::operator==(const Card &aCard) const {
        //implement me...
        if(face != aCard.getFace())
            return false;

        return true;
    }
    bool Card::operator<=(const Card &aCard) const {
        //implement me...
        if(face <= aCard.getFace())
            return true;
        return false;
    }

    std::string Card::GetFaceName() const
    {
        switch(face) {
            case(Faces::ace):
                return "A";
            case(Faces::jack):
                return "J";
            case(Faces::queen):
                return "Q";
            case(Faces::king):
                return "K";
            case(Faces::two):
                return "2";
            case(Faces::three):
                return "3";
            case(Faces::four):
                return "4";
            case(Faces::five):
                return "5";
            case(Faces::six):
                return "6";
            case(Faces::seven):
                return "7";
            case(Faces::eight):
                return "8";
            case(Faces::nine):
                return "9";
            case(Faces::ten):
                return "10";
            case(Faces::noface):
                return "No Face";

        }
    }

    std::string Card::GetSuitSymbol() const
    {
        switch(suit) {
            case (Suits::spades):
                return SPADE_SYMBOL;
            case (Suits::diamonds):
                return DIAMOND_SYMBOL;
            case (Suits::hearts):
                return HEART_SYMBOL;
            case (Suits::clubs):
                return CLUB_SYMBOL;
        }
        return "";
    }

    //card version of stream inserter...
    std::ostream& operator<<(std::ostream &anOutput, const Card &aCard)
    {
        //implement me...
        //output card, e.g.:  3H  (you can use symbols too)
        anOutput << aCard.GetFaceName() << aCard.GetSuitSymbol() ;
        return anOutput;
    }
}


