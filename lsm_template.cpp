//
// Created by YanRu Jhou on 2021/9/3.
//

#include "lsm_template.h"
#include "lsm_impl.h"
#include <fstream>

int readClock(){
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
int search(Node*r , int k){
    return traverse(r,k);
}

int traverse(Node* n, int k){
    lockNode(n);
    std::optional<int> t_ = inContents(n,k);
    if(t_.has_value()){
        unlockNode(n);
        return t_.value();
    }else{
        std::optional<Node*>n_ = findNext(n);
        if(n_.has_value()){
            unlockNode(n);
            return traverse(n_.value(),k);
        }else{
            unlockNode(n);
            return -1;
        }
    }
}

void upsert(Node*r, int k){
    int t = readClock();
    bool res = addContents(r,k,t);
    if(res){
        incrementClock();
        unlockNode(r);
    }else{
        unlockNode(r);
        upsert(r,k);
    }
}