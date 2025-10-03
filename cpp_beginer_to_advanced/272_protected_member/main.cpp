#include <iostream>
#include "player.h"

int main(int argc, char* argv[]) {
    Player p1 {"Soccer", "Lucifer", "Morningstar"};
    std::cout << p1 << '\n';    
    return EXIT_SUCCESS;
}