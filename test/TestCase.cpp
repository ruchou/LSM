//
// Created by YanRu Jhou on 2021/9/13.
//

#include "TestCase.h"

using std::cout;
using std::end;
using std::endl;

TestCase::TestCase(Node<int> *root, std::map<Node<int> *, std::set<int>> esr, std::map<int, std::optional<int>> Vr) {
    this->root = root;
    this->esr = esr;
    this->Vr = Vr;
}

void TestCase::test1() {
    auto r = this->root;
    auto esr = this->esr;
    auto Vr = this->Vr;

    std::tie(r, esr, Vr) = init();

    int k = 5;
    int time = search(r, k);
    assert(time == -1);
    upsert(r, k); // insert 5 t
    time = search(r, 5); //search 5 with time t
    cout << time << endl;

    upsert(r, k); // insert 5 t
    time = search(r, 5); //search 5 with time t +1
    cout << time << endl; //t+1


    free(r);
}

TestCase::TestCase() {
    this->root = new Node<int>();
    this->esr = std::map<Node<int> *, std::set<int>>();
    this->Vr = std::map<int, std::optional<int>>();
}

void TestCase::reset() {

    std::tie(this->root, this->esr, this->Vr) = init();

}

void TestCase::testMerge() {
    this->reset();


    for (int i = 0; i < 10; i++) {
        cout << "insert " << "Key=" << i << endl;
        upsert(this->root, i);
    }

    cout << "compact" << endl;
    compact(this->root, this->root);
    compact(this->root, this->root->next);

}




