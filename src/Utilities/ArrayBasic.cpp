//
// Created by YanRu Jhou on 2021/9/9.
//

#include "../../include/Utilities/ArrayBasic.h"

void arr_copy(std::vector<std::tuple<int, int>> *a,
              std::vector<std::tuple<int, int>> *b,
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
        auto tmp = a->at(src + i);
        b->at(dst + i) = tmp;
//        pure assert b.map == m1[dst + i := tmp];
        i += 1;
    }

//    ensures acc(a) &*& acc(b)
//    ensures a.map == old(a.map)
//    ensures b.map == map_copy(old(b.map), a.map, src, dst, len)
};


// Shift a[src..src+len] to a[dst..dst+len]
void arr_shift(std::vector<std::tuple<int, int>> *a, int src, int dst, int len) {
    assert(a != nullptr);
//    requires 0 <= src <= src + len <= a.length && 0 <= dst <= dst + len <= a.length
    assert(0 <= src && src <= src + len && src + len <= a->size()
           && 0 <= dst && dst <= dst + len && dst + len <= a->size()
    );

//    ghost var m := a.map;
    if (src < dst) {
        int i = len - 1;

        while (i >= 0)
//            invariant acc(a)
//            invariant src < dst
//            invariant 0 <= src <= src + len <= a.length
//            invariant 0 <= dst <= dst + len <= a.length
//            invariant -1 <= i < len
//            invariant map_shift(m, src + i + 1, dst + i + 1, len - i - 1) == a.map
        {

//            ghost var j: Int;
//            pure assert "test" map_shift(m, src + i + 1, dst + i + 1, len - i - 1)[j] == a.map[j];
//            ghost var m1 := a.map;

            auto tmp = a->at(src + i);
            a->at(dst + i) = tmp;
            /*
             * pure assert a.map == m1[dst + i := tmp];
      pure assert "test" forall j: Int :: map_shift(m, src + (i-1) + 1, dst + (i-1) + 1, len - (i-1) - 1)[j] == a.map[j] with {
        if (j < (dst + (i-1) + 1) || (dst + (i-1) + 1) + (len - (i-1) - 1) <= j) {
          pure assert "test" map_shift(m, src + (i-1) + 1, dst + (i-1) + 1, len - (i-1) - 1)[j] == m[j];
        } else {
          pure assert "test" map_shift(m, src + (i-1) + 1, dst + (i-1) + 1, len - (i-1) - 1)[j] == m[(src + (i-1) + 1) + (j - (dst + (i-1) + 1))];
        }
        if (j < (dst + i + 1) || (dst + i + 1) + (len - i - 1) <= j) {
          pure assert "test" map_shift(m, src + i + 1, dst + i + 1, len - i - 1)[j] == m1[j];

        } else {
          pure assert "test" map_shift(m, src + i + 1, dst + i + 1, len - i - 1)[j] == m[(src + i + 1) + (j - (dst + i + 1))];
        }
      }
             */
            i -= 1;
        }

        /*
         *  pure assert forall j: Int :: map_shift(m, src, dst, len)[j] == a.map[j] with {
      if (j < (dst + i + 1) || (dst + i + 1) + (len - i - 1) <= j) {
        pure assert "test" map_shift(m, src + i + 1, dst + i + 1, len - i - 1)[j] == m[j];
      } else {
        pure assert "test" map_shift(m, src + i + 1, dst + i + 1, len - i - 1)[j] == m[(src + i + 1) + (j - (dst + i + 1))];
      }
    }
         */
    } else if (src > dst) {
        int i = 0;

        while (i < len)
//            invariant acc(a)
//            invariant src > dst
//        invariant 0 <= src <= src + len <= a.length
//        invariant 0 <= dst <= dst + len <= a.length
//        invariant 0 <= i <= len
//        invariant map_shift(m, src, dst, i) == a.map
        {
//            ghost var m1 := a.map;
            auto tmp = a->at(src + i);
            a->at(dst + i) = a->at(src + i);
//            pure assert a.map == m1[dst + i := tmp];
//            pure assert "test" forall j: Int :: map_shift(m, src, dst, i+1)[j] == a.map[j] with {
//                    if (j < dst || dst + (i+1) <= j) {
//                        pure assert "test" map_shift(m, src, dst, i+1)[j] == m[j];
//                    } else {
//                        pure assert "test" map_shift(m, src, dst, i+1)[j] == m[src + (j - dst)];
//                    }
//                    if (j < dst || dst + i <= j) {
//                        pure assert "test" map_shift(m, src, dst, i)[j] == m1[j];
//
//                    } else {
//                        pure assert "test" map_shift(m, src, dst, i)[j] == m[src + (j - dst)];
//                    }
//            }

            i += 1;
        }

    }

//    pure assert forall j: Int :: map_shift(m, src, dst, len)[j] == a.map[j] with {
//            if (j < dst || dst + len <= j) {
//                pure assert "test" map_shift(m, src, dst, len)[j] == m[j];
//            } else {
//                pure assert "test" map_shift(m, src, dst, len)[j] == m[src + (j - dst)];
//            }
//    }
//

//    ensures acc(a)
//    ensures a.map == map_shift(old(a.map), src, dst, len)

}