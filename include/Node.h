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
template<class K>
class Node {
public:
    NodeType nodeType;
    std::vector<std::tuple<K, K>> *table;
    int tableLen;
    Node<K> *next;
    FileT *file;
};

/** {Spec} Definition of heap representation predicate, node */
template<class T>
void nodeSpatial(Node<T> *x);

template<class T>
void nodeSpatialFull(Node<T> *x);

template<class T>
void nodePure(Node<T> *r, Node<T> *n, std::map<Node<T> *, std::set<T> > esn, std::map<T, T> Vn);

template<class T>
void node(Node<T> *r, Node<T> *n, std::map<Node<T> *, std::set<T> > esn, std::map<T, T> Vn);

template<class T>
void needsNewNode(Node<T> *r, Node<T> *n, std::map<Node<T> *, std::set<T> > esn, std::map<T, T> Vn);


#endif //LSM_NODE_H
