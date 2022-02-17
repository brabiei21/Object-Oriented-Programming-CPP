#ifndef buffermanager_h
#define buffermanager_h

#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <map>

#define scale_factor 2  

namespace ECE141
{

    template <typename T, size_t defaultCapacity=32>
    class BufferManager : Testable
    {
      public:
        //---- OCF methods ------
        //Constructor/Destructor
        BufferManager(size_t aValue= 0) : capacity{0}, length{0}, buffer_ptr{nullptr}
        {
            if(aValue)
            {
                willExpand(aValue, 0); //set pointer and capacity and length is still zero
            }
        }

        BufferManager(const char* aCharPointer) : capacity{0}, length{0}, buffer_ptr{nullptr}
        {
            if(aCharPointer)
            {
                length = strlen(aCharPointer); //strlen does not include null terminate
                resize(aCharPointer, length);
                strcpy(buffer_ptr, aCharPointer);
                //we have to do this because our buffer_ptr was null, otherwise resize already copies.
            }
            //no need for else, we already took care of it
        }
        
        BufferManager(const BufferManager &aCopy)
        : capacity{0}, length{0}, buffer_ptr{nullptr}
        {*this=aCopy;}           //Copy Constructor
        
        
        BufferManager& operator=(const BufferManager& aBuffer)
        {
            buffer_ptr = copyData(aBuffer.buffer_ptr, aBuffer.capacity, aBuffer.capacity);
            capacity = aBuffer.capacity;
            length = aBuffer.length;
            return *this;
        }
        
        BufferManager& operator=(const char* aBuffer)
        {
                 if (aBuffer != nullptr)
                 { // a not null ptr is passed in
                     resize(aBuffer, strlen(aBuffer)); // resize the underlaying buffer, capacity is set in resize function
                     length = strlen(aBuffer); // record the characters length
                     strcpy(buffer_ptr, aBuffer); // set the characters into the buffer
                     return *this;
                 }
                 else
                 { // not default construct, passed in a null pointing buffer
                     length = 0;
                     if (capacity >= 1)
                     { // make sure this buffer has some capacity
                         strcpy(buffer_ptr, ""); // set the buffer to nothing
                     }
                     return *this;
                 }
        }

        ~BufferManager()
        {
            delete [] buffer_ptr;
            buffer_ptr = nullptr;
            //capacity = 0;  //not really relevant
            //length   = 0;  //not really relevant
            
        } //Destructor (Too many issues trying to implement unique pointers)

        
        //---- Basic methods you must implement. Add more if you need to...
        size_t getCapacity() const {return capacity;}   //tells us the current capacity
        T*     getBuffer() const {return buffer_ptr;}   //returns ptr to internal buffer
        size_t getLength() const { return length;}
        
        //Ask to grow buffer to aNewSize; (optional anOffset says where growth may happen),
        //I will be refining this more after I implement the String Class.
        size_t willExpand(size_t aNewSize, size_t anOffset=0)
        {
            
            T* temp = buffer_ptr; //holds the current buffer
            buffer_ptr = copyData(buffer_ptr, aNewSize, capacity); //creates new buffer and transfers data
            delete     temp;  //this deletes the old buffer
            capacity = aNewSize;
            return     capacity;
        }
        
        size_t willCompact(size_t aNewSize, size_t anOffset=0)
        {
            T* temp    = buffer_ptr;
            buffer_ptr = copyData(buffer_ptr, aNewSize, length/*capacity*/);
            //concerning, aNewsize is smaller than capacity, CHECK AT OFFICE HOURS
    
            delete     temp;
            capacity = aNewSize;
            return     capacity;
        }//Ask to shrink the buffer to aNewSize

        T& operator[](size_t pos)
        {
            if(pos and pos < capacity) //wanted to try something new*
            {
                return buffer_ptr[pos];
            }
            else return buffer_ptr[0];
        }
        
        // resize function changes the capacity of the buffer if needed beased on the buffer passed in or aNewLength
        // resize function changes the initial content inside the buffer to the budder that is passed in
        BufferManager& resize(const char* aBuffer, size_t aNewLength, bool aRelease = false)
        { // aNewLength does not count the null character
                if (aNewLength < strlen(aBuffer)) { aNewLength = strlen(aBuffer); } // make sure the length can hold the buffer passed in
                if (aNewLength + 1 <= capacity) { return *this; }// if aNewLength +1 is shorter than the current capacity, we do not need to reallocate new buffer on heap
                else
                  { // this branch is when passed in buffer size + 1 is greater than capacity
                      capacity = (aNewLength + 1) * scale_factor; // allocate buffer to 1.5 times the char array's length's +1 size
                      T* tempCopy = buffer_ptr; // copy the buffer pointer
                      buffer_ptr = (new T[capacity]{ 0 }); // initializes the first element(character) to a null.
                      if (tempCopy != nullptr)
                      {
                          strcpy(buffer_ptr, tempCopy); // restore the previous characters in buffer
                          delete[] tempCopy; // release memory since now we have a new longer buffer
                      }
                      else
                      {
                          buffer_ptr[0] = 0;  //redundant, this was already done 8 lines above
                      }
                      return *this;
                  }
        }
        
        BufferManager& append(const T* aBuffer)
        {
            if (aBuffer == nullptr) { return *this; }
            resize(aBuffer, length + strlen(aBuffer)); // make sure the capacity is enough
            copy_to_buffer_at(strlen(buffer_ptr), aBuffer); // append the new char array on
            length = length + strlen(aBuffer); // set the length
            buffer_ptr[length] = 0; // attach the null char
            return *this;
        }
        
        BufferManager& erase(size_t pos = 0, size_t len = 1)
        { // starting at pos index, including pos index char, erase len chars
            if (pos < length)
            {
                if (len != 0)
                {
                    if (pos + len >= length)
                    { // erase all chars starting from pos
                        buffer_ptr[pos] = 0; // stop the buffer at index pos
                        length = pos;
                    }
                    else
                    {
                        shift_buffer_left(len, pos + len, length - 1); // shift left portion to the right and over write the erase area
                        length = length - len;
                        buffer_ptr[length] = 0; // set null ptr
                    }
                }
                else
                { // len == 0
                    return *this;
                }
            }
            return *this;
        }
        
        BufferManager& insert(size_t pos, const T* aBuffer)
        {
            if (pos <= length)
            { // make sure the pos index is in range
                resize(aBuffer, length + strlen(aBuffer)); // make sure the capacity is enough
                shift_buffer_right(strlen(aBuffer), pos, length - 1); // shift left the second half portion
                copy_to_buffer_at(pos, aBuffer);
                length = length + strlen(aBuffer); // set the length
                buffer_ptr[length] = 0; // attach the null char
                return *this;
            }
            return *this;
        }

        // overloading with argument aMaxCopyLen
        BufferManager& insert(size_t pos, const T* aBuffer, size_t aMaxCopyLen)
        {
            if (pos <= length)
            { // make sure the pos index is in range
                resize(aBuffer, length + aMaxCopyLen); // make sure the capacity is enough
                shift_buffer_right(aMaxCopyLen, pos, length - 1); // shift left the second half portion
                copy_to_buffer_at(pos, aBuffer, aMaxCopyLen);
                length = length + aMaxCopyLen; // set the length
                buffer_ptr[length] = 0; // attach the null char
                return *this;
            }
            return *this;
        }

        BufferManager& setBuffer(const T* aBuffer) const
        {
            if (aBuffer != nullptr)
            { // not a null pointing pointer is passed in
                length = strlen(aBuffer);
                resize(aBuffer, length); // set approporate buffer length
                copy_to_buffer_at(0, aBuffer); // copy the buffer starting at index 0
                buffer_ptr[length] = 0; // put null char
                return *this;
            }
            else if (this->buffer != nullptr)
            { // a null pointing pointer is passed in
                length = 0; // set to 0 length
                buffer_ptr[0] = 0; // make buffer empty
                return *this;
            }
            else
            { // a null pointing pointer is passed in
                return *this; // this buffer is also pointing to null
            }
        }

        OptString getTestName(size_t anIndex) const override
        {
            size_t thePos{0};
            for(auto thePair: kList)
            {
                if(anIndex == thePos++)
                {
                    return thePair.first;
                }
            }
            return std::nullopt;
        }

        bool operator()(const std::string &aName)override
        {
            return kList.count(aName) ? (this->*kList[aName])(): false;
        }

        using Callable = bool(BufferManager::*)();
        std::map<std::string, Callable> kList
        {
            {"test1", &BufferManager::testGetCapacity},
            {"test2", &BufferManager::testGetBuffer},
            {"test4", &BufferManager::testConstructors},
            {"test5", &BufferManager::testEqualOperator},
            {"test6", &BufferManager::testCompact},
            {"test7", &BufferManager::testExpand}
        };

        bool testConstructors()
        {
            bool conditionOne;
            bool conditionTwo;
            bool conditionThree;

            BufferManager someBuffer{12};
            BufferManager someBuffer1;
            BufferManager someBuffer2{someBuffer};

            conditionOne   = (24 == someBuffer.getCapacity())? true : false;
            conditionTwo   = (0  == someBuffer.getCapacity() && nullptr == someBuffer1.getBuffer())? true : false;
            conditionThree = (someBuffer2.getCapacity() == someBuffer.getCapacity() && someBuffer2.getBuffer() == someBuffer.getBuffer())? true : false;

            return (conditionOne && conditionTwo && conditionThree)? true : false;
        }
        bool testEqualOperator()  //this will also test copy constructor indirectly
        {
            BufferManager someBuffer{12};
            BufferManager someBuffer2{someBuffer};
            return (someBuffer2.getCapacity() == someBuffer.getCapacity() && someBuffer2.getBuffer() == someBuffer.getBuffer())? true : false;
        }
        //Will implement greater tests after string class.
        bool testExpand()
        {
            BufferManager someBuffer{12};
            someBuffer.willExpand(100);
            return (100 == someBuffer.getCapacity())? true : false;

        }
        //Will implement greater tests after string class.
        bool testCompact()
        {
            BufferManager someBuffer{12};
            someBuffer.willExpand(5);
            return (5 == someBuffer.getCapacity())? true : false;
        }
        bool testGetCapacity()
        {
            BufferManager someBuffer{12};
            return (12 == someBuffer.getCapacity())? true : false;
        }
        bool testGetBuffer()
        {
            BufferManager someBuffer{12};
            someBuffer.setBuffer();
            return (nullptr == someBuffer.getBuffer())? true : false;
        }

   
        
        T* copyData(T* aBuffer, size_t aCapacity, size_t aCopyCount)
        {
            T* theResult = (new T[aCapacity]);
            for (size_t i = 0; i < aCopyCount; i++)
            {
                theResult[i] = aBuffer[i];
            }
                return theResult;
        }
       
        // copy a buffer starting at aPos without putting null char at the end
        BufferManager& copy_to_buffer_at(int aIndex, const T* aBuffer)
        { // aIndex is the starting index of the first char of aBuffer
            for (int i = 0; i < strlen(aBuffer); ++i)
            {
                buffer_ptr[aIndex + i] = aBuffer[i];
            } // not putting null char
                    return *this;
        }

        // copy a buffer starting at aPos without putting null char at the end overloading, has aMaxCopyLen
        BufferManager& copy_to_buffer_at(int aIndex, const T* aBuffer, int aMaxCopyLen)
        { // aIndex is the starting index of the first char of aBuffer
            if (aMaxCopyLen > strlen(aBuffer))
            { // make sure aMaxCopyLen is not over board
                for (int i = 0; i < strlen(aBuffer); ++i)
                {
                    buffer_ptr[aIndex + i] = aBuffer[i];
                } // not putting null char
                for (int i = strlen(aBuffer); i < aMaxCopyLen; ++i)
                {
                    buffer_ptr[aIndex + i] = 32; //why 32
                }
            }
            else if (aMaxCopyLen <= strlen(aBuffer))
            {
                for (int i = 0; i < aMaxCopyLen; ++i)
                {
                    buffer_ptr[aIndex + i] = aBuffer[i];
                } // not putting null char
            }
            return *this;
        }
        
        // take the porting of the chars starting at startingPos ending at endingPos and shift right by shiftCount, not putting null char at the end
        BufferManager& shift_buffer_right(size_t shiftCount, int startingIndex, int endingIndex)
        {
            for (int i = endingIndex; i >= startingIndex; --i)
            {
                buffer_ptr[i + shiftCount] = buffer_ptr[i];
            }
            return *this;
        }
        
        // take the porting of the chars starting at startingPos ending at endingPos and shift left by shiftCount, not putting null char at the end
        BufferManager& shift_buffer_left(size_t shiftCount, int startingIndex, int endingIndex)
        {
            for (int i = startingIndex; i <= endingIndex; ++i)
            {
                buffer_ptr[i - shiftCount] = buffer_ptr[i];
            }
            return *this;
        }
        
        void setCapacity(int value=0) //only for testing
        {
            capacity = value;
        }
        void setBuffer() //only for testing
        {
            buffer_ptr = nullptr;
        }
        
        void setLength(int value) //only for testing
        {
            length = value;
        }
    protected:
        T*                      buffer_ptr;  //pointer to the beginning of buffer
        size_t                  capacity;    //memory allocated to buffer
        size_t                  length;      //this does not include null
    };
}

#endif



//dispatching
