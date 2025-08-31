#include "file.hpp"


file::file(){
        root = new TreeNode(0,"","",NULL);
        version_map.insert(0,root);
        active_version = root;
        total_versions = 1;
    }
file::~file(){
        delete root;
    }

void file::insert_version(string message){
        TreeNode* newnode = new TreeNode(total_versions,message,"",active_version);
        active_version->children.push_back(newnode);
        version_map.insert(total_versions,newnode);
        active_version = newnode;
        total_versions++;
    }
