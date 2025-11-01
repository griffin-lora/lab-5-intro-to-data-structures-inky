// #ifdef MAIN

#include "Array.hpp"
#include "LinkedList.hpp"
#include "Stack.hpp"
#include <cstddef>
#include <iostream>
#include <string>

/*
    - LEAVE THE IFDEF GUARDS TO KEEP YOUR MAIN WITHOUT CONFLICTING WITH GRADESCOPE!
    - Test your code in this main and run locally with the RunMain configuration in CLion, or
    through your own command line compilation. Make sure to add flag "-DMAIN" to your compilation so this
    main function can compile.

*/

int main() {
    stack<std::string, array<std::string>> my_stack;
    my_stack.push("Hello");
    my_stack.push("World");
    my_stack.push("I am here");

    stack<std::string, array<std::string>> copy = my_stack;

    copy = my_stack;

    std::cout << my_stack.size() << '\n';

    size_t s = my_stack.size();

    for (size_t i = 0; i < s; i++) {
        std::cout << my_stack.peek() << '\n';
        my_stack.pop();
    }

    return 0;
}


// #endif