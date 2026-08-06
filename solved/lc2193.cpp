#include <bits/stdc++.h>
using namespace std;

// lc2193: Mininum moves to make palindrome.

// proof for greedy is here https://drive.google.com/file/d/13t_upAk8NEesACY7THM190HkQeiMy2he/view.
// use a implicit treap.
// but given a character, we need to know the index, we can do this by storing for each character
// in the treap node and traversing the parent pointers to get the index.
// index of a node in a implicit treap is simply how many elements are less.

// for each character, use a doubly linked list of treap nodes.
// for each round, get the element at the left, basically leftmost element in the implicit treap.
// then get the character, then get the rightmost node for that character.
// then get the idx, then count how many swaps needed, then remove both nodes.

struct tnode {
    inline static mt19937 rng;

    tnode* parent = nullptr;
    bool side = 0; // 0 means is left child, 1 means is right child (from parent's view)

    char c;
    int sz;
    int prior;

    tnode *left = nullptr, *right = nullptr;

    tnode() {}

    tnode(char c): c(c), sz(1), prior(rng()) {}
};

int get_sz(tnode *node) {
    return node ? node->sz : 0;
}

void set_parent(tnode *node, tnode *parent, bool side = 0) {
    if (!node) return;

    node->parent = parent;
    node->side = side;
}

void set_children(tnode* node, tnode* left, tnode* right) {
    if (!node) return;

    node->left = left;
    set_parent(left, node, 0);

    node->right = right;
    set_parent(right, node, 1);

    node->sz = 1 + get_sz(left) + get_sz(right);
}

int get_idx(tnode* node) {
    int idx = get_sz(node->left);

    tnode* curr = node->parent;
    bool side = node->side;
    while (curr) {
        if (side == 1) idx += 1 + get_sz(curr->left);
        side = curr->side;
        curr = curr->parent;
    }

    return idx;
}

// split into idx < key, idx == key, idx > key
array<tnode*, 3> split(tnode *node, int key) {
    if (!node) return {nullptr, nullptr, nullptr};
    
    int my_key = get_sz(node->left);
    if (my_key == key) {
        set_parent(node, nullptr);

        tnode* left = node->left;
        set_parent(left, nullptr);
        
        tnode* right = node->right;
        set_parent(right, nullptr);

        set_children(node, nullptr, nullptr);

        return {left, node, right};
    } 

    else if (my_key > key) {
        auto [l, e, r] = split(node->left, key);
        set_children(node, r, node->right);
        return {l, e, node};
    }

    else {
        auto [l, e, r] = split(node->right, key - my_key - 1);
        set_children(node, node->left, l);
        return {node, e, r};
    }
}

tnode* merge(tnode* left, tnode* right) {
    if (!left) return right;
    if (!right) return left;

    if (left->prior >= right->prior) {
        set_children(left, left->left, merge(left->right, right));
        return left;
    } else {
        set_children(right, merge(left, right->left), right->right);
        return right;
    }
}

char remove(tnode*& root, int idx) {
    auto [l, e, r] = split(root, idx);
    root = merge(l, r);
    return e->c;
}

class Solution {
public:
    int minMovesToMakePalindrome(string s) {
        tnode* root = nullptr;
        vector<deque<unique_ptr<tnode>>> nodes(26); // owns the pointers.

        for (int i = 0; i < static_cast<int>(s.size()); i++) {
            tnode* node = new tnode(s[i]);
            nodes[s[i] - 'a'].emplace_back(node);
            root = merge(root, node);
        }

        int cnt = 0;
        int curr_sz = s.size();
        
        // if size is 1, no need to do anything anymore.
        // because that element is already at the center of the created palindrome.
        while (curr_sz > 1) {
            char c = remove(root, 0);
            auto& d = nodes[c - 'a'];
            d.pop_front();

            // The only remaining occurrence of c has to be moved to the center.
            if (d.empty()) {
                cnt += curr_sz / 2;
                curr_sz--;
                continue;
            }
            
            auto partner = std::move(d.back());
            d.pop_back();

            int idx = get_idx(partner.get());
            cnt += curr_sz - 2 - idx;

            remove(root, idx);
            curr_sz -= 2;
        }

        return cnt;

    }
};
