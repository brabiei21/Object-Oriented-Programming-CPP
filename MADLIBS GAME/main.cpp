#include <iostream>
#include "MadLibsController.hpp"
#include "MadlibUserWordProvider.hpp"
#include "MadlibAutoWordProvider.hpp"
#include <fstream>

std::ostream& getOutput()
{
  return std::cout;  //You can change this for debugging, but change it back for testing!
}

//This is where we do basic madlibs (with user input)...
void testUserMadlibs(const char *aPath, std::ostream &anOutput)
{
    //complete the following code, and handle memory too!
    MadlibWordProvider *theProvider;  //make a USER provider on the heap
    theProvider = new MadlibUserWordProvider;
    MadLibsController *theController;  //make a controller on the heap
    theController = new MadLibsController;
    theController->runStory(aPath, *theProvider, anOutput);
    delete(theProvider);
    delete(theController);
}

//This is where we do auto-madlibs (chatbot answers via objects)...
void testAutoMadlibs(const char *aPath, std::ostream &anOutput)
{
    //complete the following code, and handle memory too!
    MadlibWordProvider *theProvider; //make an AUTO provider on the heap
    theProvider = new MadlibAutoWordProvider;
    MadLibsController *theController; //make a controller on the heap
    theController = new MadLibsController;
    theController->runStory(aPath, *theProvider, anOutput);
    delete(theProvider);
    delete(theController);
}

const char* getPath()
{
  return "madlibs1.txt"; //full path to madlibs1.txt ...
}

int main(int argc, const char * argv[])
{
    //std::srand((unsigned int)std::time(nullptr));  //random # seed...
    testUserMadlibs(getPath(), getOutput());
    testAutoMadlibs(getPath(), getOutput());
    return 0;
}
