//
// Created by YanRu Jhou on 2021/9/9.
//

#include "../include/Iris.h"

template<class T>
set<T> dom(map<T, optional<T>> V) {
    std::set<T> res;
    for (auto e: V) {
        if (e.has_value()) {
            res.insert(e.value());
        }
    }
    return res;
}

template<class T>
set<tuple<T, T>> set_of_map(map<T, optional<T>> V) {
    set<tuple<T, T>> res;
    for (auto e: V) {
        T key = e.first;
        optional<T> value = e.second;

        if (value.has_value()) {
            res.insert(make_tuple(key, value.value()));
        }
    }
    return res;
}

//TODO
template<class T>
map<T, optional<T>> merge(map<T, optional<T>> Cn,
                          set<T> Es,
                          map<T, optional<T>> Cm) {
    map<T, optional<T>> res;


    return res;
}

template<class T>
map<T, optional<T>> mergeLeft(map<T, optional<T>> Cn,
                              set<T> Es,
                              map<T, optional<T>> Cm
) {
    map<T, optional<T>> res;

    return res;
}

template<class T>
map<T, optional<T>> mergeRight(map<T, optional<T>> Cn,
                               set<T> Es,
                               map<T, optional<T>> Cm
) {
    map<T, optional<T>> res;

    return res;
}