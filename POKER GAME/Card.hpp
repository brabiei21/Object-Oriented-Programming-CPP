
#ifndef Card_hpp
#define Card_hpp

#include <iostream>
#include <string>

namespace ECE17 {

  static const char* gFaces[]
    {"2","3","4","5","6","7","8","9","T","J","Q","K","A"};
  static const char* gSuits[]
    {"Spade","Club","Heart","Diamond"};

  enum class Suits  {spades=1, clubs, hearts, diamonds, nosuit=100};
  enum class Faces {two=2, three, four, five, six, seven, eight, nine, ten=10,
      jack=11, queen=12, king=13, ace=14, noface=100};

  static const char* gSymbols[] = {"S", "C", "H", "D"};
  //static const char* gSymbols[] = {"♠", "♣", "♥", "♦"}; // for mac

  static constexpr size_t suitCount() {
     return sizeof(gSuits)/sizeof(const char*);
   }

  static constexpr size_t faceCount() {
     return sizeof(gFaces)/sizeof(const char*);
   }

  //----------------------------

    class Card {
    public:

        Card(Suits aSuit=Suits::nosuit, Faces aFace=Faces::noface);
        Card(const Card& aCard);
        ~Card();
        void setCard(Faces newFace, Suits newSuit)
        {
            face = newFace;
            suit = newSuit;
        };

        Card& operator=(const Card &aCard);
        bool  operator==(const Card &aCard) const;
        bool  operator<=(const Card &aCard) const;
        std::string GetSuitSymbol() const;
        std::string GetFaceName() const;

        Faces getFace() const {return face;}
        Suits getSuit() const {return suit;}

        bool DoesCardMatch(const Card &a_card) const
        {
            if( face == a_card.face &&
                suit == a_card.suit )
                return true;
            else
                return false;
        }

        friend std::ostream& operator<<(
                std::ostream &anOutput, const Card &aCard);

    protected:
        Suits suit;
        Faces face;
    };


}
#endif /* Card_hpp */
