//
// Created by YanRu Jhou on 2021/9/9.
//

#ifndef LSM_IRIS_H
#define LSM_IRIS_H

#include <cassert>
#include <optional>
#include <set>
#include <tuple>
#include <map>


/** {Spec} Functions used in specs connecting to Iris template proof. */
template<class T>
std::set<T> dom(std::map<T, std::optional<T>> V);

template<class T>
std::set<std::tuple<T, T>> set_of_map(std::map<T, std::optional<T>> V);

template<class T>
std::map<T, std::optional<T>> merge(std::map<T, std::optional<T>> Cn,
                                    std::set<T> Es,
                                    std::map<T, std::optional<T>> Cm
) {

}

template<class T>
std::map<T, std::optional<T>> mergeLeft(std::map<T, std::optional<T>> Cn,
                                        std::set<T> Es,
                                        std::map<T, std::optional<T>> Cm
) {}

template<class T>
std::map<T, std::optional<T>> mergeRight(std::map<T, std::optional<T>> Cn,
                                         std::set<T> Es,
                                         std::map<T, std::optional<T>> Cm
) {

}


#endif //LSM_IRIS_H
