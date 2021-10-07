//
// Created by YanRu Jhou on 2021/9/13.
//

#ifndef LSM_LSM_TEMPLATE_H
#define LSM_LSM_TEMPLATE_H

#include "Node.h"
#include "lsm_impl.h"

int traverse(Node<int> *r, int k);

int search(Node<int> *r, int k);

void upsert(Node<int> *r, int k);

void compact(Node<int> *r, Node<int> *n);

#endif //LSM_LSM_TEMPLATE_H
