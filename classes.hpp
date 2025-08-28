#ifndef CLASSES_HPP
#define CLASSES_HPP

#include<iostream>
#include <vector>
#include<ctime>
using namespace std;

class TreeNode{
    private:
        int version;
        string content;
        string message = "0";
        time_t created_timestamp;
        time_t snapshot_timestamp;
        TreeNode* parent;
        vector<TreeNode*> children;
    public:
    string get_message(){
        return message;
    }
};

#endif