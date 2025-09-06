#ifndef CLASSES_HPP
#define CLASSES_HPP

#include<iostream>
#include <vector>
#include<ctime>
#include<sstream>
using namespace std;

// TreeNode Creation

class TreeNode{
    
        int version;
        string content;
        string message ;
        time_t created_timestamp;
        time_t snapshot_timestamp;
        TreeNode* parent;
        vector<TreeNode*> children;
    public:
    TreeNode(int v , string c, string m, TreeNode* p = NULL){
        version = v;
        content = c;
        message = m;
        parent = p;
        created_timestamp = time(0);
        snapshot_timestamp = 0;
    }
    TreeNode* get_parent(){
        return parent;
    }
    time_t get_snap(){
        return snapshot_timestamp;
    }
    int get_version(){
        return version;
    }
    void add_child(TreeNode* child){
        children.push_back(child);
    }
    string get_message(){
        return message;
    }
    void set_content(string c){
        content = c;
    }
    string get_content(){
        return content;
    }
    void set_message(string m){
        message = m;
    }
    void set_timestamp(time_t t){
        snapshot_timestamp = t;
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

    TreeNode* root;
    int_map version_map;
    TreeNode* active_version;
    int total_versions = 0;
    time_t last_modified;
    // vector<TreeNode*> history;
    public:
    file(){
        root = new TreeNode(0,"","",NULL);
        version_map.insert(0,root);
        active_version = root;
        total_versions = 1;
        last_modified = time(0);
    }
    time_t get_last_modified(){
        return last_modified;
    }
    int get_total_versions(){
        return total_versions;
    }
    void set_last_modified(time_t t){
        last_modified = t;
    }
    TreeNode* active(){
        return active_version;
    }
    TreeNode* get_root(){
        return root;
    }

    ~file(){
        delete root;
    }
    int_map* get_version_map(){
        return &version_map;
    }
    void insert_version(string message){
        TreeNode* newnode = new TreeNode(total_versions,message,"",active_version);
        active_version->add_child(newnode);
        version_map.insert(total_versions,newnode);
        active_version = newnode;
        total_versions++;
    }

    void set_active(TreeNode* x){
        active_version = x;
    }
    vector<TreeNode*> history(){
        vector<TreeNode*> h;
        if(active_version->get_message()!=""){
            h.push_back(active_version);
        }
        TreeNode* temp = active_version->get_parent();
        while(temp!=NULL){
            if(temp->get_message()!=""){
                h.push_back(temp);
            }
            temp = temp->get_parent();
        }
        return h;
    }
};


// List Node

class ListNode{
    
    string filename;
    file* f;
    ListNode* next;
    public:
    ListNode(string s){
        filename = s;
        next = NULL;
    }
    ListNode* get_next(){
        return next;
    }
    file* get_file(){
        return f;
    }
    void set_file(file* fileptr){
        f = fileptr;
    }
    string get_filename(){
        return filename;
    }
    void set_next(ListNode* n){
        next = n;
    }
    ~ListNode(){
    }
};

//Heap Functions

template<typename T>
bool isgreater( pair<T,string> &a, pair<T,string> &b){
    if(a.first != b.first){
        return a.first > b.first;
    }
    else{
        return a.second < b.second;
    }
}

template<typename T>
void heapify(vector<pair<T,string>>& v, int n, int i){
    int pos = i;
    while(true){
        int left = 2*pos + 1;
        int right = 2*pos + 2;
        int largest = pos;
        if(left <= n && isgreater(v[left], v[largest])){
            largest = left;
        }
        if(right <= n && isgreater(v[right], v[largest])){
            largest = right;
        }
        if(largest != pos){
            swap(v[pos], v[largest]);
            pos = largest;
        }
        else{
            break;
        }
    }
}

template<typename T>
void buildheap(vector<pair<T,string>>& v, int n, int i) {
    for (int j = n; j >= i; j--) {
        heapify<T>(v, n, j);
    }
}

template<typename T>
void heapsort(vector<pair<T,string>>& v, int k) {
    int n = v.size();
    buildheap<T>(v, n - 1, 0);

    for (int i = n - 1; i >= n - k; i--) {
        swap(v[0], v[i]);
        heapify<T>(v, i - 1, 0);
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
                    ListNode* next = node->get_next();
                    delete node->get_file();
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
                if(temp->get_filename()==s){
                    return true;
                }
                temp = temp->get_next();
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
                if(temp->get_filename()==s){
                    return temp->get_file();
                }
                temp = temp->get_next();
            }
            return NULL;
        }
        void insert(string s){
            int h = hash(s);
            file* f = new file();
            f->get_root()->set_message("Initial version");
            f->get_root()->set_timestamp(time(0));
            // f->push_history(f->get_root());
            ListNode* newnode = new ListNode(s);
            newnode->set_file(f);
            if(m[h]==NULL){
                m[h] = newnode;
            }
            else{
                ListNode* temp = m[h];
                while(temp->get_next()!=NULL){
                    temp = temp->get_next();
                }
                temp->set_next(newnode);
            }
        }
};

#endif