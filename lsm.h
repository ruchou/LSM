//
// Created by YanRu Jhou on 2021/9/2.
//

#ifndef LSM_LSM_H
#define LSM_LSM_H

#include <tuple>
#include <map>
#include <set>
#include <optional>
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
    int *tableK;
    int *tableT;
    int tableLen;
    Node *next;
};

const int B = 10;

std::tuple<Node *, std::map<Node *, std::set<int>>, std::map<int, int>> init();

std::optional<int> inContents(Node *n, int k);

#endif //LSM_LSM_H
