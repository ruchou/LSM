//
// Created by YanRu Jhou on 2021/9/13.
//

#include "../include/lsm_template.h"

#include <fstream>

std::mutex g_mutex;

int readClock() {
    int clock;
    std::ifstream dataFile;  // Declare input file stream.
    dataFile.open("./clock.txt"); // Open the file.
    dataFile >> clock;  // Store first value of the data.txt into var2.
    dataFile.close();  // Close file stream.
    return clock;
}

void incrementClock() {
    int clock;
    std::ifstream ifstream;
    ifstream.open("./clock.txt");
    ifstream >> clock;
    ifstream.close();

    std::ofstream ofstream;
    ofstream.open("./clock.txt");
    ofstream << clock + 1;
    ofstream.close();
}

int traverse(Node<int> *r, int k) {
    lockNode(r);
    std::optional<int> t1 = inContents(r, k);

    if (t1.has_value()) {
        unlockNode(r);
        return t1.value();
    } else {
        std::optional<Node<int> *> m1 = findNext(r, k);
        if (m1.has_value()) {
            unlockNode(r);
            return traverse(m1.value(), k);
        } else {
            unlockNode(r);
            return -1;
        }
    }
}

int search(Node<int> *r, int k) {
    return traverse(r, k);
}

void upsert(Node<int> *r, int k, int v) {
    lockNode(r);

//    int t = readClock();
    bool res = addContent(r, k, v);

    if (res) {
//        incrementClock();
        unlockNode(r);
    } else {
        unlockNode(r);
        upsert(r, k, v);
    }

}

void compact(Node<int> *r, Node<int> *n) {
    lockNode(n);
    if (atCapacity(n)) {
        std::optional<Node<int> *> someM = chooseNext(n);
        if (someM.has_value()) {
            Node<int> *m = someM.value();
            lockNode(m);
            mergeContents(n, m);
            unlockNode(n);
            unlockNode(m);
            compact(r, m);
        } else {
            Node<int> *m = allocNode();
            insertNode(r, n, m);
            mergeContents(n, m);
            unlockNode(n);
            unlockNode(m);
            compact(r, m);
        }
    } else {
        unlockNode(n);
    }


}