//
//  Game.hpp
//  assignment7
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include <vector>
#include "Player.hpp"

namespace ECE17 {
      
  using Players = std::vector<Player*>;

  //student -- declare the Game class here...
  class Game {
  public:
            Game(size_t aCardCount=5, float aMinimumBet=5.0);
            Game(const Game &aCopy);
            ~Game();
            Game& operator=(const Game &aCopy);

    bool    addPlayer(Player &aPlayer);
   
    bool    willRun();
    bool    run(float anAnte, std::ostream &anOutput);
    bool    didRun(bool aRunStatus, const std::string &anOutput);
        
  protected:
          
    Game&   payWinner(const std::string &aPlayerName);

    Players players;
    float   minBet;
    size_t  cardCount;
        
  };

}

#endif /* Game_hpp */
