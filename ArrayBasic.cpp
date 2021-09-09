//
// Created by YanRu Jhou on 2021/9/9.
//

#include "ArrayBasic.h"

void arr_copy(std::vector<int> *a,
              std::vector<int> *b,
              int src,
              int dst,
              int len
) {
    assert(a != nullptr & b != nullptr);
    assert(0 <= src && src <= src + len && src + len <= a->size());
    assert(0 <= dst && dst <= dst + len && dst + len <= b->size());

//    ghost var mb := b.map;
//    ghost var ma := a.map;

    int i = 0;

//        invariant acc(a) &*& acc(b)
//        invariant 0 <= i <= len
//        invariant 0 <= src <= src + len <= a.length
//        invariant 0 <= dst <= dst + len <= b.length
//        invariant a.map == ma
//        invariant b.map == map_copy(mb, ma, src, dst, i)
    while (i < len) {
//        ghost var m1 := b.map;
        int tmp = a->at(src + i);
        b->at(dst + i) = tmp;
//        pure assert b.map == m1[dst + i := tmp];
        i += 1;
    }

//    ensures acc(a) &*& acc(b)
//    ensures a.map == old(a.map)
//    ensures b.map == map_copy(old(b.map), a.map, src, dst, len)
};