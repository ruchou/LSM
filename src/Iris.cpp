//
// Created by YanRu Jhou on 2021/9/9.
//

#include "../include/Iris.h"

template<class T>
std::set<T> dom(std::map<T, std::optional<T>> V) {
    std::set<T> res;
    for (auto e: V) {
        if (e.has_value()) {
            res.insert(e.value());
        }
    }
    return res;
}

template<class T>
std::set<std::tuple<T, T>> set_of_map(std::map<T, std::optional<T>> V) {
    std::set<std::tuple<T, T>> res;
    for (auto e: V) {
        T key = e.first;
        std::optional<T> value = e.second;

        if (value.has_value()) {
            res.insert(make_tuple(key, value.value()));
        }
    }
    return res;
}

