//
// Created by YanRu Jhou on 2021/9/2.
//

#ifndef LSM_LSM_H
#define LSM_LSM_H

#include <vector>
#include "arr_util.h"

/*LSM-Like Implementation of multicopy template*/
enum OptionTS {
    someTS,
    noneTS
};

enum OptionNode {
    someNode,
    noneNode
};
//Type of Node
enum NodeType {
    memtableNode,
    sstableNode
};

// TODO
// ghost var indices: Map<K, Int>;  // inverse of tableK for sstableNodes
class Node {
public:
    NodeType nodeType;
    std::vector<int> tableK;
    std::vector<int> tableT;
    int tableLen;
    Node *next;
};

const int B = 10;

std::tuple<Node*, std::map<Node *, std::set<int>>, std::map<int, int>> init();

std::optional<int> inContents(Node *n, int k);

std::tuple<bool,Node*,std::map<int,int>>addContents(Node *n,int k, int t);

std::optional<Node*>findNext(Node* n);

bool atCapacity(Node* n);

std::optional<Node*>chooseNext(Node* n);

void insertNode(Node*n);

#endif //LSM_LSM_H
