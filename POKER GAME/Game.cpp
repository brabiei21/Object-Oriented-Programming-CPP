
#include "Game.hpp"
#include "Hand.hpp"
#include "Card.hpp"
#include "Round.hpp"
#include <sstream>
#include <algorithm>

namespace ECE17 {
  
  const float kStartingBalance=1000.00;

  Game::Game(size_t aCardCount, float aMinBet) {
    cardCount=aCardCount;
    minBet=aMinBet;
  }

  Game::Game(const Game &aCopy)  {
    std::cout << "Game ctor(copy)\n";
  }

  Game& Game::operator=(const Game &aCopy) {
    return *this;
  }

  Game::~Game() {
  }

  bool Game::addPlayer(Player &aPlayer) {
    //can have other data types instead of int but must same datatype as item
    if(std::find(players.begin(), players.end(), &aPlayer)==players.end()) {
      players.push_back(&aPlayer);
      aPlayer.setBalance(kStartingBalance);
      return true;
    }
    return false;
  }
  
  bool Game::willRun() {
    return players.size()>1; //gotta have 2 or more players...
  }

  bool Game::run(float anAnte, std::ostream &anOutput) {
    Round  theRound(cardCount, anAnte);    
    while(theRound.willRun(players)) {
      theRound.didRun(theRound.run(minBet, anOutput));
    }
    return true;
  }
   
  const char* verifyRound(const std::string &anOutput) {
    return "Unverified";
  }

  bool Game::didRun(bool aRunStatus, const std::string &anOutput) {
    //find player with most cash...
    Player *theWinner=nullptr;
    for(auto thePlayer : players) {
      if(!theWinner) theWinner=thePlayer;
      else {
        if(theWinner->getBalance()<thePlayer->getBalance()) {
          theWinner=thePlayer;
        }
      }
    }
    
    if(theWinner) {
      std::cout << verifyRound(anOutput) <<
        " winner is " << theWinner->getName()
        << " balance $" << theWinner->getBalance() << "\n";
      std::cout << anOutput << "\n";
    }
    else  {
      std::cout << "Winner unknown, something is wrong!\n";
    }
    return true;
  }
  

}




