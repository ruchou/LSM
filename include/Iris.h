//
// Created by YanRu Jhou on 2021/9/9.
//

#ifndef LSM_IRIS_H
#define LSM_IRIS_H

#include <cassert>
#include <optional>
#include <set>
#include <map>

/** {Spec} Functions used in specs connecting to Iris template proof. */
template<class T>
std::set<T> dom(std::map<T, std::optional<T>> V);


#endif //LSM_IRIS_H
