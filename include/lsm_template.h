//
// Created by YanRu Jhou on 2021/9/3.
//

#ifndef LSM_LSM_TEMPLATE_H
#define LSM_LSM_TEMPLATE_H

#include <mutex>

#include "lsm_impl.h"
#include "Node.h"

int readClock();

void incrementClock();

int traverse(Node<int> *n, int k);

int search(Node<int> *r, int k);

void upsert(Node<int> *r, int k);

#endif //LSM_LSM_TEMPLATE_H
