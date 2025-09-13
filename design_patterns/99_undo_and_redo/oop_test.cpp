#include <iostream>
#include <string>
#include <sstream>
#include "log.h"
#include <utility>
#include <memory>
#include <cstring>
#include <vector>
#include <iterator>
#include "undo_and_redo.hpp"

#define BOOST_TEST_MODULE  UndoAndRedo
#include "test.hpp"


BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())


BOOST_AUTO_TEST_CASE(UndoAndRedoTest) {
   BankAccount ba {100};
   ba.deposit(50); // 150
   ba.deposit(25); // 175

   std::cout << ba << "\n";
   ba.undo(); 
   std::cout << "Undo 1: " << ba << "\n";  // 150
   ba.undo();
   std::cout << "Undo 2: " << ba << "\n";  // 100

    ba.redo();
    std::cout << "Redo: " << ba << "\n"; // 150
}

BOOST_AUTO_TEST_SUITE_END()
