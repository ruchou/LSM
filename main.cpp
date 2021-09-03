#include <tuple>
#include <map>
#include <set>
#include <optional>
#include <iostream>

#include "lsm_template.h"
#include "lsm_impl.h"

int main() {
    Node *r;
    std::map<Node *, std::set<int>> esr;
    std::map<int, int> Cr;

    std::tie(r, esr, Cr) = init();

    upsert(r, 10);

    int t = search(r, 10);
    std::cout << t << std::endl;

    upsert(r, 10);
    upsert(r, 10);
    upsert(r, 10);
    upsert(r, 10);
    upsert(r, 10);


    t = search(r, 10);
    std::cout << t << std::endl;

    upsert(r, 5);
    t = search(r, 5);
    std::cout << t << std::endl;

    upsert(r, 5);
    t = search(r, 5);
    std::cout << t << std::endl;

    upsert(r, 5);
    t = search(r, 10);
    std::cout << t << std::endl;

    t = search(r, 15);
    std::cout << t << std::endl;
}
