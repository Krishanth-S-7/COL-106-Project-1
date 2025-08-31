#include "treenode.hpp"
#include "int_map.hpp"


int_map::int_map(){
            m.resize(size);
        }


void int_map::insert(int k, TreeNode* v){
            if(currcap==size){
            m.resize(2*size);
            size *= 2;
            }
            m[currcap] = {k,v};
            currcap++;
        }

bool int_map::find(int k){
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

TreeNode* int_map::get(int k){
            return m[k].second;
        }

void int_map::erase(int k){
            if(k<0 || k>=currcap){
                return;
            }
            m[k].second = NULL;
        }
