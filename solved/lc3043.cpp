#include <bits/stdc++.h>
using namespace std;

// use just a trie.

struct node {
    vector<unique_ptr<node>> nexts = vector<unique_ptr<node>>(10);
};

void insert(unique_ptr<node>& current, int i, const string& num) {
    if (i == num.size()) {
        return;
    }

    int x = num[i] - '0';
    auto& next = current->nexts[x];
    if (!next) {
        next = make_unique<node>();
    }

    insert(next, i + 1, num);
}

int max_depth(unique_ptr<node>& current, int i, const string& num) {
    if (i == num.size()) {
        return i;
    }

    int x = num[i] - '0';
    auto& next = current->nexts[x];
    if (!next) {
        return i;
    } else {
        return max_depth(next, i + 1, num);
    }
}

class Solution {
public:
    int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2) {
        auto root = make_unique<node>();

        for (const auto& s : arr2) {
            insert(root, 0, to_string(s));
        }

        int best = 0;
        for (const auto& s : arr1) {
            int res = max_depth(root, 0, to_string(s));
            best = max(best, res);
        }

        return best;
    }
};

int main() {
    Solution sol;

    vector<int> arr1 = {1,10,100};
    vector<int> arr2 = {1000};

    int ans = sol.longestCommonPrefix(arr1, arr2);
    cout << ans << endl;
}
