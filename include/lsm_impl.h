//
// Created by YanRu Jhou on 2021/9/2.
//

#ifndef LSM_LSM_IMPL_H
#define LSM_LSM_IMPL_H

#include <vector>
#include <tuple>
#include <map>
#include <set>
#include <optional>
#include <iostream>

#include "../include/Utilities/arrayMap.h"
#include "Node.h"

const int B = 20;

std::tuple<Node<int> *, std::map<Node<int> *, std::set<int>>, std::map<int, std::optional<int>>> init();

std::optional<int> inContents(Node<int> *n, int k);

//  returns (b: Bool, implicit ghost Vn1: Map<K, OptionV>)
bool addContent(Node<int> *r, Node<int> *n, int k, int t);

std::optional<Node<int> *> findNext(Node<int> *n, int k);

bool atCapacity(Node<int> *n);

std::optional<Node<int> *> chooseNext(Node<int> *n);

void insertNode(Node<int> *r, Node<int> *n, Node<int> *m);

Node<int> *allocNode();

void mergeContents(Node<int> *r, Node<int> *n, Node<int> *m);

void lockNode(Node<int> *n);

void unlockNode(Node<int> *n);

#endif //LSM_LSM_IMPL_H
