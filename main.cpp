// #ifdef MAIN

#include "ABS.hpp"
#include <iostream>
#include <string>

/*
    - LEAVE THE IFDEF GUARDS TO KEEP YOUR MAIN WITHOUT CONFLICTING WITH GRADESCOPE!
    - Test your code in this main and run locally with the RunMain configuration in CLion, or
    through your own command line compilation. Make sure to add flag "-DMAIN" to your compilation so this
    main function can compile.

*/

int main() {
    ABS<std::string> my_stack;
    my_stack.push("Hellooooooooooooooooo");
    my_stack.push("Woooooooooooooooooooorld");
    my_stack.push("This is a testing message no sso");

    for (size_t i = 0; i < my_stack.getSize(); i++) {
        std::cout << my_stack.peek() << '\n';
        my_stack.pop();
    }

    return 0;
}


// #endif