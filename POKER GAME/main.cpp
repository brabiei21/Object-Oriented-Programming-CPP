//
//  main.cpp
//  assignment7
//

#include <iostream>
#include <sstream>
#include "Player.hpp"
#include "Card.hpp"
#include "Hand.hpp"
#include "Deck.hpp"
#include "Game.hpp"
#include "Testing.hpp"
#include "time.h"

//--------------------------------------------------------------------

int main(int argc, const char * argv[]) {    
  if(argc>1) {

    std::string temp(argv[1]);
        
    if("compile"==temp) {
      std::cout << "Compiled OK.\n";
      return 0;
    }
    else if("rank"==temp) {
      if(validateRanks()) {
        std::cout << "Validate ranks OK\n";
        return 0;
      }
    }
    else if("compare"==temp) {
      if(compareCards()) {
        std::cout << "Compare cards OK\n";
        return 0;
      }
    }
    else if("shuffle"==temp) {
      if(shuffleTest()) {
        std::cout << "Shuffle OK\n";
        return 0;
      }
    }
    else if("play"==temp)
    {
      ECE17::Game theGame;

      srand((unsigned)time(NULL));
      
      //STUDENT: Add players here...
      ECE17::Player thePlayer1("Player1");
      ECE17::Player thePlayer2("Player2");
      
      theGame.addPlayer(thePlayer1);
      theGame.addPlayer(thePlayer2);
      
      if(theGame.willRun()) {
        const float kStartAnte = 5.0;
        std::stringstream theOutput;
        theGame.didRun(theGame.run(kStartAnte,theOutput),theOutput.str());
      }
      return 0;
    }
    else if("this" == temp)
    {
        srand(time(NULL));
        Deck something, other;
        something.shuffle();
        other.shuffle();
        for(int i = 0; i < 52; i++)
        {
            std::cout<<(int)something.deckofCards[i].getFace()<<something.deckofCards[i].GetSuitSymbol()<<" ";

        }
        std::cout<<" \n";
        for(int i = 0; i < 52; i++)
        {

            std::cout<<(int)other.deckofCards[i].getFace()<<other.deckofCards[i].GetSuitSymbol()<<" ";
        }
    }
  }
        
  return -1;
}
