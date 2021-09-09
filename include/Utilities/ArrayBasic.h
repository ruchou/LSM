//
// Created by YanRu Jhou on 2021/9/9.
//

#ifndef LSM_ARRAYBASIC_H
#define LSM_ARRAYBASIC_H

#include <vector>
#include <tuple>
#include <cassert>

// Copy a[src..src+len] to b[dst..dst+len]
void arr_copy(std::vector<std::tuple<int, int>> *a,
              std::vector<std::tuple<int, int>> *b,
              int src,
              int dst,
              int len
);


#endif //LSM_ARRAYBASIC_H
