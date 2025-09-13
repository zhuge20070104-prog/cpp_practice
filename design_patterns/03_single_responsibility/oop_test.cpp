#include <iostream>
#include <string>
#include "gtest/gtest.h"
#include "journal.h"
#include "persisit_mgr.h"


GTEST_TEST(OopTest, TestInheritance) {
    Journal j {"Dear Diary"};
    j.add_entry("I ate a bug");
    j.add_entry("I cried today");

    PersisitMgr::save(j, "diary.txt");
}

