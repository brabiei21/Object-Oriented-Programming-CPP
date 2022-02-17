
#include "Player.hpp"

namespace ECE17 {

  Player::Player(const std::string &aName)
    : name(aName), balance(0.0) {}
  
  Player::Player(const Player &aCopy)
    : name(aCopy.name), balance(aCopy.balance) {}
  
  Player& Player::operator=(const Player &aCopy) {
    name=aCopy.name;
    return *this;
  }

  Player::~Player() {}
  
  void  Player::setBalance(float aBalance) {balance=aBalance;}
  float Player::getBalance() const {return balance;}

  const Hand& Player::getHand() const {return hand;}
  void  Player::setHand(const Hand &aHand) {hand=aHand;}

  const std::string& Player::getName() const  {return name;}

  bool  Player::isFolding() const
  {
    if(hand.determineRank() > HandTypes::high_card)
    return false;

    return true;
  }

  float Player::placeBet(float aMinBet)
  {
      
      float amount;
      if(hand.determineRank() > HandTypes::full_house && balance >= aMinBet)
      {   amount = balance;
          balance =0;
          return amount;
      }


      if(balance >= aMinBet)
      {
          amount = aMinBet;
          balance-= aMinBet;
          return amount;
      }


      return 0;
  }

  void  Player::drawCards(Deck &aDeck, size_t aMaxCount)
  {
    
    Card temp;
    for(int i = 0; i < aMaxCount; i++)
    {
        aDeck.pop(temp);
        if(hand.count() < 5)
        hand.add(temp);
    }
  }


  size_t Player::discardUnwanted()
  {
    
    if(hand.determineRank() == HandTypes::high_card)
    {
        for (int i = 0; i < hand.count(); i++)
        {
            if(static_cast<int>(hand.ourHand[i].getFace()) < 9)
                hand.discard(hand.ourHand[i]);
        }
    }
    return hand.count();
  }

}
