//
// Created by YanRu Jhou on 2021/9/10.
//

#ifndef LSM_ARRAYMAP_H
#define LSM_ARRAYMAP_H

#include <tuple>
#include <optional>
#include <vector>
#include <cassert>

std::tuple<std::optional<int>, int> array_find(std::vector<std::tuple<int, int>> a, int len, int k);

#endif //LSM_ARRAYMAP_H
