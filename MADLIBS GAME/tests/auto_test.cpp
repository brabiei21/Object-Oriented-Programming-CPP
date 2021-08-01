//
// Created by Shreyas Rajesh on 4/19/20.
//

#include "MadLibsController.hpp"
#include "MadlibAutoWordProvider.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    // Tests for Automatic input based Madlibs.
    MadlibWordProvider *theAutoProvider = new MadlibAutoWordProvider;
    string out;
    
    //Tests for each type of Substitute word
    // tests 1: Noun
    cout << "Testing Noun Substitution: ";
    string word_type = "noun";
    out = theAutoProvider->getSubstituteWord(theAutoProvider->getTypeForLabel(word_type));
    if(out == "aardvark"|| out == "bangladesh" || out == "bank" || out == "banker" || out == "bar" || out == "barber" || out == "bat"
    || out == "orange" || out == "blue" || out == "green" || out == "purple" || out == "apple" || out == "quail" || out == "rabbit"
    || out == "red" || out == "eight" || out == "five" || out == "fourth"){
        cout << "Success" << endl;
    }
    else {
        cout << "FAILURE, returned word: " << out << endl;
        return 1;
    }

    //tests 2: name
    cout << "Testing Name Substitution: ";
    word_type = "name";
    out = theAutoProvider->getSubstituteWord(theAutoProvider->getTypeForLabel(word_type));
    if(out == "Thompson" || out == "Curry"){
        cout << "Success" << endl;
    }
    else {
        cout << "FAILURE, returned word: " << out << endl;
        return 1;
    }

    //tests 3: Verb
    cout << "Testing Verb Substitution: ";
    word_type = "verb";
    out = theAutoProvider->getSubstituteWord(theAutoProvider->getTypeForLabel(word_type));
    if(out == "be" || out == "begin"){
        cout << "Success" << endl;
    }
    else {
        cout << "FAILURE, returned word: " << out << endl;
        return 1;
    }

    //tests 4: Adjective
    cout << "Testing Adjective Substitution: ";
    word_type = "adjective";
    out = theAutoProvider->getSubstituteWord(theAutoProvider->getTypeForLabel(word_type));
    if(out == "courteous" || out == "crazy" || out == "scared"){
        cout << "Success" << endl;
    }
    else {
        cout << "FAILURE, returned word: " << out << endl;
        return 1;
    }
    
    //tests 5: Adverb
    cout << "Testing Adverb Substitution: ";
    word_type = "adverb";
    out = theAutoProvider->getSubstituteWord(theAutoProvider->getTypeForLabel(word_type));
    if(out == "scarcely" || out == "absentmindedly"){
        cout << "Success" << endl;
    }
    else {
        cout << "FAILURE, returned word: " << out << endl;
        return 1;
    }

    //tests 6: Number
    cout << "Testing Number Substitution: ";
    word_type = "number";
    out = theAutoProvider->getSubstituteWord(theAutoProvider->getTypeForLabel(word_type));
    if(out == "eight" || out == "five" || out == "fourth"){
        cout << "Success" << endl;
    }
    else {
        cout << "FAILURE, returned word: " << out << endl;
        return 1;
    }

    //tests 7: Color
    cout << "Testing Color Substitution: ";
    word_type = "color";
    out = theAutoProvider->getSubstituteWord(theAutoProvider->getTypeForLabel(word_type));
    if(out == "green" || out == "blue" || out == "purple"){
        cout << "Success" << endl;
    }
    else {
        cout << "FAILURE, returned word: " << out << endl;
        return 1;
    }

    //tests 8: Fruit
    cout << "Testing Fruit Substitution: ";
    word_type = "fruit";
    out = theAutoProvider->getSubstituteWord(theAutoProvider->getTypeForLabel(word_type));
    if(out == "apple" || out == "orange"){
        cout << "Success" << endl;
    }
    else {
        cout << "FAILURE, returned word: " << out << endl;
        return 1;
    }

    //tests 9: Animal
    cout << "Testing Animal Substitution: ";    
    word_type = "animal";
    out = theAutoProvider->getSubstituteWord(theAutoProvider->getTypeForLabel(word_type));
    if(out == "aardvark" || out == "bat" || out == "quail" || out == "rabbit"){
        cout << "Success" << endl;
    }
    else {
        cout << "FAILURE, returned word: " << out << endl;
        return 1;
    }

    //tests 10: place
    cout << "Testing Place Substitution: ";    
    word_type = "place";
    out = theAutoProvider->getSubstituteWord(theAutoProvider->getTypeForLabel(word_type));
    if(out == "bangladesh" || out == "bank"){
        cout << "Success" << endl;
    }
    else {
        cout << "FAILURE, returned word: " << out << " Type: " << word_type << " " << (int) theAutoProvider->getTypeForLabel(word_type) << endl;
        return 1;
    }
    
    return 0;
}


