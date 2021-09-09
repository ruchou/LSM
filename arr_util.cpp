//
// Created by YanRu Jhou on 2021/9/2.
//
#include <vector>
#include "arr_util.h"

// Find key `k` in sorted array segment `a[0..len]` (EXLUDING a[len]) using binary search
std::tuple<bool,int>arrFind(std::vector<int> a,int len, int k){
    int lo = 0;
    int hi = len;

    while (hi != lo) {
        int mid = (hi + lo) / 2;
        int cmp = compare(k, a[mid]);
        if (cmp < 0) {
            hi = mid; //look in the first half
        } else if (cmp > 0) {
            lo = mid + 1; // look in the second half
        } else {
            //found it
            hi = mid;
            lo = mid;
        }
    }

    int idx = lo;
    bool found;
    if (idx == len || k < a[lo]) {
        found = false;
    } else {
        found = true;
    }
//    bool found = false;
//    int idx = 0;
//    while(!found && idx < len ){
//        int cmp  = compare(a[idx],k);
//        if(cmp==0){
//            found = true;
//            break;
//        }
//        idx += 1;
//    }

    return std::make_tuple(found, idx);
    //map_find_in_set
}

bool compare(int a, int b){
    return a - b;
}