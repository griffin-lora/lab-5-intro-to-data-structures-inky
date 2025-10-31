// #ifdef MAIN

#include "Array.hpp"
#include "Stack.hpp"
#include <cstddef>
#include <iostream>

/*
    - LEAVE THE IFDEF GUARDS TO KEEP YOUR MAIN WITHOUT CONFLICTING WITH GRADESCOPE!
    - Test your code in this main and run locally with the RunMain configuration in CLion, or
    through your own command line compilation. Make sure to add flag "-DMAIN" to your compilation so this
    main function can compile.

*/

int main() {
    stack<int, array<int>> my_stack;
    my_stack.push(10);
    my_stack.push(20);
    my_stack.push(30);

    std::cout << my_stack.size() << '\n';

    for (size_t i = 0; i < 3; i++) {
        std::cout << my_stack.peek() << '\n';
        my_stack.pop();
    }

    return 0;
}


// #endif