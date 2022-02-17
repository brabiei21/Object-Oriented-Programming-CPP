
#include "Hand.hpp"
#include <algorithm>
#include <map>
#include <set>
#include <vector>


namespace ECE17 {

    Hand::Hand(){}
    Hand::Hand(const Hand &aCopy)
    {
        *this=aCopy;
    }
    Hand& Hand::operator=(const Hand &aCards)
    {
        
        for(int i = 0; i < aCards.ourHand.size(); i++)
        {
            ourHand[i] = aCards.ourHand[i];
        }
        return *this;
    }
    Hand::~Hand()
    {
        
    }

    bool Hand::operator>(const Hand& aHand) const
    {
        
        std::vector<Faces> ourVector;
        std::vector<Faces> theirVector;
        int s = 4;

        if( this->determineRank() > aHand.determineRank())
            return true;
        if(this->determineRank() == aHand.determineRank())
        {
            for(int i = 0; i < ourHand.size(); i++)
            {
                ourVector.push_back( (ourHand[i].getFace()));
                theirVector.push_back((aHand.ourHand[i].getFace()));
            }
            std::sort (ourVector.begin(), ourVector.end());
            std::sort (theirVector.begin(), theirVector.end());

            while( s >= 0)
            {
                if(ourVector[s] > theirVector[s])
                    return true;
                else if(ourVector[s] < theirVector[s])
                    return false;
                else
                    s--;
            }
            return false;
        }
        return false;
    }


    Hand& Hand::add(const Card& aCard)
    {
       
        if ( 5 <= ourHand.size())
            return *this;

        for(int i = 0; i < ourHand.size(); i++)
        {
            if ( ourHand[i].DoesCardMatch(aCard))
                return *this;
        }
        ourHand.push_back(aCard);
        return *this;
    }
    bool Hand::discard(const Card &aCard)
    {
       
        for(int i =0; i <ourHand.size(); i++)
        {
            if(ourHand[i].getFace() == aCard.getFace() && ourHand[i].getSuit() == aCard.getSuit())
            {
                ourHand.erase(ourHand.begin() + i);
                return true;
            }
        }
        return false;
    }
    size_t Hand::count()
    {
       
        return ourHand.size();
    }
    //show deck on one line:  [4H, 3C, 10D, AC, AS]
    void Hand::show(std::ostream &anOutput) const
    {

            anOutput << "["<< ourHand[0].GetFaceName()<<ourHand[0].GetSuitSymbol()<<", "
                           << ourHand[1].GetFaceName()<<ourHand[1].GetSuitSymbol()<<", "
                           << ourHand[2].GetFaceName()<<ourHand[2].GetSuitSymbol()<<", "
                           << ourHand[3].GetFaceName()<<ourHand[3].GetSuitSymbol()<<", "
                           << ourHand[4].GetFaceName()<<ourHand[4].GetSuitSymbol()<<"] ";

    }
    //Determine the kind of hand (rank) we have, given a set of cards...


    HandTypes Hand::determineRank() const
    {
        
        if(RoyalFlush())
            return HandTypes::royal_flush;

        if(StraightFlush())
            return HandTypes::straight_flush;


        if(FourOfAKind())
            return HandTypes::four_kind;

        if(FullHouse())
            return HandTypes::full_house;

        if(Flush())
            return HandTypes::flush;

        if(Straight())
            return HandTypes::straight;

        if(ThreeOfAKind())
            return HandTypes::three_kind;

        if(TwoPair())
            return HandTypes::two_pair;

        if(OnePair())
            return HandTypes::one_pair;


        return HandTypes::high_card;
    }


    bool        Hand::RoyalFlush() const
    {
        if(isSameSuit())
        {
            if(isSequence())
            {
                for(int i = 0; i < ourHand.size(); i++)
                {
                    if( 14 == static_cast<int> (ourHand[i].getFace()))
                        return true;
                }
            }
        }
        return false;
    } // done
    bool        Hand::StraightFlush() const
    {
        if(isSequence())
        {
            if(isSameSuit())
                return true;
        }
        return false;
    } // done
    bool        Hand::Flush() const{
        if(isSameSuit())
            return true;
        return false;
    }     //done
    bool        Hand::Straight() const{
        if(isSequence())
            return true;
        return false;
    }  //done
    bool        Hand::ThreeOfAKind() const
    {
        std::set <int> tempSet;
        std::vector <int> tempVector;

        for(int i = 0; i < ourHand.size(); i++)
        {
            tempVector.push_back(static_cast <int> (ourHand[i].getFace()));
            tempSet.insert(static_cast <int> (ourHand[i].getFace()));
        }
        std::sort (tempVector.begin(), tempVector.end());


        std::set<int>::iterator i;
        for (i = tempSet.begin(); i!= tempSet.end(); i++)
        {
            if(3 == std::count(tempVector.begin(), tempVector.end(), *i))
                return true;
        }

        return false;
    } // done
    bool        Hand::FourOfAKind() const
    {
        std::set <int> tempSet;
        std::vector <int> tempVector;

        for(int i = 0; i < ourHand.size(); i++)
        {
            tempVector.push_back(static_cast <int> (ourHand[i].getFace()));
            tempSet.insert(static_cast <int> (ourHand[i].getFace()));
        }
        std::sort (tempVector.begin(), tempVector.end());

        if(tempSet.size() == 2)
        {
            std::set<int>::iterator i;
            for (i = tempSet.begin(); i!= tempSet.end(); i++)
            {
                if(4 == std::count(tempVector.begin(), tempVector.end(), *i))
                    return true;
            }
        }
        return false;
    }  //done

    bool        Hand::TwoPair() const  //done
    {
        std::set <int> tempSet;
        std::vector <int> tempVector;

        for(int i = 0; i < ourHand.size(); i++)
        {
            tempVector.push_back(static_cast <int> (ourHand[i].getFace()));
            tempSet.insert(static_cast <int> (ourHand[i].getFace()));
        }
        std::sort (tempVector.begin(), tempVector.end());

        if(tempSet.size() == 3)
        {
            std::set<int>::iterator i;
            for (i = tempSet.begin(); i!= tempSet.end(); i++)
            {
                if(2 == std::count(tempVector.begin(), tempVector.end(), *i))
                    return true;
            }
        }
        return false;
    }
    bool        Hand::OnePair()  const   //done
    {
        std::set <int> tempSet;
        std::vector <int> tempVector;

        for(int i = 0; i < ourHand.size(); i++)
        {
            tempVector.push_back(static_cast <int> (ourHand[i].getFace()));
            tempSet.insert(static_cast <int> (ourHand[i].getFace()));
        }
        std::sort (tempVector.begin(), tempVector.end());

        if(tempSet.size() == 4)
        {
            std::set<int>::iterator i;
            for (i = tempSet.begin(); i!= tempSet.end(); i++)
            {
                if(2 == std::count(tempVector.begin(), tempVector.end(), *i))
                    return true;
            }
        }
        return false;
    }
    bool        Hand::HighCard() const
    {}
    bool        Hand::FullHouse()  const //done
    {
        std::set <int> tempSet;
        std::vector <int> tempVector;

        for(int i = 0; i < ourHand.size(); i++)
        {
            tempVector.push_back(static_cast <int> (ourHand[i].getFace()));
            tempSet.insert(static_cast <int> (ourHand[i].getFace()));
        }
        std::sort (tempVector.begin(), tempVector.end());

        if(tempSet.size() == 2)
        {
            std::set<int>::iterator i;
            for (i = tempSet.begin(); i!= tempSet.end(); i++)
            {
                if(2 == std::count(tempVector.begin(), tempVector.end(), *i))
                    return true;
            }
        }
        return false;
    }

}

