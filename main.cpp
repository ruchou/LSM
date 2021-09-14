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
    cout << "-------------------------" << endl;
    T1.test1();
    cout << "-------------------------" << endl;
    T1.testMerge();

    return 1;
}
