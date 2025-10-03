#include <iostream>
#include "player.h"

int main(int argc, char* argv[]) {
    Player p1 {"Football"};
    std::cout << p1 << '\n';


    p1.set_fname("Johnny");
    p1.set_lname("Test");
    std::cout << p1 << '\n';
    
    return EXIT_SUCCESS;
}