//
// Created by YanRu Jhou on 2021/9/2.
//

#include "../include/lsm_impl.h"

std::tuple<Node *, std::map<Node *, std::set<int>>, std::map<int, int>> init() {
    Node *r = new Node();
    r->tableK.reserve(2 * B);
    r->tableT.reserve(2 * B);
    r->tableLen = 0;
    r->next = nullptr;
    r->nodeType = memtableNode;

    std::map<Node *, std::set<int>> esr;
    std::map<int, int> Cr;

    return std::make_tuple(r, esr, Cr);

}

std::optional<int> inContents(Node *n, int k) {
    if (n->nodeType == memtableNode) {
        int i = n->tableLen - 1;
        bool flag = false;

        while (i >= 0 && !flag) {
            if (n->tableK[i] == k) {
                flag = true;
            } else {
                i -= 1;
            }
        }

        if (flag) {
            return n->tableT[i];
        } else {
            return {};
        }
    } else {
        bool b;
        int i;
        std::tie(b, i) = arrFind(n->tableK, n->tableLen, k); //elements are sorted in sstable
        if (b) {
            return n->tableT[i];
        } else {
            return {};
        }
    }
}

bool atCapacity(Node *n) {
    if (n->tableLen < n->tableK.capacity())
        return false;
    else
        return true;
}

bool addContents(Node *n, int k, int t) {
    if (n->tableLen < n->tableK.capacity()) {
        n->tableK[n->tableLen] = k;
        n->tableT[n->tableLen] = t;
        n->tableLen += 1;

        return true;
    } else {
        return false;
    }
}

std::optional<Node *> findNext(Node *n) {
    if (n->next == nullptr) {
        return {};
    } else {
        return n->next;
    }
}

std::optional<Node *> chooseNext(Node *n) {
    if (n->next != nullptr) {
        return n->next;
    } else {
        return {};
    }
}

void insertNode(Node *n, Node *m) {
    m = new Node();

    n->next = m;
    m->tableLen = 0;
    m->next = nullptr;
    m->nodeType = sstableNode;
}


//TODO c++ lock?
void lockNode(Node *n) {
    if (!n->lock) {
        n->lock = true;
    } else {
        lockNode(n);
    }
}

void unlockNode(Node *n) {
    n->lock = false;
}


void mergeContent(Node *n, Node *m) {

    std::map<int, bool> n_map;
    std::vector<int> n_new_k;
    std::vector<int> n_new_t;
    for (int i = n->tableLen - 1; i >= 0; i--) {
        if (n_map.find(n->tableK[i]) != n_map.end()) {
            n_new_k.push_back(n->tableK[i]);
            n_new_t.push_back(n->tableT[i]);
            n_map[n->tableK[i]] = true;
        }
    }

    int i, tmp_k, tmp_t, j;
    for (i = 1; i < n_new_t.size(); i++) {
        tmp_k = n_new_t[i];
        tmp_t = n_new_k[i];
        j = i - 1;

        while (j >= 0 && n_new_t[j] > tmp_k) {
            n_new_t[j + 1] = n_new_t[j];
            n_new_k[j + 1] = n_new_k[j];
            j = j - 1;
        }
        n_new_k[j + 1] = tmp_k;
        n_new_t[j + 1] = tmp_t;
    }


    std::vector<int> mergeK;
    std::vector<int> mergeT;
    i = 0;
    j = 0;
    int k = 0;

    while (i < n_new_t.size() && j < m->tableLen) {
        if (n_new_t[i] < m->tableK[j]) {
            mergeK[k++] = n_new_k[i++];
            mergeT[k++] = n_new_t[i++];
        } else if (n_new_t[i] == m->tableK[j]) {
            if (n_new_t[i] > m->tableK[j]) {
                mergeK[k++] = n_new_k[i++];
                mergeT[k++] = n_new_t[i++];
                j++;
            }
        } else {
            mergeK[k++] = n_new_k[j++];
            mergeT[k++] = n_new_t[j++];
        }
    }


    while (i < n_new_t.size()) {
        mergeK[k++] = n_new_k[i++];
        mergeT[k++] = n_new_t[i++];
    }
    while (j < m->tableLen) {
        mergeK[k++] = n_new_k[j++];
        mergeT[k++] = n_new_t[j++];
    }

    m->tableK = mergeK;
    m->tableT = mergeT;

}

Node *allocateNode() {
    return new Node();
}

