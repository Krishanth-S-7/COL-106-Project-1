#include "heap.hpp"

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

