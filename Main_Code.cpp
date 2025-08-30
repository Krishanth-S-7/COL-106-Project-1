#include "classes.hpp"

using namespace std;


int main(){
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

            //add file to map
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

            //read file from map
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
            //update content into file
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
            //take snapshot of file
        }
        else if(inp[0]=="ROLLBACK"){
            if(inp[1]==""){
                cout<<"Enter the file name"<<endl;
                continue;
            }
            if(inp[2]==""){
                cout<<"Enter the version id"<<endl;
                continue;
            }
            string filename = inp[1];
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
            // need to make sure file exists
            //print history of file
        }
        else{
            cout<<"Invalid Command"<<endl;
            continue;
        }
    }
}
