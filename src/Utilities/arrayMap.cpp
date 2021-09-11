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
    assert((blen + end) < b->size());

    b->insert(b->end(), a->begin(), a->end());
    std::sort(b->begin(), b->end());

    int key, value;
    int tmp_key = -1;
    auto *res = new std::vector<std::tuple<int, int>>;
    for (auto ele: *b) {
        std::tie(key, value) = b->at(0);
        if (key != tmp_key) {
            tmp_key = key;
            res->push_back(std::make_tuple(key, value));
        } else {
            res->back() = std::make_tuple(key, value);
        }
    }
    b = res;

    return b->size();

    //    ensures a.map == old(a.map)
//    ensures acc(a)
//    ensures sorted_array_prefix(b, blen1)
//    ensures contents(b.map, 0, blen1) == append(contents(old(a.map), start, end), contents(old(b.map), 0, blen))
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
    assert(std::is_sorted(a->begin(), a->begin() + alen));
    assert(std::is_sorted(b->begin(), b->begin() + blen));
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