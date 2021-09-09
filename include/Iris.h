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

using namespace std;

/** {Spec} Functions used in specs connecting to Iris template proof. */
template<class T>
set<T> dom(map<T, optional<T>> V);

template<class T>
set<tuple<T, T>> set_of_map(map<T, optional<T>> V);

template<class T>
map<T, optional<T>> merge(map<T, optional<T>> Cn,
                          set<T> Es,
                          map<T, optional<T>> Cm
);

template<class T>
map<T, optional<T>> mergeLeft(map<T, optional<T>> Cn,
                              set<T> Es,
                              map<T, optional<T>> Cm
);

template<class T>
map<T, optional<T>> mergeRight(map<T, optional<T>> Cn,
                               set<T> Es,
                               map<T, optional<T>> Cm
);


#endif //LSM_IRIS_H
