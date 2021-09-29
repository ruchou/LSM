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

void TestCase::testMerge4() {
    this->reset();

    cout << "---------------------------" << endl;
    for (int i = 0; i < 8; i++) {
        cout << "insert " << "Key=" << i << endl;
        upsert(this->root, i);
    }

    this->printContent(this->root);

    int key = 5;
    int res = search(this->root, key);
    cout << "Search Key " << key << ": " << res << endl;

    //upsert only with the value from readClock
    upsert(this->root, 5);
    res = search(this->root, key);
    cout << "Search Key " << key << ": " << res << endl;
    this->printContent(this->root);

    cout << "---------------------------" << endl;
    //compact fail since the size doesn't exceed
    compact(this->root, this->root);
    this->printContent(this->root);

    cout << "---------------------------" << endl;
    upsert(this->root, 10);
    compact(this->root, this->root);
    this->printContent(this->root);


}

void TestCase::testMerge5() {
    this->reset();

    for (int i = 0; i < 9; i++)
        upsert(this->root, 5);
    upsert(this->root, 8);
    this->printContent(this->root);
    cout << "------------------------" << endl;
    compact(this->root, this->root);
    cout << "After Compact" << endl;
    this->printContent(this->root);

    cout << "------------------------" << endl;
    for (int i = 0; i < 10; i++)
        upsert(this->root, i * i);
    this->printContent(this->root);
    cout << "------------------------" << endl;


    compact(this->root, this->root);
    cout << "After Compact" << endl;
    this->printContent(this->root);
    cout << "------------------------" << endl;

}

int genNumber(int min, int max) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(min, max); // distribution in range [1, 6]

    return dist(rng);
}

void TestCase::testMerge6() {
    this->reset();
    cout << "Upsert Elements" << endl;
    for (int i = 0; i < 10; i++) {
        upsert(this->root, genNumber(0, 5));
    }
    this->printContent(this->root);

    cout << "Compact" << endl;
    compact(this->root, this->root);
    this->printContent(this->root);

    cout << "Upsert Elements" << endl;
    for (int i = 0; i < 10; i++) {
        upsert(this->root, genNumber(6, 10));
    }
    this->printContent(this->root);
    cout << "Compact" << endl;
    compact(this->root, this->root);
    this->printContent(this->root);

    cout << "Compact" << endl;
    compact(this->root, this->root);
    this->printContent(this->root);

    cout << "Upsert Elements" << endl;
    for (int i = 0; i < 5; i++) {
        upsert(this->root, genNumber(0, 10));
    }
    this->printContent(this->root);

    int key = 5;
    cout << "search key " << key << endl;
    cout << "Value : " << search(this->root, key) << endl;


    cout << "Upsert Elements" << endl;
    for (int i = 0; i < 5; i++) {
        upsert(this->root, genNumber(0, 20));
    }
    this->printContent(this->root);
    key = 5;
    cout << "search key " << key << endl;
    cout << "Value : " << search(this->root, key) << endl;


    cout << "Compact" << endl;
    compact(this->root, this->root);
    this->printContent(this->root);


}

void TestCase::testSStableMerge() {
    this->reset();

    cout << "Upsert Elements" << endl;
    for (int i = 0; i < 10; i++) {
        upsert(this->root, i);
    }
    this->printContent(this->root);

    cout << "Compact" << endl;
    compact(this->root, this->root);
    this->printContent(this->root);


    cout << "Upsert Elements" << endl;
    for (int i = 20; i < 30; i++) {
        upsert(this->root, i);
    }
    this->printContent(this->root);

    cout << "Compact" << endl;
    compact(this->root, this->root);
    this->printContent(this->root);


    cout << "Upsert Elements" << endl;
    for (int i = 30; i < 40; i++) {
        upsert(this->root, i);
    }
    this->printContent(this->root);

    cout << "Compact" << endl;
    compact(this->root, this->root);
    this->printContent(this->root);


    cout << "Upsert Elements" << endl;
    for (int i = 40; i < 50; i++) {
        upsert(this->root, i);
    }
    this->printContent(this->root);

    cout << "Compact" << endl;
    compact(this->root, this->root);
    this->printContent(this->root);


    cout << "Upsert Elements" << endl;
    for (int i = 40; i < 50; i++) {
        upsert(this->root, genNumber(40, 45));
    }
    this->printContent(this->root);

    cout << "Compact" << endl;
    compact(this->root, this->root);
    this->printContent(this->root);


}





