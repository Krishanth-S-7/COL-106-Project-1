#ifndef TREENODE_HPP
#define TREENODE_HPP

#include<string>
#include<ctime>
#include<vector>
using namespace std;

class TreeNode{
    public:
        int version;
        string content;
        string message ;
        time_t created_timestamp;
        time_t snapshot_timestamp;
        TreeNode* parent;
        vector<TreeNode*> children;

    TreeNode(int v , string c, string m, TreeNode* p = NULL);
    ~TreeNode();
};


#endif