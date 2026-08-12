#include <bits/stdc++.h>
using namespace std;

// just use a trie.
// for the wildcard '.', recurse on every child.

struct trie {
    bool end = false;
    vector<trie*> nexts = vector<trie*>(26, nullptr);
    
    void insert(const string& s, int i = 0) {
        if (i == s.size()) {
            end = true;
            return;
        }

        int idx = s[i] - 'a';
        trie*& next = nexts[idx];
        if (next == nullptr) next = new trie();
        next->insert(s, i + 1);
    }

    bool search(const string& s, int i = 0) {
        if (i == s.size()) {
            return end;
        }

        if (s[i] == '.') {
            bool res = false;
            for (auto ptr : nexts) {
                if (!ptr) continue;
                res = res || ptr->search(s, i + 1);
            }
            return res;
        } else {
            int idx = s[i] - 'a';
            return nexts[idx] && nexts[idx]->search(s, i + 1);
        }
    }
};

void clean_trie(trie*& root) {
    if (!root) return;
    for (auto ptr : root->nexts) clean_trie(ptr);
    delete root;
    root = nullptr;
}

class WordDictionary {
public:
    trie* root = new trie();
    
    WordDictionary() {}
    
    void addWord(string word) {
        root->insert(word);
    }
    
    bool search(string word) {
        return root->search(word);
    }

    ~WordDictionary() {
        clean_trie(root);
    }
};
