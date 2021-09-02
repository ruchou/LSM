//
// Created by YanRu Jhou on 2021/9/2.
//

#ifndef LSM_ARR_UTIL_H
#define LSM_ARR_UTIL_H

#include <tuple>

std::tuple<bool,int>arrFind(std::vector<int> a,int len, int k);
bool compare(int a, int b);
#endif //LSM_ARR_UTIL_H
