//
// Created by YanRu Jhou on 2021/9/2.
//

#include "../include/lsm_impl.h"


std::tuple<Node<int> *, std::map<Node<int> *, std::set<int>>, std::map<int, std::optional<int>>> init() {
    auto *r = new Node<int>;
    r->table = new std::vector<std::tuple<int, int>>;
    r->table->reserve(2 * B);
    r->tableLen = 0;
    r->next = nullptr;
    r->nodeType = memtableNode;

    std::map<Node<int> *, std::set<int>> esn;
    std::map<int, std::optional<int>> Vr;

    return std::make_tuple(r, esn, Vr);
}

std::optional<int> inContents(Node<int> *r, Node<int> *n, int k) {
//    requires node(r, n, esn, Vn)
//    ensures node(r, n, esn, Vn)
    if (n->nodeType == memtableNode) {
        int start = n->table->size() - n->tableLen;
        int i = start;
        bool flag = false;

        int key, timestamp;

        while (i < n->tableLen && !flag) {
//            invariant n.nodeType == memtableNode;
//            invariant start == n.table.length - n.tableLen;
//            invariant node(r, n, esn, Vn)
//            invariant start <= i <= n.table.length
//            invariant flag ==> start <= i < n.table.length && n.table[i].key == k
//            invariant contents(n.table.map, start, i)[k] == NoneV
            std::tie(key, timestamp) = n->table->at(i);
            if (key == k) {
                flag = true;
            } else {
//                contents_extend(n.table.map, start, i);
                i += 1;
            }
        }

        if (flag) {
//            contents_split(n.table.map, start, i + 1, n.table.length);
//            contents_extend(n.table.map, start, i);

            return timestamp;
        } else {
            return {};
        }

    } else {
        FileT *f = n->file;
        if (!isOpenFile(f)) {
            openFile(f);
        }
        std::optional<int> value;
        int idx;
        std::tie(value, idx) = array_find(*(f->ram), n->tableLen, k);
        return value;
    }

}

bool addContent(Node<int> *r, Node<int> *n, int k, int t) {
//    requires node(r, n, esn, Vn) &*& n == r
    assert(n == r);

    assert(n->nodeType == memtableNode);
    int start = n->table->size() - n->tableLen;
//    pure assert Vn == contents(n.table.map, start, n.table.length);

    if (n->tableLen < n->table->capacity()) {
        n->table->at(start - 1) = std::make_tuple(k, t);

//        contents_extensional(n.table.map, old(n.table.map), start, n.table.length);
        n->tableLen += 1;
        return true;
    } else {
        return false;
    }

}

