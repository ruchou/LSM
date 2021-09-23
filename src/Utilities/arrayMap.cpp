//
// Created by YanRu Jhou on 2021/9/10.
//

#include "../../include/Utilities/arrayMap.h"

// Merge unsorted array a[start..end] into sorted array b
int flush(std::vector<std::tuple<int, int>> *a,
          int start,
          int end,
          std::vector<std::tuple<int, int>> *b,
          int blen
) {
//    requires acc(a)
    assert(a != nullptr);
//    requires sorted_array_prefix(b, blen)
    assert(0 <= start && start <= end && !a->empty());
    assert((blen + end) <= b->size());

    int i = end - 1;
    int blen1 = blen;

//    pure assert contents(old(a.map), i + 1, end) == empty_map;
//    append_empty_left(contents(old(b.map), 0, blen));
//    pure assert contents(b.map, 0, blen1) == append(contents(old(a.map), i + 1, end), contents(old(b.map), 0, blen));

    while (start <= i) {
//        invariant acc(a)
//        invariant sorted_array_prefix(b, blen1)
//        invariant -1 <= start-1 <= i < end
//        invariant blen1 + i <= blen + end < b.length
//        invariant a.map == old(a.map)
//        invariant contents(b.map, 0, blen1) == append(contents(old(a.map), i + 1, end), contents(old(b.map), 0, blen))

//        ghost var bmap := b.map;
//        ghost var blen_i := blen1;
//        ghost var c := contents(bmap, 0, blen_i);

        int idx1, new_blen;
        std::tie(idx1, new_blen) = arr_insert(b, a->at(i), blen1);
        blen1 = new_blen;
        i -= 1;


//        pure assert c == append(contents(old(a.map), i+2, end), contents(old(b.map), 0, blen));
//
//        pure assert contents(b.map, 0, blen1) == c[a[i+1].key := SomeV(a[i+1].val)];
//
//        append_contents_extend_left(old(a.map), i+2, end, contents(old(b.map), 0, blen));
//

    }

//    pure assert contents(b.map, 0, blen1) == append(contents(old(a.map), start, end), contents(old(b.map), 0, blen));



    return b->size();

    //    ensures a.map == old(a.map)
//    ensures acc(a)
//    ensures sorted_array_prefix(b, blen1)
//    ensures contents(b.map, 0, blen1) == append(contents(old(a.map), start, end), contents(old(b.map), 0, blen))
}

bool sortbysec(const std::tuple<int, int> &a,
               const std::tuple<int, int> &b) {
    return (std::get<0>(a) < std::get<0>(b));
}


int array_merge(std::vector<std::tuple<int, int>> *a,
                int alen,
                std::vector<std::tuple<int, int>> *b,
                int blen,
                std::vector<std::tuple<int, int>> *c
) {
//    requires sorted_array_prefix(a, alen)
//    requires sorted_array_prefix(b, blen)
//    requires acc(c)
//    requires alen + blen <= c.length

    assert(std::is_sorted(a->begin(), a->begin() + alen, sortbysec));
    assert(std::is_sorted(b->begin(), b->begin() + blen, sortbysec));
    assert(c != nullptr);
    assert(alen + blen <= c->capacity());

    int ai = 0;
    int bi = 0;
    int ci = 0;

//    pure assert contents(a.map, 0, ai) == empty_map;
//    pure assert contents(b.map, 0, bi) == empty_map;
//    pure assert contents(c.map, 0, ci) == empty_map;
//    append_empty_left(contents(a.map, 0, ai));


    while (ai < alen || bi < blen) {
        /*
        invariant 0 <= ai <= alen
        invariant 0 <= bi <= blen
        invariant 0 <= ci <= ai + bi
        invariant ci == 0 ==> ai == 0 && bi == 0
        invariant alen + blen <= c.length
        invariant alen == old(alen)
        invariant blen == old(blen)
        invariant sorted_array_prefix(a, alen)
        invariant sorted_array_prefix(b, blen)
        invariant sorted_array_prefix(c, ci)
        invariant ci > 0 && ai > 0 ==> le(a[ai - 1].key, c[ci - 1].key)
        invariant ci > 0 && bi > 0 ==> le(b[bi - 1].key, c[ci - 1].key)
        invariant ci > 0 && ai < alen ==> lt(c[ci - 1].key, a[ai].key)
        invariant ci > 0 && bi < blen ==> lt(c[ci - 1].key, b[bi].key)
        invariant a.map == old(a.map)
        invariant b.map == old(b.map)
        invariant contents(c.map, 0, ci) == append(contents(old(a.map), 0, ai), contents(old(b.map), 0, bi))
        */

        std::tuple<int, int> p;
//        ghost var cmap := c.map;
        if (ai < alen) {
//            not_in_sorted_seg(old(a.map), 0, ai, b[bi].key);
            if (bi < blen) {
//                not_in_sorted_seg(old(b.map), 0, bi, b[bi].key);
                if (std::get<0>(b->at(bi)) > std::get<0>(a->at(ai))) {
                    p = b->at(bi);
                    c->at(ci) = p;

//                    contents_extend(old(b.map), 0, bi);
//                    append_none(contents(old(a.map), 0, ai), contents(old(b.map), 0, bi), p);
//                    append_write_left(contents(old(a.map), 0, ai), contents(old(b.map), 0, bi), p);
                    bi += 1;
//                    assert sorted_array_prefix(a, alen) &*& sorted_array_prefix(b, blen) &*& sorted_array_prefix(c, ci + 1);

                } else {
                    p = a->at(ai);
                    c->at(ci) = p;
//                    contents_extend(old(a.map), 0, ai);
//                    append_none(contents(old(a.map), 0, ai), contents(old(b.map), 0, bi), p);
//                    append_write_left(contents(old(a.map), 0, ai), contents(old(b.map), 0, bi), p);
//
                    if (std::get<0>(a->at(ai)) == std::get<0>(b->at(bi))) {
//                        contents_extend(old(b.map), 0, bi);
//                        append_write(contents(old(a.map), 0, ai), contents(old(b.map), 0, bi), a[ai], b[bi]);
                        bi += 1;
                    }

                    ai += 1;
//                    assert sorted_array_prefix(a, alen) &*& sorted_array_prefix(b, blen) &*& sorted_array_prefix(c, ci + 1);

                }


            } else {
                p = a->at(ai);
                c->at(ci) = p;
//                contents_extend(old(a.map), 0, ai);
//                append_none(contents(old(a.map), 0, ai), contents(old(b.map), 0, bi), p);
//                append_write_left(contents(old(a.map), 0, ai), contents(old(b.map), 0, bi), p);
                ai += 1;
            }
        } else {
            p = b->at(bi);
            c->at(ci) = p;

//            contents_extend(old(b.map), 0, bi);
//            append_none(contents(old(a.map), 0, ai), contents(old(b.map), 0, bi), p);
//            append_write_left(contents(old(a.map), 0, ai), contents(old(b.map), 0, bi), p);

            bi += 1;
//            assert sorted_array_prefix(a, alen) &*& sorted_array_prefix(b, blen) &*& sorted_array_prefix(c, ci + 1);

        }

//        not_in_sorted_seg(c.map, 0, ci, p.key);
//        contents_extensional(c.map, cmap, 0, ci);
//        contents_extend(c.map, 0, ci);
//        pure assert contents(c.map, 0, ci + 1) == append(contents(old(a.map), 0, ai), contents(old(b.map), 0, bi));
        ci += 1;
    }
//    ensures sorted_array_prefix(a, alen)
//    ensures sorted_array_prefix(b, blen)
//    ensures sorted_array_prefix(c, clen)
//    ensures contents(c.map, 0, clen) == append(contents(old(a.map), 0, alen), contents(old(b.map), 0, blen))
    return ci;
}

// Given a sorted array segment `a[0..len]`,
// insert `k` into `a[0..len+1]` while preserving sortedness.
// If `k` is already contained in `a[0..len]`, then do not modify `a`.
std::tuple<int, int> arr_insert(std::vector<std::tuple<int, int>> *a,
                                std::tuple<int, int> p,
                                int len) {
//    requires sorted_array_prefix(a, len)
    assert(len < a->size());

    int i;
    std::optional<int> v;
    int k = std::get<0>(p);

    std::tie(v, i) = arr_find(a, len, k);

//    map_find_in_contents(a.map, 0, len, k);

    if (v.has_value()) {
        a->at(i) = p;
//        contents_split(a.map, 0, i, len);
//        contents_split(old(a.map), 0, i, len);
//        contents_extensional(a.map, old(a.map), 0, i);
//        contents_extensional(a.map, old(a.map), i + 1, len);
//        not_in_sorted_seg(a.map, 0, i, p.key);
//        append_write(contents(old(a.map), 0, i), contents(old(a.map), i, len), p, p);
//
//        pure assert contents(old(a.map), i + 1, len)[p.key := SomeV(p.val)] == contents(a.map, i, len)[p.key := SomeV(p.val)];
//        pure assert contents(old(a.map), i + 1, len)[p.key := SomeV(p.val)] == contents(old(a.map), i, len)[p.key := SomeV(p.val)];
//
//        append_none(contents(old(a.map), 0, i), contents(a.map, i, len), p);

        return std::make_tuple(i, len);
    } else {

        arr_shift(a, i, i + 1, len - i);
//        ghost var ms := a.map;
        a->at(i) = p;

//        ghost var i1 : Int;
//
//        pure assert forall i1: Int :: a.map[i1] == ms[i := p][i1] with {
//                if (i1 == i) pure assert a.map[i1] == p;
//                else pure assert a.map[i1] == ms[i1];
//        }
//
//        pure assert forall i1: Int, i2: Int :: 0 <= i1 < i2 < len + 1 ==> lt(a.map[i1].key, a.map[i2].key) with {
//                if (i1 < i || (i + 1) + (len - i) <= i1) {
//                    pure assert a.map[i1] == old(a.map)[i1];
//                } else if (i < i1) {
//                    pure assert a.map[i1] == old(a.map)[i + (i1 - (i + 1))];
//                }
//                if (i2 < i || (i + 1) + (len - i) <= i2) {
//                    pure assert a.map[i2] == old(a.map)[i2];
//                } else if (i < i2) {
//                    pure assert a.map[i2] == old(a.map)[i + (i2 - (i + 1))];
//                }
//        }

//        pure assert contents(a.map, 0, len + 1) == contents(old(a.map), 0, len)[p.key := SomeV(p.val)] with {
//                contents_split(a.map, 0, i + 1, len + 1);
//                contents_split(old(a.map), 0, i, len);
//                contents_extensional(a.map, old(a.map), 0, i);
//
//                pure assert forall k: Int :: 0 <= k < (len + 1) - (i + 1) ==> a.map[(i + 1) + k] == old(a.map)[i + k] with {
//                    if (0 <= k < (len + 1) - (i + 1)) {
//                        pure assert a.map[(i + 1) + k] == old(a.map)[i + (((i + 1) + k) - (i + 1))];
//                    }
//                }
//                contents_extensional2(a.map, old(a.map), i + 1, len + 1, i, len);
//
//                not_in_sorted_seg(a.map, 0, i, p.key);
//                contents_extend(a.map, 0, i);
//
//                append_write_left(contents(a.map, 0, i), contents(a.map, i + 1, len + 1), p);
//        }

        return std::make_tuple(i, len + 1);
    }


//    ensures sorted_array_prefix(a, new_len)
//    ensures idx == map_find(old(a.map), 0, len, p.key)
//    ensures contents(a.map, 0, new_len) == contents(old(a.map), 0, len)[p.key := SomeV(p.val)];
//    ensures contents(old(a.map), 0, len)[p.key] != NoneV ==> new_len == len && a.map == old(a.map)[idx := p]
//    ensures contents(old(a.map), 0, len)[p.key] == NoneV ==> (new_len == len + 1
//                                                              && a.map == map_shift(old(a.map), idx, idx + 1, len - idx)[idx := p])
//    ensures a[idx] == p
}


// Find key `k` in sorted array segment `a[0..len]` (EXLUDING a[len]) using binary search
std::tuple<std::optional<int>, int> arr_find(std::vector<std::tuple<int, int>> *a, int len, int k) {
//    requires sorted_array_prefix(a, len)
    assert(0 <= len && len <= a->size());
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
        int cmp = k - std::get<0>(a->at(mid));

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
    if (idx == len || k < std::get<0>(a->at(lo))) {
        return std::make_tuple(std::nullopt, len);
    } else {
        int key, value;
        std::tie(key, value) = a->at(idx);
        return std::make_tuple(value, idx);
    }


//    ensures sorted_array_prefix(a, len)
//    ensures a.map == old(a.map)
//    // what we actually care about
//    ensures idx == map_find(a.map, 0, len, k)
//    ensures v == contents(a.map, 0, len)[k]
//    ensures v != NoneV ==> 0 <= idx < len && a[idx].key == k
//    ensures v == NoneV ==> (idx == len || lt(k, a[idx].key))


}