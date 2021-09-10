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

std::optional<int> inContents(Node<int> *r, Node<int> *n, int k);

#endif //LSM_LSM_IMPL_H
