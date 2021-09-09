//
// Created by YanRu Jhou on 2021/9/3.
//

#ifndef LSM_NODE_H
#define LSM_NODE_H

#include "FileSystem.h"

#include <vector>
#include <set>
#include <map>
#include <iostream>

/*LSM-Like Implementation of multicopy template*/
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
    std::vector<std::tuple<int, int>> *table;
    int tableLen;
    Node *next;
    FileT *file;
};

/** {Spec} Definition of heap representation predicate, node */

void nodeSpatial(Node *x);

void nodeSpatialFull(Node *x);

void nodePure(Node *r, Node *n, std::map<Node *, std::set<int>> esn, std::map<int, int> Vn);

void node(Node *r, Node *n, std::map<Node *, std::set<int>> esn, std::map<int, int> Vn);

void needsNewNode(Node *r, Node *n, std::map<Node *, std::set<int>> esn, std::map<int, int> Vn);

#endif //LSM_NODE_H
