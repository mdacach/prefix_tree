# prefix_tree

Prefix Tree ([Trie](https://en.wikipedia.org/wiki/Trie)) implementation in Modern C++17.

This is a structure I have coded for work to store our in-memory database. It performs much better than our previous structure,
being up to 6 times as fast in a specific computation, while being memory-efficient too. A Trie is generally used for Strings application,
but it can be generalized to any "sequence", as was the case then.



Tags:

* C++17
* Test-Driven Development, TDD, BDD
* Unit Tests
* Best practices, Clean Code
* Documentation
* Data Structures, Algorithms

Tools:

* Clang-format
* Clang-tidy
* Cppcheck
* Catch2
* Sanitizers
* Doxygen
* CLion IDE
* Linux
 
Tool usage based on:

* [Jason Turner's setup](https://github.com/cpp-best-practices/cmake_conan_boilerplate_template)
* [Euripedes' ctdsp setup](https://github.com/euripedesrocha/ctdsp)

TODO:
* Use https://github.com/TartanLlama/optional to return an optional to reference of info. (Optimization)
* Add iterator to structure.
* Improve the template programming.
