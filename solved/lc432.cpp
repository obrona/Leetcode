#include <bits/stdc++.h>
using namespace std;

// key here is incr and decr is by 1 only.
// use a doubly linked list.
// each linked list store a set of strings.
// linked list store values in decreasing order.
// front of the linked list is the highest vals, back of the linked list is the lowest value
// then store a hashmap of str -> linked list node.

// when incr, check the prev node, if it is of the correct cnt, insert there,
// else create a new node to the left and insert into it.
// when decr check the prev node, if it is of the correc cnt, insert there,
// else create a new node to the right and insert into it.

struct Store {
    int cnt = 0;
    unordered_set<string> my_strings;
};

class AllOne {
public:
    list<Store> ll;
    unordered_map<string, list<Store>::iterator> mapper;

    AllOne() {
        
    }

    
    void insert_prev(list<Store>::iterator curr_it, string key, int new_cnt) {
        auto next_it = curr_it;
        if (next_it == ll.begin() || (--next_it)->cnt > new_cnt) {
            next_it = ll.emplace(curr_it);
            next_it->cnt = new_cnt;
        } 
        
        next_it->my_strings.insert(key);
        mapper[key] = next_it;

        erase_key_from_store(curr_it, key);
    }

    void insert_next(list<Store>::iterator curr_it, string key, int new_cnt) {
        auto next_it = next(curr_it);
        if (next_it == ll.end() || next_it->cnt < new_cnt) {
            next_it = ll.emplace(next_it);
            next_it->cnt = new_cnt;
        }
        
        next_it->my_strings.insert(key);
        mapper[key] = next_it;

        erase_key_from_store(curr_it, key);
    }

    void erase_key_from_store(list<Store>::iterator curr_it, string key) {
        if (curr_it == ll.end()) return;
        
        curr_it->my_strings.erase(key);
        if (curr_it->my_strings.empty()) {
            ll.erase(curr_it);
        }
    }
    
    void inc(string key) {
        if (!mapper.contains(key)) {
            insert_prev(ll.end(), key, 1);
        } else {
            auto curr_it = mapper[key];
            insert_prev(curr_it, key, curr_it->cnt + 1);
        }
        
    }
    
    void dec(string key) {
        auto curr_it = mapper[key];
        if (curr_it->cnt == 1) {
            mapper.erase(key);
            erase_key_from_store(curr_it, key);
        } else {
            insert_next(curr_it, key, curr_it->cnt - 1);
        }
        
    }
    
    string getMaxKey() {
        if (ll.empty()) {
            return "";
        }
        return *ll.front().my_strings.begin();
    }
    
    string getMinKey() {
        if (ll.empty()) {
            return "";
        }
        return *ll.back().my_strings.begin();
    }
};

int main() {
    AllOne sol;

    sol.inc("hello");
    sol.inc("hello");
    cout << sol.getMaxKey() << endl;
    cout << sol.getMaxKey() << endl;
    sol.inc("leet");
    cout << sol.getMaxKey() << endl;
    cout << sol.getMinKey() << endl;
}
