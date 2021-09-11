//
// Created by YanRu Jhou on 2021/9/10.
//

#ifndef LSM_ARRAYMAP_H
#define LSM_ARRAYMAP_H

#include <tuple>
#include <optional>
#include <vector>
#include <cassert>

// Find key `k` in sorted array segment `a[0..len]` (EXLUDING a[len]) using binary search
std::tuple<std::optional<int>, int> array_find(std::vector<std::tuple<int, int>> a, int len, int k);

// Merge unsorted array a[start..end] into sorted array b
int flush(std::vector<std::tuple<int, int>> *a,
          int start,
          int end,
          std::vector<std::tuple<int, int>> *b,
          int blen
);

// Merge two sorted arrays a and b into a sorted array c such that
// the resulting contents of c appends the contents of a and b.
int array_merge(std::vector<std::tuple<int, int>> *a,
                int alen,
                std::vector<std::tuple<int, int>> *b,
                int blen,
                std::vector<std::tuple<int, int>> *c
);

#endif //LSM_ARRAYMAP_H
