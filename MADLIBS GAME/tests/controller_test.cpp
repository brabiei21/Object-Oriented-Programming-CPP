//
// Created by Shreyas Rajesh on 4/19/20.
//
#include "MadLibsController.hpp"
#include "MadlibWordProvider.hpp"

using namespace std;

class MadlibEchoWordProvider : public MadlibWordProvider {
    public:
        virtual std::string getSubstituteWord(WordType aType) {
            return getLabelForType(aType);
        };
};

int main(int argc, const char * argv[]) {

    // Tests for User input based Madlibs.
    MadlibWordProvider *theProvider = new MadlibEchoWordProvider;
    MadLibsController *theController = new MadLibsController;
    std::vector<std::string> required_words;
    std::vector<std::string> words;
    const char* file = "madlibs1.txt";

    if(theController->readFile(file)) {
        theController->getSubstitutes(*theProvider);
        //tests 1
        cout << "Testing word list identification using the echo word provider: ";
        words = theController->getWords();
        string user_words;
        for(auto it=words.begin();it!=words.end();it++){
            user_words += *it;
            user_words += " ";
        }
        if(user_words == "verb adjective adjective pluralnoun adjective fruit name place adjective name color animal adjective adjective adjective noun number pluralnoun pluralnoun "){
            cout << "Success" << endl;
        }
        else {
            cout << "FAILURE" << endl;
            cout << "List: " << user_words << endl;
            return 1;
        }

        //tests 2
        // Check if the passage output is correct.
        theController->showFinishedStory(cout);
    }
    else {
        cout << " Failed reading madlibs1.txt" << endl;
        delete theProvider;
        delete theController;
        return 1;
    }
    delete theProvider;
    delete theController;
    return 0;
}
