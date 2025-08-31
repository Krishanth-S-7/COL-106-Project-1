#ifndef FILE_HPP
#define FILE_HPP

#include "treenode.hpp"
#include "int_map.hpp"



class file{
    public:
    TreeNode* root;
    int_map version_map;
    TreeNode* active_version;
    int total_versions = 0;
    vector<TreeNode*> history;

    file();

    ~file();

    void insert_version(string message);
};
#endif