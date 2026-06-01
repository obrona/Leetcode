#include <bits/stdc++.h>
using namespace std;

// can use suffix automaton.
// suffix automaton is a finite state automata.
// each substring in the string can be represented as a series of transition.
// terminal nodes are such that any path from root to a terminal node will create a string that is a suffix.

// let endpos be a set for a substring. It represents the end indices of all occurence of that substring in s
// eg abb, endpos for b is {1, 2}
 
// every node in a suffix automaton corresponds to a set of substrings with the same endpos

// let w be the longest substring of the equivalence class. Then every node has a suffix link to another node, 
// whose w' is the longest suffix of w with a different equivalence class (which definitely is bigger).

// when transiting to different state, always choose node v with the smallest len(v). We maintain that invariant.

// when adding a new character, let last be the last node created.

// the suffix link for the new node must be from a node from the transitive chain starting from the suffix link of last
// let w be the suffix string for last, and then for the new node, it ends to the left of w
// call it w'.
// there exist an end index for w' such that the total string processed does not appear
// but w' - c is is the same equivalence class of last so last string appears too, and since c is the last character, we get curr
// string which is a contradiction.

// when we clone a node, must redirect all transition c from p to clone and also do this for the suffix link chain of p.

// all incoming edges into a node have the same transition character.

// finding substring that occurs once is simply counting the size of endpos per node.


struct State {
    int len = 0, link = -1;
    unordered_map<int,int> next;
    bool is_terminal = false;
    int occ = 0;
};

struct SuffixAutomation {
    int last = 0;
    vector<State> store;

    SuffixAutomation(int len) {
        store.reserve(2 * len + 10);
        store.emplace_back();
    }

    pair<int, State&> add_node() {
        return {store.size(), store.emplace_back()};
    }

    void extend(int c) {
        auto [curr_idx, curr] = add_node();
        curr.len = store[last].len + 1;
        curr.occ = 1;

        int p = last;
        for (; p != -1 && !store[p].next.contains(c); p = store[p].link) {
            store[p].next[c] = curr_idx;
        }

        if (p == -1) {
            curr.link = 0;
        } else {
            int q = store[p].next[c];

            if (store[q].len == store[p].len + 1) {
                curr.link = q;
            } else {
                auto [clone_idx, clone] = add_node();

                // clone.occ is 0 for now, because we are gonna link 
                clone = State{store[p].len + 1, store[q].link, store[q].next};
                
                store[q].link = curr.link = clone_idx;
                
                while (p != -1 && (store[p].next.contains(c) && store[p].next[c] == q)) {
                    store[p].next[c] = clone_idx;
                    p = store[p].link;
                }
            }   
        }

        last = curr_idx;
    }

    void mark_terminal() {
        for (int p = last; p != -1; p = store[p].link) {
            store[p].is_terminal = true;
        }
    }

    int solve() {
        // for each node we want cnt[v] which is the size of endpos.
        // suppose 2 nodes have the same suffix link, then the intersection of endpos is null. 
        // if intersection is not null, then one of these 2 nodes suffix link must be to the other, contradiction.
        vector<pair<int,int>> order;
        for (int i = 0; i < store.size(); i++) {
            order.emplace_back(i, store[i].len);
        }
        sort(order.begin(), order.end(), [] (auto a, auto b) { return a.second > b.second; });
        for (auto [i, _] : order) {
            if (store[i].link == -1) continue;
            store[store[i].link].occ += store[i].occ;
        }

        // to get min length of a node (i.e shortest substring of the equivalence class) no need to bfs
        // it is just len(suffix_link) + 1
        int best = 999999;
        for (int i = 1; i < store.size(); i++) {
            if (store[i].occ > 1) continue;
            int min_length = store[store[i].link].len + 1;
            best = min(best, min_length);
        }

        return best;
    }
};

class Solution {
public:
    int smallestUniqueSubarray(vector<int>& nums) {
        SuffixAutomation sam(nums.size());
        for (int x : nums) {
            sam.extend(x);
        }
        sam.mark_terminal();
        return sam.solve();
    }
};

int main() {
    Solution sol;
    vector<int> nums = {2,1,2,3,3};
    int ans = sol.smallestUniqueSubarray(nums);
    println("{}", ans);
}