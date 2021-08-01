#ifndef MadLibsController_hpp
#define MadLibsController_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include "MadlibWordProvider.hpp"
#include <sstream>


class MadLibsController {
public:

    MadLibsController(); //default ctor
    bool  runStory(const char *aFilename, MadlibWordProvider &aProvider, std::ostream &anOutput);
    bool  readFile(const char *aFilename);
    void  getSubstitutes(MadlibWordProvider &aProvider);
    void  showFinishedStory(std::ostream &anOutput);
    std::vector<std::string> getWords();
  
protected:
    std::vector<std::string> words;
    std::vector<std::string> wordsForOutput;
    std::vector<std::string> vectorOfLines;
};

#endif
