#include <iostream>
#include <sstream>
#include <string>
#include "Testable.hpp"
#include "BufferManager.hpp"
#include "autotest.hpp"
#include "Tracker.hpp"
#include "String.hpp"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <memory>

int main(int argc, const char * argv[])
{
  static const char* kMsgs[]={"FAIL","PASS"};
  if(argc>1) {
   std::string temp(argv[1]);
    std::stringstream theOutput;
  
    srand(static_cast<uint32_t>(time(NULL)));
    //std::string temp = "insert";
    
      
    if("compile"==temp) {
        std::cout << temp << " test " << kMsgs[true] << "\n";
    }
    else if("OCF"==temp) {
        std::cout << temp << " test " << kMsgs[doOCFTests(theOutput)] << "\n";
    }
    else if("insert"==temp) {
        std::cout << temp << " test " << kMsgs[doInsertTests(theOutput)] << "\n";
    }
    else if("append"==temp) {
      std::cout << temp << " test " << kMsgs[doAppendTests(theOutput)] << "\n";
    }
    else if("replace"==temp) {
        std::cout << temp << " test " << kMsgs[doReplaceTests(theOutput)] << "\n";
    }
    else if("erase"==temp) {
      std::cout << temp << " test " << kMsgs[doEraseTests(theOutput)] << "\n";
    }
    else if("search"==temp) {
      std::cout << temp << " test " << kMsgs[doSearchTests(theOutput)] << "\n";
    }
    else if("compare"==temp) {
        std::cout << temp << " test " << kMsgs[doCompareTests(theOutput)] << "\n";
    }
    else if("speed"==temp) {
        std::cout << temp << " test " << kMsgs[doSpeedTest(theOutput)] << "\n";
    }
    std::cout << theOutput.str() << "\n";
  }
	return 0;
}

