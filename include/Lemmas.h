//
// Created by YanRu Jhou on 2021/9/9.
//

#ifndef LSM_LEMMAS_H
#define LSM_LEMMAS_H

#include <cassert>
#include <map>
#include <set>
#include <optional>

void dom_empty_map();

template<class T>
void mergeLeft_append(std::map<T, std::optional<T>> Vn,
                      std::set<T> Es,
                      std::map<T, std::optional<T>> Vm
);


#endif //LSM_LEMMAS_H
