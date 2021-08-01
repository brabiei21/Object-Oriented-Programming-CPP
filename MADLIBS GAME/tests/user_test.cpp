//
// Created by Shreyas Rajesh on 4/19/20.
//

#include "MadLibsController.hpp"
#include "MadlibUserWordProvider.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    // Tests for Automatic input based Madlibs.
    MadlibWordProvider *theProvider = new MadlibUserWordProvider;
    //Tests for each type of Substitute word
    // tests 1: tests for proper input
    cout << "Testing first request: ";
    string word_type = "noun";
    string out;
    out = theProvider->getSubstituteWord(theProvider->getTypeForLabel(word_type));
    if(out == "spying") {
        cout << "Success" << endl;
    }
    else {
        cout << "FAILURE" << endl;
        return 1;
    }

    cout << "Testing second request: ";
    out = theProvider->getSubstituteWord(theProvider->getTypeForLabel(word_type));
    if(out == "brilliant") {
        cout << "Success" << endl;
    }
    else {
        cout << "FAILURE" << endl;
        return 1;
    }
    return 0;
}



