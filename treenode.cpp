#include "treenode.hpp"

TreeNode::TreeNode(int v , string c, string m, TreeNode* p){
        version = v;
        content = c;
        message = m;
        parent = p;
        created_timestamp = time(0);
        snapshot_timestamp = 0;
    }

TreeNode::~TreeNode(){
        for(TreeNode* child: children){
            delete child;
        }
    }