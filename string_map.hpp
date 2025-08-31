#ifndef STRING_MAP_HPP

#define STRING_MAP_HPP

#include "listnode.hpp"

class string_map{
    int size = 1003;
    vector<ListNode*> m;
    int hash(string s);
    public:
        string_map();

        ~string_map();

        bool find(string s);

        file* get(string s);

        void insert(string s);
};

#endif