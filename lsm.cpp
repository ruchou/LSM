//
// Created by YanRu Jhou on 2021/9/2.
//
#include <tuple>
#include <map>
#include <set>
#include <optional>
#include "lsm.h"

std::tuple<Node *, std::map<Node *, std::set<int>>, std::map<int, int>> init() {
    Node *r = new Node();
    r->tableK.reserve(2*B);
    r->tableT.reserve(2*B);
    r->tableLen = 0;
    r->next = nullptr;
    r->nodeType = memtableNode;

    std::map<Node *, std::set<int>> esr;
    std::map<int, int> Cr;

    return std::make_tuple(r, esr, Cr);

}

std::optional<int> inContents(Node *n, int k) {
    if (n->nodeType == memtableNode) {
        int i = n->tableLen - 1;
        bool flag = false;

        while (i >= 0 && !flag) {
            if (n->tableK[i] == k) {
                flag = true;
            } else {
                i -= 1;
            }
        }

        if (flag) {
            return n->tableT[i];
        } else {
            return {};
        }
    } else {
        bool b;
        int i;
        std::tie(b, i) = arrFind(n->tableK, n->tableLen, k);
        if (b) {
            return n->tableT[i];
        } else {
            return {};
        }
    }
}

bool atCapacity(Node* n){
    if(n->tableLen < n->tableK.capacity())
        return false;
    else
        return true;
}

//TODO findNExt chooseNext insertNode