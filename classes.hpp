#ifndef CLASSES_HPP
#define CLASSES_HPP

#include<iostream>
#include <vector>
#include<ctime>
#include<sstream>
using namespace std;

// TreeNode Creation

class TreeNode{
    public:
        int version;
        string content;
        string message ;
        time_t created_timestamp;
        time_t snapshot_timestamp;
        TreeNode* parent;
        vector<TreeNode*> children;

    TreeNode(int v , string c, string m, TreeNode* p = NULL){
        version = v;
        content = c;
        message = m;
        parent = p;
        created_timestamp = time(0);
        snapshot_timestamp = 0;
    }
    ~TreeNode(){
        for(TreeNode* child: children){
            delete child;
        }
    }
};

//HashMap creation

class int_map{
    private:
        long long size = 10;
        vector<pair<int,TreeNode*>> m;
        long long currcap = 0;
    public:
        int_map(){
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
        bool find(int k){
            if(k<0 || k>=currcap){
                return false;
            }
            if(m[k].second==NULL){
                return false;
            }
            else{
                return true;
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




// File Structure

class file{
    public:
    TreeNode* root;
    int_map version_map;
    TreeNode* active_version;
    int total_versions = 0;
    file(){
        root = new TreeNode(0,"","",NULL);
        version_map.insert(0,root);
        active_version = root;
        total_versions = 1;
    }
    ~file(){
        delete root;
    }
    void insert_version(string message){
        TreeNode* newnode = new TreeNode(total_versions,message,"",active_version);
        active_version->children.push_back(newnode);
        version_map.insert(total_versions,newnode);
        active_version = newnode;
        total_versions++;
    }
};


// List Node

class ListNode{
    public:
    string filename;
    file* f;
    ListNode* next;
    ListNode(string s){
        filename = s;
        next = NULL;
    }
    ~ListNode(){
    }
};
//Heap Functions

void heapify(vector<pair<int,TreeNode*>>& v, int n, int i){
    int pos = i;
    int left = 2*i + 1;
    int right = 2*i + 2;
    while(right<=n){
        if(v[pos].first < min(v[left].first,v[right].first)){
            break;
        }
        else{
            if(v[left].first < v[right].first){
                swap(v[pos],v[left]);
                pos = left;
            }
            else{
                swap(v[pos],v[right]);
                pos = right;
            }
        }
        left = 2*pos + 1;
        right = 2*pos + 2;
    }
    if(left==n && v[pos].first > v[left].first){
        swap(v[pos],v[left]);
    }
}

void buildheap(vector<pair<int, TreeNode*>>& v, int n, int i) {
    for (int j = (n - 1) / 2; j >= i; j--) {
        heapify(v, n, j);
    }
}


void heapsort(vector<pair<int, TreeNode*>>& v) {
    int n = v.size();
    buildheap(v, n - 1, 0);
    for (int i = n - 1; i > 0; i--) {
        swap(v[0], v[i]);
        heapify(v, i - 1, 0);
    }
}








// Input Processing

vector<string> process(string command){
    vector<string> result = {"","",""};
    int i=0;
    while(i<command.size() && command[i]!=' '){
            result[0] += command[i];
            i++;
        }
    while(i<command.size() && command[i]==' '){
        i++;}
    while(i<command.size() && command[i]!=' '){
        result[1] += command[i];
        i++;
    }
    while(i<command.size() && command[i]==' '){
        i++;}
    while(i<command.size()){
        result[2] += command[i];
        i++;
    }
    return result;
}

class string_map{
    int size = 1003;
    vector<ListNode*> m;
    int hash(string s){
        int h = 5381;
        for(int i=0;i<s.size();i++){
            h = (h*31 + s[i])%size;
        }
        return h;
    }
    public:
        string_map(){
            m.resize(size);
        }
        ~string_map(){
            for (auto node : m) {
                while (node) {
                    ListNode* next = node->next;
                    delete node->f;
                    delete node;    
                    node = next;
                }
            }
    }
        bool find(string s){
            int h = hash(s);
            if (m[h]==NULL){
                return false;
            }
            ListNode* temp = m[h];
            while(temp!=NULL){
                if(temp->filename==s){
                    return true;
                }
                temp = temp->next;
            }
            return false;
        }
        file* get(string s){
            int h = hash(s);
            if (m[h]==NULL){
                return NULL;
            }
            ListNode* temp = m[h];
            while(temp!=NULL){
                if(temp->filename==s){
                    return temp->f;
                }
                temp = temp->next;
            }
            return NULL;
        }
        void insert(string s){
            int h = hash(s);
            file* f = new file();
            f->root->message = "Initial version";
            ListNode* newnode = new ListNode(s);
            newnode->f = f;
            if(m[h]==NULL){
                m[h] = newnode;
            }
            else{
                ListNode* temp = m[h];
                while(temp->next!=NULL){
                    temp = temp->next;
                }
                temp->next = newnode;
            }
        }
};

#endif