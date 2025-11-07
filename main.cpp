#ifdef MAIN

#include "ABDQ.hpp"
#include "ABS.hpp"
#include "ABQ.hpp"
#include "LLDQ.hpp"
#include <iostream>
#include <string>

/*
    - LEAVE THE IFDEF GUARDS TO KEEP YOUR MAIN WITHOUT CONFLICTING WITH GRADESCOPE!
    - Test your code in this main and run locally with the RunMain configuration in CLion, or
    through your own command line compilation. Make sure to add flag "-DMAIN" to your compilation so this
    main function can compile.

*/

int main() {
    LLDQ<std::string> my_deque;
    my_deque.pushFront("Hellooooooooooooooooo");
    my_deque.pushFront("Woooooooooooooooooooorld");
    my_deque.pushFront("This is a testing message no sso");

    LLDQ<std::string> s3 = my_deque;
    my_deque = s3;

    LLDQ<std::string> s2 = std::move(my_deque);
    my_deque = std::move(s2);
    
    size_t n = my_deque.getSize();

    for (size_t i = 0; i < n; i++) {
        std::cout << my_deque.back() << '\n';
        my_deque.popBack();
    }

    return 0;
}


#endif