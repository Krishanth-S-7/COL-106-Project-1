#include "classes.hpp"

using namespace std;

int main(){
    string_map files;
    vector<string> all_files;
    while(true){
        string command;
        getline(cin,command);
        if(command=="EXIT") break;
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
            all_files.push_back(filename);
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
            cout<<"File "<<filename<<" content: "<<f->active()->get_content()<<endl;

            
        }
        else if(inp[0]=="INSERT"){
            if(inp[1]==""){
                cout<<"Enter the file name"<<endl;
                continue;
            }
            string filename = inp[1];
            if (!files.find(filename))
            {
                cout << "File " << filename << " does not exist" << endl;
                continue;
            }
            if(inp[2]==""){
                cout<<"Enter the content to be inserted"<<endl;
                continue;
            }

            string content = inp[2];

            // need to make sure file exists
            
            file* f = files.get(filename);
            f->set_last_modified(time(0));
            string k =f->active()->get_content() + content;
            if(f->active()->get_message()==""){
                f->active()->set_content(k);
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
            string filename = inp[1];
            if (!files.find(filename))
            {
                cout << "File " << filename << " does not exist" << endl;
                continue;
            }
            if(inp[2]==""){
                cout<<"Enter the content to be updated"<<endl;
                continue;
            }
            string content = inp[2];

            // need to make sure file exists

            file* f = files.get(filename);
            f->set_last_modified(time(0));
            if(f->active()->get_message()==""){
                f->active()->set_content(content);
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
            
            string filename = inp[1];
            if (!files.find(filename))
            {
                cout << "File " << filename << " does not exist" << endl;
                continue;
            }
            if(inp[2]==""){
                cout<<"Enter Snapshot message"<<endl;
                continue;
            }

            string message = inp[2];
            // need to make sure file exists

            file* f = files.get(filename);
            if(f->active()->get_message()!=""){
                cout<<"Current version is already snapshotted."<<endl;
                continue;
            }
            else{
                f->active()->set_message(message);
                f->active()->set_timestamp(time(0));
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
                if(f->active() == f->get_root()){
                    cout<<"Already at root version"<<endl;
                    continue;
                }
                f->set_active(f->active()->get_parent());
                cout<<"File "<<inp[1]<<" rolled back to version "<<f->active()->get_version()<<endl;
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
            int_map* vm = f->get_version_map();
            if(!vm->find(version)){
                cout<<"Version "<<version<<" does not exist for file "<<filename<<endl;
                continue;
            }
            TreeNode* v = vm->get(version);
            f->set_active(v);
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
            cout<<"History of file "<<filename<<":"<<endl;
            vector<TreeNode*> h = f->history();
            for(int i = h.size()-1;i>=0;i--){
                time_t snap_time = h[i]->get_snap();
                string dt = ctime(&snap_time);
                dt.pop_back();
                cout<<"Version "<<h[i]->get_version()<<", Timestamp: "<<dt<<", Message: "<<h[i]->get_message()<<endl;
            }
        }
        else if(inp[0]=="RECENT_FILES"){
            if(inp[1]==""){
                cout<<"Enter the number of files"<<endl;
                continue;
            }
            if(inp[2]!=""){
                cout<<"Number of files should be a single integer"<<endl;
                continue;
            }
            if(inp[1][inp[1].size()-1]==' '){
                cout<<"Number of files should not have trailing spaces"<<endl;
                continue;
            }
            int n;
            try{
                n = stoi(inp[1]);
            }
            catch(...){
                cout<<"Invalid number of files"<<endl;
                continue;
            }
            if(n<=0){
                cout<<"Number of files should be positive"<<endl;
                continue;
            }
            // cout << all_files.size() << endl;
            if(n>all_files.size()){
                cout<<"There are only "<<all_files.size()<<" files"<<endl;
                continue;
            }
            vector<pair<time_t,string>> recent;
            for(auto f: all_files){
                recent.push_back({files.get(f)->get_last_modified(),f});
            }
            heapsort<time_t>(recent,n);
            cout<<"Most recent "<<n<<" files:"<<endl;

            for(int i=(int)recent.size()-1;i>=(int)recent.size()-n;i--){
                time_t t = recent[i].first;
                string dt = ctime(&t);
                dt.pop_back();
                cout<<"File Name : "<<recent[i].second<<", Last Modified: "<<dt<<endl;
            }
        }
        else if(inp[0]=="BIGGEST_TREES"){
            if(inp[1]==""){
                cout<<"Enter the number of files"<<endl;
                continue;
            }
            if(inp[2]!=""){
                cout<<"Number of files should be a single integer"<<endl;
                continue;
            }
            int n;
            try{
                n = stoi(inp[1]);
            }
            catch(...){
                cout<<"Invalid number of files"<<endl;
                continue;
            }
            if(n<=0){
                cout<<"Number of files should be positive"<<endl;
                continue;
            }
            if(n>all_files.size()){
                cout<<"There are only "<<all_files.size()<<" files"<<endl;
                continue;
            }
            vector<pair<int,string>> biggest;
            for(auto f: all_files){
                biggest.push_back({files.get(f)->get_total_versions(),f});
            }
            heapsort<int>(biggest,n);
            cout<<"Files with biggest trees:"<<endl;

            for(int i=(int)biggest.size()-1;i>=(int)biggest.size()-n;i--){
                cout<<"File Name : "<<biggest[i].second<<", Size: "<<biggest[i].first<<endl;
            }
        }
        else{
            cout<<"Invalid Command"<<endl;
            continue;
        }
    }
}
