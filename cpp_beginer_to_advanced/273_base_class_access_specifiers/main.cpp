#include <iostream>
#include "player.h"
#include "nurse.h"
#include "engineer.h"
#include "person.h"

int main(int argc, char* argv[]) {
    Person p1 {"Daniel Licht", 38, "Toronto, Canada"};
    std::cout << p1 << '\n';

    Player player1;
    player1.play();
    std::cout << player1 << '\n';

    player1.m_fullname = "Not a fullname";

    std::cout << player1 << '\n';

    Nurse n1;
    n1.treat_well();
    std::cout << n1 << '\n';

    Engineer e1; 
    e1.build_something();
    std::cout << e1 << '\n';
    
    return EXIT_SUCCESS;
}