//
// Created by YanRu Jhou on 2021/9/13.
//

#ifndef LSM_TESTCASE_H
#define LSM_TESTCASE_H

#include "../include/lsm_template.h";

class TestCase {
public:
    Node<int> *root;
    std::map<Node<int> *, std::set<int>> esr;
    std::map<int, std::optional<int>> Vr;

    TestCase();

    TestCase(Node<int> *root, std::map<Node<int> *, std::set<int>> esr, std::map<int, std::optional<int>> Vr);

    void reset();

    void test1();

    void printContent(Node<int> *n);

    void testMerge();

    void testMerge2();

    void testMerge3();

};


#endif //LSM_TESTCASE_H
