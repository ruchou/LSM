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


#include "Node.h"


int B = 10;

std::tuple<Node *, std::map<Node *, std::set<int>>, std::map<int, int>> init();

//Helper functions
std::optional<int> inContents(Node *n, int k);

bool addContents(Node *n, int k, int t);

std::optional<Node *> findNext(Node *n);

bool atCapacity(Node *n);

std::optional<Node *> chooseNext(Node *n);

void insertNode(Node *n, Node *m);

void lockNode(Node *n);

void unlockNode(Node *n);

void mergeContent(Node *n, Node *m);

Node *allocateNode();


#endif //LSM_LSM_IMPL_H
