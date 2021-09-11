//
// Created by YanRu Jhou on 2021/9/3.
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

int traverse(Node<int> *n, int k) {
    lockNode(n);
    std::optional<int> t1 = inContents(n, k);

    if (t1.has_value()) {
        unlockNode(n);
        return t1.value();
    } else {
        std::optional<Node<int> *> m1 = findNext(n, k);
        if (m1.has_value()) {
            unlockNode(n);
            traverse(m1.value(), k);
        } else {
            unlockNode(n);
            return -1;
        }
    }

}

int search(Node<int> *r, int k) {
    return traverse(r, k);
}

void upsert(Node<int> *r, int k) {
    lockNode(r);

    int t = readClock();
    bool res = addContent(r, k, t);

    if (res) {
        incrementClock();
        unlockNode(r);
    } else {
        unlockNode(r);
        upsert(r, k);
    }

}