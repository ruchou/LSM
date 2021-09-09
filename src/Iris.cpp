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
