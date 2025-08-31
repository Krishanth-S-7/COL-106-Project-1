#ifndef LISTNODE_HPP
#define LISTNODE_HPP

#include "file.hpp"

class ListNode{
    public:
    string filename;
    file* f;
    ListNode* next;

    ListNode(string s);
    ~ListNode();

};
#endif