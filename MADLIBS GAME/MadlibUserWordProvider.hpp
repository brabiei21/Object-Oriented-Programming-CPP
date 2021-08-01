#ifndef MadlibUserWordProvider_hpp
#define MadlibUserWordProvider_hpp

#include <stdio.h>
#include "MadlibWordProvider.hpp"

class MadlibUserWordProvider : public MadlibWordProvider
        {
public:
    MadlibUserWordProvider(); //ctor
    MadlibUserWordProvider(const MadlibUserWordProvider &aUserProvider);
    MadlibUserWordProvider &operator=(const MadlibUserWordProvider &aUserProvider);
    ~MadlibUserWordProvider();
    virtual std::string getSubstituteWord(WordType aType);

};

#endif
