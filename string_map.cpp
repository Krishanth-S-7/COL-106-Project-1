

#include "string_map.hpp"


int string_map::hash(string s){
            int h = 5381;
            for(int i=0;i<s.size();i++){
                h = (h*31 + s[i])%size;
            }
            return h;
        }

string_map::string_map(){
                m.resize(size);
            }

string_map::~string_map(){
                for (auto node : m) {
                    while (node) {
                        ListNode* next = node->next;
                        delete node->f;
                        delete node;    
                        node = next;
                    }
                }
        }

bool string_map::find(string s){
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

file* string_map::get(string s){
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

void string_map::insert(string s){
                int h = hash(s);
                file* f = new file();
                f->root->message = "Initial version";
                f->root->snapshot_timestamp = time(0);
                f->history.push_back(f->root);
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