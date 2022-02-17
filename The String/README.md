# WI22-Assignment3
Let's build our own string class

### Due: Feb 7, 11:30p (PST)

## Preface

We've spent the last few weeks covering the intricacies of C++ classes in considerable detail. Now it's your turn to create your first intermediate stand-alone class.

## Welcome to JobCo!

You've just started a new internship at JobCo, a chic software company in the heart of Silicon Valley that sells party balloons with integrated block-chain tracking. You've met your new manager, Chloe, who introduces you to the rest of the team. As you are wisked through the office, you race past a herd of zombies that are wandering aimlessly in the break room. "Oh my goodness", you say, in disbelief.  "Don't let them bother you", Chloe says smiling, "that's just the marketing department taking a lunch break". JobCo is going to be very interesting.

### Your FIRST Sprint Meeting

The next morning you get to sit in on your very first "Sprint Meeting" where the team discusses the work they're going to accomplish for the week. Each of the engineers talks briefly about their challenges and expected output. At last, all eyes drop onto you. Before panic seizes you, Chloes says, "Hey everyone, this is our new summer intern!". The team smiles knowingly, fully expecting you to soon become lunch for the Marketing department.  What happens next is mostly a blur. For one, you don't remember actually saying anything. But suddenly you realize that Chloe has tasked you with delivering some mission critical code, and FAST!  

### Your Team Makes a Decision

Just before the end of the standup meeting, Morris (a performance engineer) raises the topic of how slowly the application is performing. "Seriously", he says, "the app is running 5x slower today than it was a month ago". "What we need", he continues, "is someone to rewrite our string class to stop all the unnecessary memory allocations and performance problems."

Never one to miss an opportunity, Chloe exclaimed, "Great -- our new intern can build us a new string class this Sprint!". Sade, a Rady School student and UX designer on the team, says, "Hold on, why can't we just use the std::string class provided by the STL? Won't that be cheaper than building our own?"  Morris can barely contain himeself. "No!", he chides, "the STL is great in general, but it's way too big, and I just know we can build something smaller and faster!"

Sadly, no amount of arguing about re-inventing the wheel (or adhering to the DRY principle) would stop Morris and Chloe from building their own string class. Welcome to Silicon Valley. :)

## Assignment Details

String classes provide an object-oriented solution to managing character buffers in an application. Most modern applications have to manage strings to some degree, but for some applications, like word-processors and browsers, string management can have a tremendous impact on performance and memory management.

In this assignment, you are going to build a string class using an "aspect-oriented" design technique.  Instead of building one (large) class, you're going to assemble your `String` class from several smaller, "special-purpose" classes, like `BufferManager'.  You might make other little helper classes for other features. 

> NOTE: You may not use the `std::string` class (or derivatives) to build your `String` class.  You can use `std::string` as a tool to help you do testing, like we do in the autograder.  You may use library functions, like `std::strcpy`, `std::memcpy`, `std::strlen`. and so forth. 

### Class interfaces (incomplete)

Take a look at `String.hpp`. At first glance, it looks like you have 50+ methods to implement in the `String` class. If you are careful and thoughtful, however, you can reuse nearly half of your methods, and you can write much less code.   In our solution, for example, we only had to implement about 25 methods (the rest reused the ones we wrote).  Most of our methods are fewer than 4 lines of code.  Keep in mind that your `String` class should worry about `String` operations, and leave buffer management to your `BufferManager` class.  

Also notice that many interfaces are repeated -- once with `String`, and once with `const char*`. That's so your new `String` class is compatible with old-school C-strings. As you're building your code, consider how you might write your code so that you can handle both types with just one method.    
> NOTE: Your project won't successfully build until you write basic versions of each of your methods.  The auto-tester is expecting them to be available.

---

### Part 1. -- Build upon your BufferManager<> template class

You will reuse the `BufferManager` class you built last week. 

The job of `BufferManager` class is to allocate, manage, and (eventually) delete the underying heap-buffer that the `String` class uses to hold string information (the text users assign/set/change in the string). In particular, `BufferManager` will:

1. Allocate a heap memory buffer to contain your string data (chars)
3. Always manages the buffer capacity according to a policy you set
4. Grow/shrink the heap-buffer when your user changes the string 
5. Automatically delete the underlying heap-buffer when the `String` object is destroyed

The BufferManager class wants to be as efficient as possible. As the user changes the string, this class should grow/shrink the underlying buffer in an time/space efficient way as possible.  We discussed this challenge in lecture, so refer to our discussion on this topic.

> It's up to you to decide whether you make your `String` class a sub-class of `BufferManager`, or simply an owner of a `BufferManager` instance (IS-A vs HAS-A). Both can be made to work.

#### Scenario 1 -- Construction

When someone makes a new `String`, it is empty by default. Empty strings should occupy no space. Typically, the buffer pointer that the `BufferManager` uses to manage the buffer is null at this point.  

```
String theString; //an empty string with length 0
```

#### Scenario 2 -- Assignment/Copy construction

It is possible to create a `String` class, and give it a non-null initializer value in the constructor:

```
String theString("hello world"); //this string requires buffer memory right from the start
```

In this scenario, the `BufferManager` needs to pre-allocate space on the heap for the buffer that will hold the contents of the `String`. Again, since time/space efficiency is important, you should think carefully about how large your buffer should be. 

1. Should it be exactly as large as the initialize string (+1 for the null terminator?)
2. Should be somewhat larger, so the string could grow "a little" without having to resize your buffer

#### Scenario 3 -- Mutating (add/insert/delete) some/all of your string

In this scenario, the user is using part of the mutatation API to add/delete/insert characters into an existing string. This can change the size requirements of the underlying buffer. 

```
String theString("hello world"); //string length is 11 (+1 for null terminator)
theString.append(" it's a really fine day in San Diego!"); 
//we just added nearly 40 characters to the string; resize buffer?
```

It's likely that your buffer will need to be resized at this point. We discussed the implications of that process in lecture. If the length of your current buffer + the length of the appended string is more than your current buffer can hold, you'll do something like this:

1. allocate a new buffer, big enough to hold original string + new string + null terminator
2. copy the contents of the old buffer to the new buffer
3. copy the content being "appended" to the end of the new buffer
4. delete the original buffer
5. set your internal buffer pointer to your buffer

---

### Part 2. -- 

It's time to actually build your `String` class.  If you open `String.hpp` you'll notice that it seems incomplete.

If you're confused about what one of your `String` methods should do -- try looking up that same method on the std::string class provided by the C++ library. We modeled our class on theirs.  If you're still confused, come to office hours.

#### -- The First Challenge with This Assignment is MUTABILITY

You might realize that managing the character buffer in your class can be a challenge. On the one hand, we want to make the code fast, so our algorithms needs to be efficient and simple. Second, we have to handle many types of changes to our character buffer, including:

1. handling empty strings
2. appending characters
3. inserting characters anywhere in the string
4. replacing substrings with other substrings
5. removing characters from anywhere in the string

> NOTE: Operations that mutate the a `String` might require that your underlying buffer grow/shink in size. So methods that MUTATE the string will likely interact with methods you write in your `BufferManager<>` class.  The key here is the `BufferManager` should focus on making sure you have enough memory for the changes you want to make to your string, and the `String` class should worry about manipulating data in the buffer, assuming the buffer is properly sized. 


#### -- Design your code before you implement ANYTHING...

One of the most interesting aspects of a string class, is how much code gets shared and reused between different operations.  For example, both **append** and **insert** operations cause the string to get grow.  The **replace** is a combination of erase and insert. There are many other such relationships.

Before your write any code, take time to think about the use-case scenarios. You can append, insert, erase, and replace, and each of these operations can happen on some, or just a part, of your existing string. If you take time to work through these scenarios, a "story" will emerge. You'll see that there are a set of *basic* operations that can be used to implement all the top-level string methods. Software design is all about thinking through the story of your code, and finding the small operations that can be combined to build larger, more complex functionality.  

--- 

### Part 3. -- Implement Relational Operators

Your next step is to add support for the relational operators (`<, >, <=, >=, ==, !=`). These operators are used to _compare_ strings, but also used if you want to _sort_ them. 

There are 6 operators, with two versions of each (one for `String` and one for `const char*` compatibility), for a total of 12 methods in all.  However, if you're smart about how you write your code, you can actually implement far fewer. First, it's possible to implement the `char*` version, and let the `String` version call the `char*` version (if you're careful).  Second, it is possible to implement some of your operators in terms of others. For example: `X==Y` and `X!=Y` are logical opposites. That means you can impelement one in terms of the other. `X!=Y` is the same as `!(X==Y)`. 

Try to implement some of your relational operators in terms of the logical opposites. 

--- 

### Part 4. -- Implement the Find() methods

In this step, you will add support for the `Find()` method, which will allow a user of your class to search within the given string for a character, or sub-string. If found, these methods return the index position within the `String` where the char/substring was found, searching left-to-right.  As with the relational operators, you should be able to write reusable code that works for either `String` or `const char*`. 

```cpp

  //return offset of target in string, or -1 to indicate "not found"
  //anOffset indicates where in your string to start searching...
  int find(const T &aTarget, size_t anOffset=0) const {
    return 0;
  }

  int find(const char *aBuffer, size_t anOffset=0) const {
    return 0;
  }
  
  int find(char aChar, size_t anOffset=0) const {
    return 0;
  }  
```

---

### Part 5. -- Testing your String class implementation 

See? Building a basic string class isn't all that hard. But making it run fast, and ensuring that uses memory efficiently takes considerably more effort. Finding the right balance between memory usage and performance can be a challenge.  In order to test your memory utilization and performance, you must write your own tests. To help you, we've added two extra functions in the StringTester class:

Still - no self-respecting engineer would consider the job done unless they had also provided a complete set of tests to ensure that the solution worked as designed. Well, we've already provided a basic testing harness for you, contained in the StringTester file. 

Make sure you test all the methods in the `String` class.

> It is up to you to fully implement the tests for the `String` class. You might want to make (but are not required) tests for the `BufferManager` class -- because it can help you get your assignment done more quickly. 

A great way to test a class is to compare against a baseline. In this case C++ provides the std::string which has the same kinds of methods that you are building for your `String` class. So a clever way to test, is to create two objects: your string, and a std::string, and do the same operations. Then compare the results. Here's an example:

```
const char* theBuffer="hello world";
ECE141::String theString(theBuffer); //initialize with theBuffer
std::string    theSTLString(theBuffer); //also intialize with theBuffer

    //now validate that we the strings are the same
if(!(theString==theSTLString.c_str())) {  //SHOULD  be valid!
  std::cout << "string init failed!\n";
  return false;
}
```

#### Speed Test

After you have your tests working, and your class is fully implemented, you can try out the speed test we provided in the `Testing` class.  You'll have to uncomment the call (and the code) in the `runSpeedTest()` function.

## Grading

```
OCF Tests: 10pts
Search Tests: 10pts
Compare Tests: 15pts
Insert Tests: 15pts
Append Tests: 15pts
Replace Tests: 10pts
Erase Tests: 10pts
Performance Tests: 5pts
Coding Style: 10pts
```

As we explained earlier, in addition to passing the basic string tests (StringTest), your code will be measured for memory efficiency and performance. Our grading test harness will generate 1000's of strings and measure your memory usage. So make sure you test performance and memory efficiency carefully.


## Code Style Guide

This isn’t your first class on software or programming, and you’re probably wondering how we expect your code to be structured and formatted.  From the perspective of our auto-grader, structure and format are completely irrelevant. However, your instructors also will be viewing your code as well, so you would be wise to adhere to a few rules of thumb. 

### Format and Clarity

Your code should be formatted to be easily readable by anyone with more than 1 year of programming experience.  Here are some guidelines for things that matter:

- Avoid dense and complicated code
- Be consistent!  Choose a coding standard for yourself and stick with it
- Partition your logic into class methods as needed to maintain clarity
- Document your code with comments that clearly indicate what you’re doing at a high level

## Submitting Your Work - Due Feb 7th at 11:30p (PST)

You’ll recall that your work is due by 11:15pm (PST).  We strongly recommend that you aim for 6p (PST) as to avoid the last minute mishaps that frequently occur when panic related to an impending deliverable begins, and we all tend to make silly mistakes.  

As we’ve said in lecture, you will turn your work in using GitHub. GitHub is an online code repository.  Managing code can be very confusing, but GitHub makes the process fairly easy. And the way we’re going to handle code in this class is even simpler still.  More on that later.

With that said, please understand that when you submit your work via GitHub, your changes are automatically timestamped. Meta data in the code repository makes it plainly obvious to humans and computers alike when your submission arrived.  This is worth mentioning, because the github timestamps on your submissions will be used to to arbitrate whether you turned your work in on time or not. 

Your homework will usually be auto-graded by “Vlad the Compiler” — otherwise known as our software-based auto-grader.  Vlad can be a bit harsh when it comes to scoring homework (see the syllabus), but he does have a somewhat casual relationship with deadlines.  During Grad-school, Vlad often spent spring-break in Cabo-San-Lucas where he learned to enjoy siestas.  Most nights, Vlad awakens from his last-afternoon siesta around midnight, to begin the process of grading your assignments. In other words, you can generally count on a 45 minute grace period for turning in your work. We strongly suggest that you do not try his patience.

**NOTE**: Please don't submit object or executable files with your submissions. Only check in text files (source, make, student.json, and so forth).  

Please make sure that you fill out your student.json file. We need your name, PID, email and the operating system you used for your work. For the operating system attribute, please specify "windows", "mac" or "linux". 

```
{
  "name"  : "Your Name",
  "pid"   : "Your StudentId",
  "email" : "Your Email",
  "os"    : "windows|mac|linux",
  "effort": "# of hours you spent on this assignment",
  "course": "ece141a"
}
```

### Getting Help

You can talk with your peers about this problem. You can ask your instructors about this too. But you cannot use any other code for reference in solving these problems. If you're really stuck with an algorithm, join us in the programming dojo to get unblocked. It's really essential that you think about this challenge and work to solve it yourself.

## EXTRA Credit!

If you're feeling ambitious, you can earn extra credit if you complete this additional challenge.

### Adding support for operator+ 

Supporting operator+ may force you to learn a powerful new idiom in C++ on your own, before we discuss it in class. 
Let's take a look at how operator+ is used:

```
const char* thePrefix = "hello";
String theSuffix(" there");
String s3 = thePrefix + theSuffix;  //invoke operator+
```

In our sample code, we are concatenating a standard C-String with an String. What makes this curious, is that C-Strings don't offer methods of their own. Only objects (and sometimes classes) can do that. So how does this work? The secret is revealed when you realize that these are not members of a class, but rather, standalone functions. 

If you're up for the challenge, you can implement these methods:

```
String operator+(const String& lhs, const String& rhs);
String operator+(const String& lhs, const char* rhs);
String operator+(const char* lhs, const String& rhs);
```
