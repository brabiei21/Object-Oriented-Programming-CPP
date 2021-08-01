//
// Created by Shreyas Rajesh on 4/19/20.
//

#include "MadLibsController.hpp"
#include "MadlibAutoWordProvider.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    // Tests for Automatic input based Madlibs.
    MadlibWordProvider *theAutoProvider = new MadlibAutoWordProvider;
    //Tests for each type of Substitute word
    // tests 1: Plural Noun
    cout << "Testing request for plural noun: ";
    string word_type = "pluralnoun";
    string out = theAutoProvider->getSubstituteWord(theAutoProvider->getTypeForLabel(word_type));
    if(out == "aardvarks"|| out == "bangladeshs" || out == "banks" || out == "bankers" || out == "bars" || out == "barbers" || out == "bats"
       || out == "oranges" || out == "blues" || out == "greens" || out == "purples" || out == "apples" || out == "quails" || out == "rabbits"
       || out == "reds" || out == "eights" || out == "fives" || out == "fourths")
    {
        cout << "Success" << endl;
    }
    else
    {
        cout << "FAILURE, returned: " << out << endl;
        return 1;
    }

    return 0;
}
