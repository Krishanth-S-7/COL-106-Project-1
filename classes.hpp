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

class map{
    private:
        long long size = 10;
        vector<pair<int,TreeNode*>> m;
        long long currcap = 0;
    public:
        map(){
            m.resize(size);
        }
        void insert(int k, TreeNode* v){
            if(currcap==size){
            m.resize(2*size);
            size *= 2;
            }
            m[currcap] = {k,v};
            currcap++;
        }
        int find(int k){
            if(k<0 || k>=currcap){
                return -1;
            }
            if(m[k].second==NULL){
                return -1;
            }
            else{
                return k;
            }
        }
        TreeNode* get(int k){
            return m[k].second;
        }
        void erase(int k){
            if(k<0 || k>=currcap){
                return;
            }
            m[k].second = NULL;
        }
};

class file{
    public:
    TreeNode* root;
    map versions;
    TreeNode* active_version;
    int total_versions = 0;
    file(){
        root = new TreeNode();
        versions.insert(0,root);
        active_version = root;
        total_versions = 1;
    }
    ~file(){
        delete root;
    }
};
#endif