#include <tuple>
#include <map>
#include <set>
#include <optional>
#include <iostream>
#include <cassert>

#include "test/TestCase.h"
using std::cout;
using std::endl;

int main() {
    TestCase T1;
    cout << "------------Case 0----------------------" << endl;
    T1.test1();
    cout << "------------Case 1----------------------" << endl;
    T1.testMerge();
    cout << "------------Case 2----------------------" << endl;
    T1.testMerge2();
    cout << "------------Case 3----------------------" << endl;
    T1.testMerge3();
    cout << "------------Case 4----------------------" << endl;
    T1.testMerge4();
    cout << "------------Case 5----------------------" << endl;
    T1.testMerge5();

    return 1;
}
