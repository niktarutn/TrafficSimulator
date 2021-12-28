#Instructions

1. Create a .cpp file in "tests" folder (ClassTest.cpp)
2. Include  *<gtest/gtest.h>* and *Class.cpp*. If you came across linking problem, include needed source files :)
3. To CMake add *add_executable* and *target_link_libraries* (you may see how testing for person is done)
4. Finally, don't forget to add name of your test to *gtest_discover_tests(person_test)* 