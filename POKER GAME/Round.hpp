
#ifndef Round_h
#define Round_h

#include "Game.hpp"
#include "Deck.hpp"
#include "Hand.hpp"
#include "Player.hpp"
#include <map>
#include <vector>

namespace ECE17 {
      
  //using Hands = std::map<ECE17::Player*, Hand>;

  class Round {
  public:
    Round(size_t aCardCount, float anAnte=5.0)
      : cardCount(aCardCount), pot(0.0), ante(anAnte), round(0) {}
              
    //give each player a turn to drop/add cards.
    Round& drawCards(Deck &aDeck)
    {
        int numCards;
      
      aDeck.shuffle();
      for(int i = 0; i < players.size(); i++)
      {
          numCards = players[i]->discardUnwanted();
          numCards = 5 - numCards;
          players[i]->drawCards(aDeck, numCards);
      }
      return *this;
    }
    
    Round& dealCards(Deck &aDeck)
    {
      
      aDeck.shuffle();
      Card tempCard;
      for(int i = 0; i < players.size(); i++)
      {
          players[i]->hand.ourHand.clear();
      }

      for(int i =0; i < players.size(); i++)
      {

          for (int j =0; j < 5; j++)
          {
              aDeck.shuffle();
              aDeck.pop(tempCard);
              players[i]->hand.ourHand.push_back(tempCard);
          }
      }
      return *this;
    }



    //Get bets from each player; some may "fold" (quit hand)
    //return # of players who are still in this round
    size_t placeBets(float aMinBet)
    {
        int temp;
      size_t theCount=0;
      for(int i = 0; i<players.size(); i++)
      {
          if(!players[i]->isFolding())
          {
              temp = players[i]->placeBet(aMinBet);
              if(temp > aMinBet)
              {
                  pot += temp;
                  theCount++;
              }
          }
      }
      return theCount;
    }
          
    //rank the hand of each player, and give the winning hand the pot...
    Round& payWinner(std::ostream &anOutput) {
      
      Player *theWinner=nullptr;
            
      for(auto thePlayer : players) {
        if(theWinner) {
          if(thePlayer->getHand()>theWinner->getHand()) {
            theWinner=thePlayer;
          }
        }
        else theWinner=thePlayer;
      }
      
      for(auto thePlayer : players) {
        anOutput << "\t" << thePlayer->getName() << " ";
        thePlayer->getHand().show(anOutput);
        if(theWinner==thePlayer) {
          float theBal=thePlayer->getBalance();
          thePlayer->setBalance(theBal+pot);
          anOutput << " won " << pot;
        }
        anOutput << "\n";
      }
      
      return *this;
    }
    
    bool willRun(Players &aPlayers) {
      players.clear(); //no players in the round...
      pot=0.0;
      for(auto thePlayer : aPlayers) {
        float theBalance=thePlayer->getBalance();
        if(theBalance>=ante) {
          players.push_back(thePlayer);
          thePlayer->setBalance(theBalance-ante);
          thePlayer->setHand(Hand()); //empty?
          pot+=ante;
        }
      }
      return players.size()>1;
    }
    
    bool didRun(bool runStatus) {
      ante+=1.0; //increment every round...
      return runStatus;
    }

    bool run(float aMinBet, std::ostream &anOutput) {
      Deck theDeck;
      dealCards(theDeck);

      anOutput << "Round " << ++round << "-- \n";
      if(placeBets(aMinBet)>1) {
        drawCards(theDeck).placeBets(aMinBet);
      }
      payWinner(anOutput);
      return players.size();
    }
        
  protected:
    Players players;
    size_t  cardCount;
    float   ante;
    float   pot;
    size_t  round;
  };

}
#endif /* Round_h */

