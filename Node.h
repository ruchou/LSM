//
// Created by YanRu Jhou on 2021/9/3.
//

#ifndef LSM_NODE_H
#define LSM_NODE_H

#include <vector>
#include <iostream>
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


#endif //LSM_NODE_H
