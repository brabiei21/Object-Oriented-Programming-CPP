//
//  Testing.hpp
//  assignment7
//

#ifndef Testing_h
#define Testing_h

#include "Card.hpp"
#include "Deck.hpp"

using namespace ECE17;

//----------------------------------------------

Hand getRandomHand(Deck &aDeck) {
  Hand theHand;
  
  for(int i=0;i<5;i++) {
    Card theCard;
    aDeck.pop(theCard);
    theHand.add(theCard);
  }
  return theHand;
}

Hand getHighCard() {
  Hand theHand;
  theHand.add(Card(Suits::hearts,Faces::two));
  theHand.add(Card(Suits::diamonds,Faces::four));
  theHand.add(Card(Suits::spades,Faces::seven));
  theHand.add(Card(Suits::clubs,Faces::nine));
  theHand.add(Card(Suits::hearts,Faces::jack));
  return theHand;
}

Hand getOnePair() {
  Hand theHand;
  theHand.add(Card(Suits::hearts,Faces::five));
  theHand.add(Card(Suits::diamonds,Faces::five));
  theHand.add(Card(Suits::spades,Faces::seven));
  theHand.add(Card(Suits::clubs,Faces::nine));
  theHand.add(Card(Suits::hearts,Faces::jack));
  return theHand;
}

Hand getTwoPair() {
  Hand theHand;
  theHand.add(Card(Suits::hearts,Faces::five));
  theHand.add(Card(Suits::diamonds,Faces::five));
  theHand.add(Card(Suits::spades,Faces::seven));
  theHand.add(Card(Suits::clubs,Faces::seven));
  theHand.add(Card(Suits::hearts,Faces::jack));
  return theHand;
}

Hand getThreeOfAKind() {
  Hand theHand;
  theHand.add(Card(Suits::hearts,Faces::five));
  theHand.add(Card(Suits::diamonds,Faces::five));
  theHand.add(Card(Suits::spades,Faces::five));
  theHand.add(Card(Suits::clubs,Faces::seven));
  theHand.add(Card(Suits::hearts,Faces::jack));
  return theHand;
}

Hand getStraight() {
  Hand theHand;
  theHand.add(Card(Suits::hearts,Faces::five));
  theHand.add(Card(Suits::diamonds,Faces::six));
  theHand.add(Card(Suits::spades,Faces::seven));
  theHand.add(Card(Suits::clubs,Faces::eight));
  theHand.add(Card(Suits::hearts,Faces::nine));
  return theHand;
}

Hand getFlush() {
  Hand theHand;
  theHand.add(Card(Suits::hearts,Faces::three));
  theHand.add(Card(Suits::hearts,Faces::six));
  theHand.add(Card(Suits::hearts,Faces::seven));
  theHand.add(Card(Suits::hearts,Faces::nine));
  theHand.add(Card(Suits::hearts,Faces::jack));
  return theHand;
}

Hand getFullHouse() {
  Hand theHand;
  theHand.add(Card(Suits::hearts,Faces::five));
  theHand.add(Card(Suits::diamonds,Faces::five));
  theHand.add(Card(Suits::spades,Faces::five));
  theHand.add(Card(Suits::clubs,Faces::seven));
  theHand.add(Card(Suits::hearts,Faces::seven));
  return theHand;
}

Hand getFourOfAKind() {
  Hand theHand;
  theHand.add(Card(Suits::hearts,Faces::five));
  theHand.add(Card(Suits::diamonds,Faces::five));
  theHand.add(Card(Suits::spades,Faces::five));
  theHand.add(Card(Suits::clubs,Faces::five));
  theHand.add(Card(Suits::hearts,Faces::seven));
  return theHand;
}

Hand getStraightFlush() {
  Hand theHand;
  theHand.add(Card(Suits::hearts,Faces::three));
  theHand.add(Card(Suits::hearts,Faces::four));
  theHand.add(Card(Suits::hearts,Faces::five));
  theHand.add(Card(Suits::hearts,Faces::six));
  theHand.add(Card(Suits::hearts,Faces::seven));
  return theHand;
}

Hand getRoyalFlush() {
  Hand theHand;
  theHand.add(Card(Suits::hearts,Faces::ten));
  theHand.add(Card(Suits::hearts,Faces::jack));
  theHand.add(Card(Suits::hearts,Faces::queen));
  theHand.add(Card(Suits::hearts,Faces::king));
  theHand.add(Card(Suits::hearts,Faces::ace));
  return theHand;
}

//-----------------------------------------------------

//make a hand that corresponds to the given type...
bool validateRank(HandTypes aType, const Hand& aHand, const char *aMsg) {
  if(aType!=aHand.determineRank()) {
    std::cout << "Determine rank for " << aMsg << " failed\n";
    return false;
  }
  return true;
}

bool validateRanks() {

  if(!validateRank(HandTypes::high_card, getHighCard(), "high-card")) {
    return false;
  }

  if(!validateRank(HandTypes::one_pair,  getOnePair(), "one-pair")) {
    return false;
  }

  if(!validateRank(HandTypes::two_pair,  getTwoPair(), "two-pair")) {
    return false;
  }

  if(!validateRank(HandTypes::three_kind, getThreeOfAKind(),"three-kind")) {
    return false;
  }

  if(!validateRank(HandTypes::straight,  getStraight(),"straight")) {
    return false;
  }

  if(!validateRank(HandTypes::flush,  getFlush(),"flush")) {
    return false;
  }
    
  if(!validateRank(HandTypes::full_house,  getFullHouse(),"full-house")) {
    return false;
  }

  if(!validateRank(HandTypes::four_kind,  getFourOfAKind(),"four-kind")) {
    return false;
  }

  if(!validateRank(HandTypes::straight_flush,  getStraightFlush(),"straight")) {
    return false;
  }
           
  if(!validateRank(HandTypes::royal_flush,  getRoyalFlush(),"royal-flush")) {
    std::cout << "Determine rank for royal-flush failed\n";
    return false;
  }

  return true;
}

//confirm that deck shuffle produces unique results...
bool shuffleTest() {
  Deck theDeck1;
  theDeck1.shuffle();
  Card theCard;

  std::stringstream theOutput1;

  while(theDeck1.pop(theCard)) {
    theOutput1 << theCard;
  }

  Deck theDeck2;
  theDeck2.shuffle();

  std::stringstream theOutput2;

  while(theDeck2.pop(theCard)) {
    theOutput2 << theCard;
  }
  
  std::string theStr1=theOutput1.str();
  std::string theStr2=theOutput2.str();
    
  return theStr1.size()>0 && (theStr1!=theStr2);
}

bool compareCards() {

  srand((unsigned)time(NULL));

  for(int i=0;i<1000;i++) {
    size_t theRand1=2+((rand() % 13));
    size_t theRand2=2+((rand() % 13));
    Faces theFace1=static_cast<Faces>(theRand1);
    Faces theFace2=static_cast<Faces>(theRand2);
    Card theCard1(Suits::hearts, theFace1);
    Card theCard2(Suits::hearts, theFace2);

    if(theRand1<=theRand2) {
      if(theCard1<=theCard2) {}
      else {
        std::cout << "Comparison error: (" << theRand1 << "," << theRand2 << ")\n";
        return false;
      }
    }
    else {
      if(theCard1<=theCard2) {
        std::cout << "Comparison error: (" << theRand1 << "," << theRand2 << ")\n";
        return false;
      }
    }
  }
    
  return true;
}

#endif /* Testing_h */
