#include <tuple>
#include <map>
#include <set>
#include <optional>
#include <iostream>
#include <cassert>

#include "include/lsm_impl.h"
#include "include/lsm_template.h"

using std::cout;
using std::end;

int main() {
    Node<int> *r;
    std::map<Node<int> *, std::set<int>> esr;
    std::map<int, std::optional<int>> Vr;

    std::tie(r, esr, Vr) = init();

    search(r, 10);
}
