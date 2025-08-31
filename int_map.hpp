#ifndef INT_MAP_HPP
#define INT_MAP_HPP
#include "treenode.hpp"

class int_map{
    private:
        long long size = 10;
        vector<pair<int,TreeNode*>> m;
        long long currcap = 0;
    public:
        int_map();

        void insert(int k, TreeNode* v);

        bool find(int k);

        TreeNode* get(int k);

        void erase(int k);
};

#endif