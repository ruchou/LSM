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

void TestCase::testMerge2() {
    this->reset();


    for (int i = 0; i < 10; i++) {
        cout << "insert " << "Key=" << i << endl;
        upsert(this->root, i);
    }

    cout << "compact" << endl;
    compact(this->root, this->root);
    compact(this->root, this->root->next);

    int k = 5;
    int t = search(this->root, k);
    cout << "search key:" << k << " return: " << t << endl;

}

void TestCase::testMerge3() {
    this->reset();

    for (int i = 0; i < 10; i++) {
        cout << "insert " << "Key=" << i << endl;
        upsert(this->root, i);
    }

    cout << "compact" << endl;
    compact(this->root, this->root);

    for (int i = 20; i < 30; i++) {
        cout << "insert " << "Key=" << i << endl;
        upsert(this->root, i);
    }

    cout << "compact" << endl;
    compact(this->root, this->root);


    for (int i = 50; i < 60; i++) {
        cout << "insert " << "Key=" << i << endl;
        upsert(this->root, i);
    }

    cout << "compact" << endl;
    compact(this->root, this->root);

    printContent(this->root);
}

void TestCase::printContent(Node<int> *n) {
    if (n->nodeType == memtableNode) {
        cout << "Memtable Content" << endl;
        for (int i = 0; i < n->tableLen; i++) {
            int key, timestamp;
            std::tie(key, timestamp) = n->table->at(i);
            cout << "K: " << key << "->" << " T: " << timestamp << endl;
        }

    } else {
        cout << "SStable Content" << endl;
        for (int i = 0; i < n->file->size; i++) {
            int key, timestamp;
            std::tie(key, timestamp) = n->file->ram->at(i);
            cout << "K: " << key << "->" << " T: " << timestamp << endl;
        }
    }
    if (n->next != nullptr)
        printContent(n->next);

}





