//
// Created by YanRu Jhou on 2021/9/10.
//

#include "../../include/Utilities/arrayMap.h"


// Find key `k` in sorted array segment `a[0..len]` (EXLUDING a[len]) using binary search
std::tuple<std::optional<int>, int> array_find(std::vector<std::tuple<int, int>> a, int len, int k) {
//    requires sorted_array_prefix(a, len)
//    requires 0 <= len <= a.length
    assert(0 <= len && len <= a.size());

//    ghost var am := a.map;
    int lo = 0, hi = len;

    while (hi != lo) {
//        invariant sorted_array_prefix(a, len)
//        invariant a.map == am
//        // what we actually care about
//        invariant 0 <= lo <= hi <= len <= a.length
//        invariant hi == len || a.map[lo].key == k || lt(k, a.map[hi].key)
//        invariant 0 < lo ==> lt(a.map[lo - 1].key, k)
//        invariant hi < len - 1 ==> lt(k, a.map[hi + 1].key)
        int mid = (hi + lo) / 2;
        int key, value;
        std::tie(key, value) = a.at(mid);
        int cmp = k - key;

        if (cmp < 0) {
            hi = mid;
        } else if (cmp > 0) {
            lo = mid + 1;
        } else {
            hi = mid;
            lo = mid;
        }

    }

    int idx = lo;
    int key, value;
    std::tie(key, value) = a.at(lo);

    if (idx == len || k != key) {
        return std::tuple(std::nullopt, -1);
    } else {
        return std::tuple(value, idx);
    }

//    map_find_in_contents(a.map, 0, len, k);

//    ensures sorted_array_prefix(a, len)
//    ensures a.map == old(a.map)
//    // what we actually care about
//    ensures idx == map_find(a.map, 0, len, k)
//    ensures v == contents(a.map, 0, len)[k]
//    ensures v != NoneV ==> 0 <= idx < len && a[idx].key == k
//    ensures v == NoneV ==> (idx == len || lt(k, a[idx].key))
}
