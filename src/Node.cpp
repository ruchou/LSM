//
// Created by YanRu Jhou on 2021/9/3.
//

#include "../include/Node.h"

template<class T>
void nodeSpatial(Node<T> *x) {
    assert(x != nullptr);
}

template<class T>
void nodeSpatialFull(Node<T> *x) {
    nodeSpatial(x);

    if (x->nodeType == memtableNode && x->table != nullptr)
        return;
    else {
        assert(x->nodeType != memtableNode);
        File(x->file, x->file->is_new, x->file->is_open, x->file->ram->size());
    }

}

template<class T>
void nodePure(Node<T> *r, Node<T> *n, std::map<Node<T> *, std::set<T>> esn, std::map<T, T> Vn) {
    //TODO
    //true
//    // Node is either memtable or sstable:
//    && (n.nodeType == memtableNode
//        && n == r
//        && Vn == contents(n.table.map, n.table.length - n.tableLen, n.table.length)
//        && 0 <= n.tableLen <= n.table.length
//        || n.nodeType == sstableNode
//           && n != r
//           && sorted_map_seg(n.file.disk_cont.map, 0, n.tableLen)
//           // Cn is given by table
//           && Vn == contents(n.file.disk_cont.map, 0, n.tableLen)
//           && (n.file.is_open ==> n.file.ram.map == n.file.disk_cont.map)
//    && 0 <= n.tableLen <= n.file.disk_cont.length
//    )
//    // No self-loops
//    && n.next != n && n.next != r
//       // Edgeset to next node is entire keyspace if non-null
//       && (n.next != null
//           ==> (forall k: K :: k in esn[n.next]))
//    // All other nodes have empty edgeset
//    && (forall n1: Node :: n1 != n.next ==> esn[n1] == {})
//    && esn[null] == {}

}

template<class T>
void node(Node<T> *r, Node<T> *n, std::map<Node<T> *, std::set<T>> esn, std::map<T, T> Vn) {
    nodeSpatial(n);
    nodePure(r, n, esn, Vn);
}

template<class T>
void needsNewNode(Node<T> *r, Node<T> *n, std::map<Node<T> *, std::set<T>> esn, std::map<T, T> Vn) {
    assert(n->next == nullptr);
}