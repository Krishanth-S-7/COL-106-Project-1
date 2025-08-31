#ifndef HEAP_HPP
#define HEAP_HPP

#include "listnode.hpp"

void heapify(vector<pair<int,TreeNode*>>& v, int n, int i);

void buildheap(vector<pair<int, TreeNode*>>& v, int n, int i);

void heapsort(vector<pair<int, TreeNode*>>& v);

#endif