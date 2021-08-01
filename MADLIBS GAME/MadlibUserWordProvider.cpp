#include "MadlibUserWordProvider.hpp"
#include <iostream>

MadlibUserWordProvider::MadlibUserWordProvider() : MadlibWordProvider(){}
MadlibUserWordProvider::MadlibUserWordProvider(const MadlibUserWordProvider &aUserProvider){}
MadlibUserWordProvider &MadlibUserWordProvider::operator=(const MadlibUserWordProvider &aUserProvider){return *this;}
MadlibUserWordProvider::~MadlibUserWordProvider(){}

std::string MadlibUserWordProvider::getSubstituteWord(WordType aType)
{
    std::string word;
    std::string type;
    int number = int(aType);


    switch(number)
    {
        case 0:
        {
            type = "invalid";
            break;
        }
        case 1:
        {
            type = "noun";
            break;
        }
        case 2:
        {
            type = "pluralnoun";
            break;
        }
        case 3:
        {
            type = "name";
            break;
        }
        case 4:
        {
            type = "verb";
            break;
        }
        case 5:
        {
            type = "adjective";
            break;
        }
        case 6:
        {
            type = "adverb";
            break;
        }
        case 7:
        {
            type = "number";
            break;
        }
        case 8:
        {
            type = "color";
            break;
        }
        case 9:
        {
            type = "fruit";
            break;
        }
        case 10:
        {
            type = "animal";
            break;
        }
        case 11:
        {
            type = "place";
            break;
        }
        default:
            type = "Not sure what you gave me.";
    }

  //ask the user for console input (std::cin), and return their input...
  if(type != "invalid")
  {
      std::cout<<"Please enter a/an "<<type<<": ";
      std::cin>>word;
      return word;
  }
  return "nothing";
}


