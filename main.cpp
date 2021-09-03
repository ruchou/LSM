#include <tuple>
#include <map>
#include <set>
#include <optional>
#include <iostream>

#include "lsm_template.h"
#include "lsm_impl.h"

int main() {
    Node *r;
    std::map<Node*,std::set<int>> esr;
    std::map<int,int> Cr ;

    std::tie(r,esr,Cr) = init();


}
