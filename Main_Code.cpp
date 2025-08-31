// #include "classes.hpp"
#include <iostream>
#include "string_map.hpp"
#include "process.hpp"


using namespace std;

int main(){
    string_map files;
    while(true){
        string command;
        getline(cin,command);
        if(command=="exit") break;
        if(command.size()==0) continue;
        vector<string> inp = process(command);
        if(inp[0]=="") continue;
        if(inp[0]=="CREATE"){
            if(inp[1]==""){
                cout<<"Enter the file name"<<endl;
                continue;
            }
            if(inp[2]!=""){
                cout<<"File name cannot contain spaces"<<endl;
                continue;
            }
            string filename = inp[1];
            // need to make sure file doesn't already exist
            if(files.find(filename)){
                cout<<"File "<<filename<<" already exists"<<endl;
                continue;
            }

            files.insert(filename);
            cout<<"File "<<filename<<" created"<<endl;
        }
        else if(inp[0]=="READ"){
            if(inp[1]==""){
                cout<<"Enter the file name"<<endl;
                continue;
            }
            if(inp[2]!=""){
                cout<<"Invalid File Name"<<endl;
                continue;
            }

            // need to make sure file exists

            string filename = inp[1];
            if(!files.find(filename)){
                cout<<"File "<<filename<<" does not exist"<<endl;
                continue;
            }
            //read file from map
            file* f = files.get(filename);
            cout<<"File "<<filename<<" content: "<<f->active_version->content<<endl;

            
        }
        else if(inp[0]=="INSERT"){
            if(inp[1]==""){
                cout<<"Enter the file name"<<endl;
                continue;
            }
            if(inp[2]==""){
                cout<<"Enter the content to be inserted"<<endl;
                continue;
            }

            string content = inp[2];
            string filename = inp[1];
            // need to make sure file exists
            if(!files.find(filename)){
                cout<<"File "<<filename<<" does not exist"<<endl;
                continue;
            }
            file* f = files.get(filename);
            string k =f->active_version->content + content;
            if(f->active_version->message==""){
                f->active_version->content = k;
            }
            else{
                f->insert_version(k);
            }
            cout<<"Content inserted into file "<<filename<<endl;
            //insert content into file
        }
        else if(inp[0]=="UPDATE"){
            if(inp[1]==""){
                cout<<"Enter the file name"<<endl;
                continue;
            }
            if(inp[2]==""){
                cout<<"Enter the content to be updated"<<endl;
                continue;
            }
            string content = inp[2];
            string filename = inp[1];
            // need to make sure file exists
            if(!files.find(filename)){
                cout<<"File "<<filename<<" does not exist"<<endl;
                continue;
            }
            file* f = files.get(filename);
            if(f->active_version->message==""){
                f->active_version->content = content;
            }
            else{
                f->insert_version(content);
            }
            cout<<"File "<<filename<<" updated"<<endl;
        }
        else if(inp[0]=="SNAPSHOT"){
            if(inp[1]==""){
                cout<<"Enter the file name"<<endl;
                continue;
            }
            if(inp[2]==""){
                cout<<"Enter Snapshot message"<<endl;
                continue;
            }
            string filename = inp[1];
            string message = inp[2];
            // need to make sure file exists
            if(!files.find(filename)){
                cout<<"File "<<filename<<" does not exist"<<endl;
                continue;
            }
            file* f = files.get(filename);
            if(f->active_version->message!=""){
                cout<<"Current version is already snapshotted."<<endl;
                continue;
            }
            else{
                f->active_version->message = message;
                f->active_version->snapshot_timestamp = time(0);
                vector<TreeNode*>* h = &f->history;
                h->push_back(f->active_version);
                cout<<"Snapshot created"<<endl;
            }
            //take snapshot of file
        }
        else if(inp[0]=="ROLLBACK"){
            if(inp[1]==""){
                cout<<"Enter the file name"<<endl;
                continue;
            }
            string filename = inp[1];
            if(!files.find(filename)){
                cout<<"File "<<filename<<" does not exist"<<endl;
                continue;
            }
            
            if(inp[2]==""){
                file* f = files.get(inp[1]);
                if(f->active_version == f->root){
                    cout<<"Already at root version"<<endl;
                    continue;
                }
                f->active_version = f->active_version->parent;
                cout<<"File "<<inp[1]<<" rolled back to version "<<f->active_version->version<<endl;
                continue;
            }

            int version;
            if(inp[2][inp[2].size()-1]==' '){
                cout<<"Version ID Should not have Trailing spaces"<<endl;
                continue;
            }
            try{
                version = stoi(inp[2]);
            }
            catch(...){
                cout<<"Invalid version number"<<endl;
                continue;
            }
            
            // need to make sure file exists

            file* f = files.get(filename);
            int_map* vm = &f->version_map;
            if(!vm->find(version)){
                cout<<"Version "<<version<<" does not exist for file "<<filename<<endl;
                continue;
            }
            TreeNode* v = vm->get(version);
            f->active_version = v;
            cout<<"File "<<filename<<" rolled back to version "<<version<<endl;
            //rollback to version
        }
        else if(inp[0]=="HISTORY"){
            if(inp[1]==""){
                cout<<"Enter the file name"<<endl;
                continue;
            }
            if(inp[2]!=""){
                cout<<"Invalid File Name"<<endl;
                continue;
            }
            string filename = inp[1];

            if(!files.find(filename)){
                cout<<"File "<<filename<<" does not exist"<<endl;
                continue;
            }
            file* f = files.get(filename);
            vector<TreeNode*>* h = &f->history;
            cout<<"History of file "<<filename<<":"<<endl;
            for(int i=0;i<h->size();i++){
                cout<<"Version "<<(*h)[i]->version<<", Timestamp: "<<ctime(&(*h)[i]->snapshot_timestamp)<<", Message: "<<(*h)[i]->message<<endl;
            }
        }
        else{
            cout<<"Invalid Command"<<endl;
            continue;
        }
    }
}
