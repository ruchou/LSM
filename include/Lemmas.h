//
// Created by YanRu Jhou on 2021/9/9.
//

#ifndef LSM_LEMMAS_H
#define LSM_LEMMAS_H

#include <cassert>
#include <map>
#include <set>
#include <optional>
#include "Node.h"

//TODO
void dom_empty_map() {}

template<class T>
void mergeLeft_append(std::map<T, std::optional<T>> Vn,
                      std::set<T> Es,
                      std::map<T, std::optional<T>> Vm
) {};

template<class T>
void mergeRight_append(std::map<T, std::optional<T>> Vn,
                       std::set<T> Es,
                       std::map<T, std::optional<T>> Vm
) {};

void set_of_empty_map() {};

template<class T>
void set_of_map_append(std::map<T, std::optional<T>> Cn,
                       std::map<T, std::optional<T>> Cm
) {};

template<class T>
void dom_append_right(std::map<T, std::optional<T>> Cn,
                      std::map<T, std::optional<T>> Cm
) {};

/** {Spec} Implementation-specific lemmas needed by Iris */

template<class T>
void node_sep_star(Node<T> *r,
                   Node<T> *n,
                   std::map<Node<T> *, std::set<T>> esn,
                   std::map<Node<T> *, std::set<T>> esn1,
                   std::map<T, std::optional<T>> V,
                   std::map<T, std::optional<T>> V1
) {};

template<class T>
void node_es_disjoint(Node<T> *r,
                      Node<T> *n,
                      std::map<Node<T> *, std::set<T>> esn,
                      std::map<T, std::optional<T>> V
) {};

template<class T>
void node_es_empty(Node<T> *r,
                   Node<T> *n,
                   std::map<Node<T> *, std::set<T>> esn,
                   std::map<T, std::optional<T>> V
) {};


#endif //LSM_LEMMAS_H
