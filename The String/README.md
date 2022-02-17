#Let's build our own string class



## Preface

String classes provide an object-oriented solution to managing character buffers in an application. Most modern applications have to manage strings to some degree, but for some applications, like word-processors and browsers, string management can have a tremendous impact on performance and memory management.

In this program, I am going to build a string class using an "aspect-oriented" design technique.  Instead of building one (large) class, I will assemble my `String` class from several smaller, "special-purpose" classes, like `BufferManager'. 


### Class interfaces

Take a look at `String.hpp`. At first glance, it looks like you have 50+ methods to implement in the `String` class. If you are careful and thoughtful, however, you can reuse nearly half of your methods, and you can write much less code.   In our solution, for example, we only had to implement about 25 methods (the rest reused the ones we wrote).  Most of our methods are fewer than 4 lines of code.  Keep in mind that your `String` class should worry about `String` operations, and leave buffer management to your `BufferManager` class.  

Also notice that many interfaces are repeated -- once with `String`, and once with `const char*`. That's so your new `String` class is compatible with old-school C-strings. As you're building your code, consider how you might write your code so that you can handle both types with just one method.    

---

### Part 1. -- Build upon your BufferManager<> template class

The job of `BufferManager` class is to allocate, manage, and (eventually) delete the underying heap-buffer that the `String` class uses to hold string information (the text users assign/set/change in the string). In particular, `BufferManager` will:

1. Allocate a heap memory buffer to contain your string data (chars)
3. Always manages the buffer capacity according to a policy you set
4. Grow/shrink the heap-buffer when your user changes the string 
5. Automatically delete the underlying heap-buffer when the `String` object is destroyed

The BufferManager class wants to be as efficient as possible. As the user changes the string, this class should grow/shrink the underlying buffer in an time/space efficient way as possible.

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

It's likely that your buffer will need to be resized at this point. If the length of your current buffer + the length of the appended string is more than your current buffer can hold, you'll do something like this:

1. allocate a new buffer, big enough to hold original string + new string + null terminator
2. copy the contents of the old buffer to the new buffer
3. copy the content being "appended" to the end of the new buffer
4. delete the original buffer
5. set your internal buffer pointer to your buffer

---

### Part 2. -- 

It's time to actually build your `String` class.  If you open `String.hpp` you'll notice that it seems incomplete.

#### -- The First Challenge with This program is MUTABILITY

You might realize that managing the character buffer in your class can be a challenge. On the one hand, we want to make the code fast, so our algorithms needs to be efficient and simple. Second, we have to handle many types of changes to our character buffer, including:

1. handling empty strings
2. appending characters
3. inserting characters anywhere in the string
4. replacing substrings with other substrings
5. removing characters from anywhere in the string

> NOTE: Operations that mutate the a `String` might require that your underlying buffer grow/shink in size. So methods that MUTATE the string will likely interact with methods you write in your `BufferManager<>` class.  The key here is the `BufferManager` should focus on making sure you have enough memory for the changes you want to make to your string, and the `String` class should worry about manipulating data in the buffer, assuming the buffer is properly sized. 


#### -- Design your code before you implement ANYTHING...

One of the most interesting aspects of a string class, is how much code gets shared and reused between different operations.  For example, both **append** and **insert** operations cause the string to get grow.  The **replace** is a combination of erase and insert. There are many other such relationships.  

--- 

### Part 3. -- Implement Relational Operators

Your next step is to add support for the relational operators (`<, >, <=, >=, ==, !=`). These operators are used to _compare_ strings, but also used if you want to _sort_ them. 

There are 6 operators, with two versions of each (one for `String` and one for `const char*` compatibility), for a total of 12 methods in all.  However, if you're smart about how you write your code, you can actually implement far fewer. First, it's possible to implement the `char*` version, and let the `String` version call the `char*` version (if you're careful).  Second, it is possible to implement some of your operators in terms of others. For example: `X==Y` and `X!=Y` are logical opposites. That means you can impelement one in terms of the other. `X!=Y` is the same as `!(X==Y)`. 

Try to implement some of your relational operators in terms of the logical opposites. 

--- 

### Part 4. -- Implement the Find() methods

In this step, I will add support for the `Find()` method, which will allow a user of your class to search within the given string for a character, or sub-string. If found, these methods return the index position within the `String` where the char/substring was found, searching left-to-right.  As with the relational operators, I should be able to write reusable code that works for either `String` or `const char*`. 

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

