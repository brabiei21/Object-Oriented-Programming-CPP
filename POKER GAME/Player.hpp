//
//  AutoPlayer.hpp
//  assignment7
//
//  Created by rick gessner on 11/23/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include <string>
#include "Hand.hpp"

namespace ECE17 {
  
  class Player {
  public:
    
    Player(const std::string &aName="");
    Player(const Player &aPlayer);
    ~Player();
    Player& operator=(const Player &aPlayer);
      
    void          setBalance(float aValue);
    float         getBalance() const;
    
    const Hand&   getHand() const;
    void          setHand(const Hand &aHand);

    const std::string&  getName() const;
    
    bool          isFolding() const;
    float         placeBet(float aMinBet);
    size_t        discardUnwanted();
    
    void          drawCards(Deck &aDeck, size_t aMaxCount);
      Hand        hand;
    
  protected:
    
    std::string name;
    float       balance;

  };

}
 
#endif /* Player_hpp */
