//
// Created by YanRu Jhou on 2021/9/13.
//

#include "TestCase.h"
#include <random>
using std::cout;
using std::end;
using std::endl;

TestCase::TestCase(Node<int> *root, std::map<Node<int> *, std::set<int>> esr, std::map<int, std::optional<int>> Vr) {
    this->root = root;
    this->esr = esr;
    this->Vr = Vr;
}


TestCase::TestCase() {
    this->root = new Node<int>();
    this->esr = std::map<Node<int> *, std::set<int>>();
    this->Vr = std::map<int, std::optional<int>>();
}

void TestCase::reset() {

    std::tie(this->root, this->esr, this->Vr) = init();

}

void TestCase::printContent(Node<int> *n) {
    if (n->nodeType == memtableNode) {
        cout << "Memtable Content" << endl;
        for (int i = 0; i < n->table->size(); i++) {
            int key, timestamp;
            std::tie(key, timestamp) = n->table->at(i);
            cout << "K: " << key << "->" << " T: " << timestamp << endl;
        }

    } else {
        cout << "SStable Content" << endl;
        for (int i = 0; i < n->file->disk_cont->size(); i++) {
            int key, timestamp;
            std::tie(key, timestamp) = n->file->disk_cont->at(i);
            cout << "K: " << key << "->" << " T: " << timestamp << endl;
        }
    }
    if (n->next != nullptr)
        printContent(n->next);

}

int genNumber(int min, int max) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(min, max); // distribution in range [1, 6]

    return dist(rng);
}

void TestCase::testSStableMerge() {
    this->reset();

    cout << "Upsert Elements" << endl;
    for (int i = 0; i < 10; i++) {
        upsert(this->root, i, i);
    }
    this->printContent(this->root);

    cout << "Compact" << endl;
    compact(this->root, this->root);
    this->printContent(this->root);


    cout << "Upsert Elements" << endl;
    for (int i = 20; i < 30; i++) {
        upsert(this->root, i, i);
    }
    this->printContent(this->root);

    cout << "Compact" << endl;
    compact(this->root, this->root);
    this->printContent(this->root);


    cout << "Upsert Elements" << endl;
    for (int i = 30; i < 40; i++) {
        upsert(this->root, i, i);
    }
    this->printContent(this->root);

    cout << "Compact" << endl;
    compact(this->root, this->root);
    this->printContent(this->root);


    cout << "Upsert Elements" << endl;
    for (int i = 40; i < 50; i++) {
        upsert(this->root, i, i);
    }
    this->printContent(this->root);

    cout << "Compact" << endl;
    compact(this->root, this->root);
    this->printContent(this->root);


    cout << "Upsert Elements" << endl;
    for (int i = 40; i < 50; i++) {
        upsert(this->root, genNumber(40, 45), i);
    }
    this->printContent(this->root);

    cout << "Compact" << endl;
    compact(this->root, this->root);
    this->printContent(this->root);

    for (int i = 0; i < 200; i++) {
        cout << "Upsert Elements" << endl;
        for (int j = 0; j < 10; j++) {
            upsert(this->root, genNumber(0, 50), i);
        }
        cout << "Compact" << endl;
compact(this->root, this->root);
}

this->printContent(this->root);

int k = 5;
int t = search(this->root, k);
cout << "Key is: " << k << ", t is: " << t << endl;
}

void TestCase::test1() {
this->reset();

for (int i= 0; i<10;i++){
upsert(this->root, 1, i);
}
this->printContent(this->root);

int key = 1;
int res = search(this->root, key);
cout<<"Search key: "<<key<<" Ret : "<<res<<endl;

cout<<"Compact"<<endl;
compact(this->root, this->root);
this->printContent(this->root);



}



