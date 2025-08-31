#include "process.hpp"

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
