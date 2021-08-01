#include "MadLibsController.hpp"
#include <fstream>
#include <ctype.h>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>


MadLibsController::MadLibsController(){}

std::vector<std::string> MadLibsController::getWords(){return words;}

bool isPunct(char aChar)
{
  static std::string punct(".;?!:,'-");
  return std::string::npos != punct.find(aChar);
}

//in this method, show the final result of your madlib (with user data) to given output
void MadLibsController::showFinishedStory(std::ostream &anOutput)
{
    anOutput << "Your madlib is: \n";

      for(int i =0; i < wordsForOutput.size()-2; i++)
    {
          if(wordsForOutput[i+1] != "\n")
         anOutput << wordsForOutput[i]<<" ";
          else
              anOutput << wordsForOutput[i];

    }
    anOutput << wordsForOutput[wordsForOutput.size()-1];
      anOutput<<"\n";

    //now show the user their madlib, with their words embedded in the output...    
}

//Notice how we separated 'reading a file' from other operations?
//In this method, you read the madlib template file...
bool MadLibsController::readFile(const char *aPath)
{
    std::string word;
    std::ifstream read;
    read.open(aPath);
    if (!read.is_open())
        return false;

    while (!read.eof())
    {
        getline(read, word);
        vectorOfLines.push_back(word);
    }
    return true;
}
//Find all the capitalized words madlib (file), and ask provider for word substitutes...
void MadLibsController::getSubstitutes(MadlibWordProvider &aProvider)
{
    //iterate through the madlib file (words), and ask your word provider for each CAPITALIZED word...
    std::string word;
    std::string word2;
    WordType ourType;
    char lastChar;
    std::stringstream vectorOfStream[vectorOfLines.size()];
    bool pun = false;
    //std::stringstream iss;
    for(int i = 0; i<vectorOfLines.size(); i++)
    {
        vectorOfStream[i] << vectorOfLines[i];
        while (vectorOfStream[i] >> word)
        {
            lastChar = word.back();
            //std::string s(1, lastChar);
            if(isPunct(lastChar))
            {
                word = word.substr(0,word.length()-1);
                pun = true;
            }


            if (std::all_of(word.begin(), word.end(), [](unsigned char c){ return std::isupper(c); }) && (word.length() > 1))
            {
                ourType = aProvider.getTypeForLabel(word);
                word2 = aProvider.getSubstituteWord(ourType);
                //std::cout<<word<<"\n";
                words.push_back(word2);
                if(pun)
                {
                    word2 = word2 + lastChar;
                }
                wordsForOutput.push_back(word2);
            }
            else
            {
                word2 = word;

                if(pun)
                {
                    word2 = word2 + lastChar;
                }
                wordsForOutput.push_back(word2);
            }
            pun = false;

        }
        wordsForOutput.push_back("\n");
    }

}

bool MadLibsController::runStory(const char *aFilename, MadlibWordProvider &aProvider, std::ostream &anOutput)
{
    if(readFile(aFilename))
    {
        getSubstitutes(aProvider); //get replacement for each CAPITALIZED word (substitutes)
        showFinishedStory(anOutput);
        return true;
    }
    return false;
}





