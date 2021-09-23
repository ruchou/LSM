//
// Created by YanRu Jhou on 2021/9/2.
//

#include "../include/lsm_impl.h"


std::tuple<Node<int> *, std::map<Node<int> *, std::set<int>>, std::map<int, std::optional<int>>> init() {
    auto *r = new Node<int>;
    r->table = new std::vector<std::tuple<int, int>>;
    r->table->resize(2 * B);
    std::fill(r->table->begin(), r->table->end(), std::make_tuple(-1, -1));
    r->tableLen = 0;
    r->next = nullptr;
    r->nodeType = memtableNode;

    std::map<Node<int> *, std::set<int>> esn;
    std::map<int, std::optional<int>> Vr;

    return std::make_tuple(r, esn, Vr);
}

std::optional<int> inContents(Node<int> *n, int k) {
//    requires node(r, n, esn, Vn)
//    ensures node(r, n, esn, Vn)
    if (n->nodeType == memtableNode) {
        int start = n->table->size() - n->tableLen;
        int i = start;
        bool flag = false;

        int key, timestamp;

        while (i < n->table->size() && !flag) {
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
        std::tie(value, idx) = arr_find((f->ram), n->tableLen, k);
        return value;
    }

}

bool addContent(Node<int> *n, int k, int t) {
//    requires node(r, n, esn, Vn) &*& n == r
//    assert(n == r);

    assert(n->nodeType == memtableNode);
    int start = n->table->size() - n->tableLen;
//    pure assert Vn == contents(n.table.map, start, n.table.length);


    if (n->tableLen < n->table->size()) {
        n->table->at(start - 1) = std::make_tuple(k, t);

//        contents_extensional(n.table.map, old(n.table.map), start, n.table.length);
        n->tableLen += 1;
        return true;
    } else {
        return false;
    }

}

std::optional<Node<int> *> findNext(Node<int> *n, int k) {
//    requires node(r, n, esn, Vn)

    if (n->next == nullptr) {
//        ensures res != noneNode ==> k in esn[res.nd]
        return {};
    } else {
//        ensures res == noneNode ==> (forall n1: Node :: k !in esn[n1])
        return n->next;
    }

}

bool atCapacity(Node<int> *n) {
//    requires node(r, n, esn, Vn)

    if (n->nodeType == memtableNode) {
        if (n->tableLen < n->table->size()) {
            return false;
        } else {
            return true;
        }
    } else {
        return false;
//        if(n->file->size > n->file->ram->size()/2 ){
//            return true;
//        }else{
//            return false;
//        }
    }
}

std::optional<Node<int> *> chooseNext(Node<int> *n) {
//    requires node(r, n, esn, Vn)
    if (n->next != nullptr) {
//        ensures node(r, n, esn, Vn)
//        ensures res != noneNode ==> esn[res.nd] != {}
        return n->next;
    } else {
//        ensures node(r, n, esn, Vn)
//        ensures res == noneNode ==> needsNewNode(r, n, esn, Vn)
        return {};
    };
}


void insertNode(Node<int> *r, Node<int> *n, Node<int> *m) {
//    requires node(r, n, esn, Vn) &*& nodeSpatial(m)
//    requires needsNewNode(r, n, esn, Vn) &*& m != r
    assert(m != r);

    assert(n != m);
    n->next = m;
    std::map<Node<int> *, int> esn1;

    m->tableLen = 0;
    m->next = nullptr;
    m->nodeType = sstableNode;
    m->file = createFile(0);

    std::map<Node<int> *, int> esm;
    std::map<Node<int> *, int> Vm;

//    ensures node(r, n, esn1, Vn) &*& node(r, m, esm, Vm)
//    ensures esn1[m] != {} && esn1 == esn[m := esn1[m]]
//    ensures esm == { x: Node :: {} } && Vm == empty_map

//    return esn1, esm, Vm;

}

Node<int> *allocNode() {
    assert(true);

    auto *m = new Node<int>();

    nodeSpatial(m);
    return m;
}


//ghost esn: Map<Node, Set<K>>,
//ghost Vn: Map<K, OptionV>,
//ghost esm: Map<Node, Set<K>>,
//ghost Vm: Map<K, OptionV>)
template<class T>
void mergeContentsHelper(Node<T> *n, Node<T> *m) {
//    requires node(r, n, esn, Vn) &*& node(r, m, esm, Vm)
//    requires esn[m] != {}
    assert(m != n);

    if (n->nodeType == memtableNode) {
        // n is root node: flush
        FileT *f = m->file;

        if (!isOpenFile(f))
            openFile(f);

        FileT *f_new = createFile(n->table->size() + f->size);
        openFile(f_new);

        arr_copy(f->ram, f_new->ram, 0, 0, f->ram->size());

//        contents_extensional(f.ram.map, f_new.ram.map, 0, m.tableLen);

        //Weird
        int rlen = flush(n->table,
                         0,
                         n->tableLen,
                         f_new->ram, m->tableLen);
        writeFile(f_new);

//        contents_extensional(f_new.ram.map, f_new.disk_cont.map, 0, rlen);
        deleteFile(f);
        m->file = f_new;
        m->tableLen = rlen;

        n->tableLen = 0;

    } else {
        // n and m are disk nodes: compact
        auto fn = n->file;
        auto fm = m->file;

        if (!isOpenFile(fn))
            openFile(fn);

        if (!isOpenFile(fm))
            openFile(fm);

        auto fm_new = createFile(n->tableLen + m->tableLen);
        openFile(fm_new);

        int rlen = array_merge(fn->ram, n->tableLen, fm->ram, m->tableLen, fm_new->ram);
        writeFile(fm_new);

        deleteFile(fm);
        m->file = fm_new;
        m->tableLen = rlen;

        auto fn_new = createFile(n->file->size);
        openFile(fn_new);
        writeFile(fn_new);

        deleteFile(fn);
        n->file = fn_new;
        n->tableLen = 0;
        return;
    }

//    ensures node(r, n, esn, empty_map) &*& node(r, m, esm, append(Vn, Vm))

}

/*
 *ghost esn: Map<Node, Set<K>>,
    ghost Vn: Map<K, OptionV>,
    ghost esm: Map<Node, Set<K>>,
    ghost Vm: Map<K, OptionV>)
 */

void mergeContents(Node<int> *n, Node<int> *m) {
//    requires node(r, n, esn, Vn) &*& node(r, m, esm, Vm)
//    requires esn[m] != {}

    mergeContentsHelper(n, m);

//    // Some ghost code to relate to spec assumed in Iris proof
//    ghost var K11 := dom(Vn);
//    ghost var Vm11 := append(Vn, Vm);
//    ghost var Vn11 := empty_map;
//
//    mergeLeft_append(Vn, esn[m], Vm);
//    mergeRight_append(Vn, esn[m], Vm);


//    ensures node(r, n, esn, Vn1) &*& node(r, m, esm, Vm1)
//    ensures Vn1 == mergeLeft(K1, Vn, esn[m], Vm)
//    ensures Vm1 == mergeRight(K1, Vn, esn[m], Vm)
//    returns (implicit ghost K1: Set<K>, implicit ghost Vn1: Map<K, OptionV>, implicit ghost Vm1: Map<K, OptionV>)

}

void lockNode(Node<int> *n) {
    bool b;
    bool t = false;
    b = n->lockBit.compare_exchange_strong(t, true);
    if (b) {

    } else {
        lockNode(n);
    }
}

void unlockNode(Node<int> *n) {
    n->lockBit = false;
}
