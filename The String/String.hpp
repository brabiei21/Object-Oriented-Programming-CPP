
//  Created by rick gessner on 1/29/20.
//  Copyright © 2020 rick gessner. All rights reserved.

// Only frame was made by rick genssner, All implementation were done by Behrad Rabiei
#ifndef String_hpp
#define String_hpp

#include <stdio.h>
#include <iostream>
#include <cstring>
#include "BufferManager.hpp"
 

namespace ECE141
{
    template<typename T=char>
    struct IsStringy
    {
        virtual T  *getBuffer() const  = 0;
        virtual size_t getLength() const  = 0;
    };

   
    class CharAdapter : public IsStringy<>, public BufferManager<char, 32>
    {
    public:
        CharAdapter(const char * cString): BufferManager<char, 32>{cString} {}
        char*       getBuffer() const override {return BufferManager<char,32>::getBuffer();}
        size_t      getLength() const override {return BufferManager<char,32>::getCapacity();}
    };

    template<typename T=char, size_t aPresize=32>
    class String : public IsStringy<T>
    {
      public:
        //all OCF methods...
        String() :  myBuffer{}{}
        String(const String &aString)
        {
            myBuffer = aString.getBuffer();
        }
        String(const T* aCharPointer)
        {
            myBuffer = aCharPointer;
        }

        String& operator=(const String &aBuffer)
        {
            //add version to assign from const char*
            myBuffer = aBuffer.getBuffer();
            return *this;
        }
          
        String& operator=(const T* aBuffer)
        {
            myBuffer = aBuffer;
            return *this;
        }
          
        //mutation methods...
        T& operator[](size_t pos)
        {
            if(pos and pos < myBuffer.getCapacity()) //wanted to try something new*
            {
                return myBuffer.operator[](pos);
            }
            else return myBuffer.operator[](0);
        }
        
        String  operator+(const String &rhs)
        {
            BufferManager<T, 32> temp(rhs.getBuffer());
            temp.insert(0, myBuffer.getBuffer());
            return temp.getBuffer();
        }
        //add method to add const char*
        String operator+(const T* rhs)
        {
            BufferManager<T,32> temp(rhs);
            temp.insert(0, myBuffer.getBuffer());
            return temp.getBuffer();
        }

        //add method to support "hello"+theStringObject
        String& operator+=(const String &rhs)
        {
            if (rhs.getBuffer() == nullptr) { return *this; }
            myBuffer.resize(rhs.getBuffer(), myBuffer.getLength() + rhs.size()); // make sure the capacity is enough
            myBuffer.copy_to_buffer_at(myBuffer.getLength(), rhs.getBuffer()); // append the new char array on
            myBuffer.setLength(myBuffer.getLength() + strlen(rhs.getBuffer())); // set the length
            myBuffer[myBuffer.getLength()] = 0; // attach the null char
            return *this;
        }
          
          
        //add method to append const char*
        String& insert(size_t anIndex, const String &aStr, size_t aStrIndex, size_t aStrCount)
        {
            if (anIndex <= myBuffer.getLength())
            {
                myBuffer.insert(anIndex, aStr.getBuffer()+aStrIndex, aStrCount);
                return *this;
            }
            return *this;
        }
        String& insert(size_t anIndex, const char * aStr, size_t aStrIndex, size_t aStrCount)
        {
            if (anIndex <= myBuffer.getLength())
            {
                myBuffer.insert(anIndex, aStr+aStrIndex, aStrCount);
                return *this;
            }
            return *this;
        }
              //add method to insert const char*

        String& insert(size_t anIndex, T aChar)
        {
            if (anIndex <= myBuffer.getLength())
            {
                T* inner = &aChar;
                BufferManager<T,32> temp{inner};
                myBuffer.insert(anIndex, temp.getBuffer(), strlen(temp.getBuffer())-1);
                return *this;
            }
            return *this;
        }

        String& replace(size_t anIndex, size_t aMaxCopyLen, const String &aString)
        {
            erase(anIndex, aMaxCopyLen);
            myBuffer.insert(anIndex, aString.getBuffer(), strlen(aString.getBuffer()));
            return *this;
        }
        
        String& replace(size_t anIndex, size_t aMaxCopyLen, const char* aString)
        {
            erase(anIndex, aMaxCopyLen);
            myBuffer.insert(anIndex, aString, strlen(aString));
            return *this;
        }
        //add method to replace const char*

        //Search...
        int find( const String &aString, size_t anIndex = 0 )
        {
            int counter = 0;
            
            for(int i =anIndex; i<myBuffer.getLength() - strlen(aString.getBuffer())+1; i++)
            {
                for(int j = 0; j<strlen(aString.getBuffer()); j++)
                {
                    if(myBuffer[i+j] == aString.getBuffer()[j])
                       counter++;
                }
               if(strlen(aString.getBuffer()) == counter)
               {
                   return i;
               }
               counter=0;
            }
            return 0;
        }
        
        int find( const T* aString, size_t anIndex = 0 )
        {
            int counter = 0;
            
            for(int i =anIndex; i<myBuffer.getLength() - strlen(aString); i++)
            {
                for(int j = 0; j<strlen(aString); j++)
                {
                    if(myBuffer[i+j] == aString[j])
                       counter++;
                }
               if(strlen(aString) == counter)
               {
                   return i;
               }
               counter=0;
            }
            return 0;
        }
        

        friend std::ostream& operator << (std::ostream &anOut, const String &aStr)
        {
            anOut<<aStr.getbuffer();
            return anOut;
        }//?
        friend std::istream& operator >> (std::istream &anOut,  String &aString)
        {
            anOut>>aString;
            return anOut;
        }
        
        //Comparision methods...
        int compare(const IsStringy<T>& aString) const
        {
            return std::strcmp(myBuffer.getBuffer(),aString.getBuffer());
        }//?

        //add method to compare const String&
        bool operator==(const String &aString) const {return compare(CharAdapter(aString.getBuffer())) == 0;}
        bool operator!=(const String &aString) const {return compare(CharAdapter(aString.getBuffer())) != 0;}
        bool operator<(const String &aString) const {return compare(CharAdapter(aString.getBuffer())) < 0;}
        bool operator<=(const String &aString) const {return compare(CharAdapter(aString.getBuffer())) <= 0;}
        bool operator>(const String &aString) const {return compare(CharAdapter(aString.getBuffer())) > 0;}
        bool operator>=(const String &aString) const {return compare(CharAdapter(aString.getBuffer())) >= 0;}
          
        bool operator==(const T* aChar) const {return compare(CharAdapter(aChar)) == 0;}
        bool operator!=(const T* aChar) const {return compare(CharAdapter(aChar)) != 0;}
        bool operator<(const T* aChar) const {return compare(CharAdapter(aChar)) < 0;}
        bool operator<=(const T* aChar) const {return compare(CharAdapter(aChar)) <= 0;}
        bool operator>(const T* aChar) const {return compare(CharAdapter(aChar)) > 0;}
        bool operator>=(const T* aChar) const {return compare(CharAdapter(aChar)) >= 0;}
        //Add version(s) to support const char*...
    
        String& erase(size_t pos = 0, size_t len = 1)
        {
            // starting at pos index, including pos index char, erase len chars
            myBuffer.erase(pos, len);
            return *this;
        }
        
        size_t      size()      const          {return myBuffer.getLength();}
        T*          getBuffer() const override {return myBuffer.getBuffer();}
        size_t      getLength() const override {return myBuffer.getLength();}
        
        
        friend String operator+(const String& lhs, const String& rhs)
        {
            String<T> temp;
            temp = lhs + rhs;
            return temp;
        }
        friend String operator+(const String& lhs, const char* rhs)
        {
            String<T> temp;
            temp = lhs + rhs;
            return temp;
        }
        friend String operator+(const char* lhs, const String& rhs)
        {
            String<T> temp;
            temp = lhs + rhs;
            return temp;
        }
        
    protected:
          BufferManager<T, aPresize> myBuffer;
      };
     
} //end namespace

#endif /* String_hpp */



