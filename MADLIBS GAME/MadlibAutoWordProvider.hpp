#ifndef MadlibAutoWordProvider_hpp
#define MadlibAutoWordProvider_hpp


#include "MadlibWordProvider.hpp"
#include <cstdlib>
#include <ctime>

//a tiny little class, with a base class
class MadlibAutoWordProvider : public MadlibWordProvider {
public:
    MadlibAutoWordProvider(); //ctor (don't forget the rest of the OCF)
    MadlibAutoWordProvider(const MadlibAutoWordProvider &aAutoProvider);
    MadlibAutoWordProvider &operator=(const MadlibAutoWordProvider &aAutoProvider);
    ~MadlibAutoWordProvider() ;
    virtual std::string getSubstituteWord(WordType aType); //provide random words for each type...
    bool readJSON(const char *jsonPath);

protected:
    struct WORD
            {
        std::string word;
        std::string pos;
        std::string category;

    };
    std::vector<WORD> word_list;
    //std::vector<std::string> names = {"Fatemeh","Bardiya","Salman", "Sara", "John","Bahador", "Ernika","Mahboba", "Mahroo", "Malalai","Soltan"};
    unsigned seed = time(0);

};



#endif /* MadlibAutoWordProvider_hpp */
