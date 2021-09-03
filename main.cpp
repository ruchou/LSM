#include <tuple>
#include <map>
#include <set>
#include <optional>
#include <iostream>

#include "lsm_impl.h"

int main() {
    Node *r;
    std::map<Node*,std::set<int>> esr;
    std::map<int,int> Cr ;

    std::tie(r,esr,Cr) = init();
    std::optional<int> v = inContents(r,10);
    std::cout <<v.value_or(0)<< std::endl;

    bool isFull = atCapacity(r);
    std::cout << isFull <<std::endl;

    bool op = addContents(r,10,20);

    std::cout << op << std::endl;

    v  = inContents(r,10);
    std::cout <<v.value_or(0)<< std::endl;



}
