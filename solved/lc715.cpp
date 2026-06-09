#include <bits/stdc++.h>
using namespace std;

// store a set of disjoint half open intervals.
// sorted by left, we do not care about right.
// we cannot have [x, y) and [y, z), we must merge them to [x, z).

// each range is inserted and remove once, so total time complexity is O(nlogn).
// actually not really true, but still can pass.

class RangeModule {
public:

    set<pair<int,int>, function<bool(pair<int,int>, pair<int,int>)>> store{
        [] (auto p1, auto p2) { return p1.first < p2.first; }
    };
    
    RangeModule() {}
    
    void addRange(int left, int right) {
        auto it = store.lower_bound({left, left});
        if (it != store.begin()) {
            it = prev(it);
            auto [l, r] = *it;
            if (r >= left) {
                left = l;
                right = max(right, r);
                store.erase(it);
            }
        }

        for (auto it = store.lower_bound({left, left}); 
             it != store.end() && it->first <= right; 
             it = store.lower_bound({left, left})) 
        {
            right = max(right, it->second);
            store.erase(it);
        }

        store.emplace(left, right);


    }
    
    // only way is for a single existing range to encompass [left, right).
    // for that range [x, y), either x = left or x < left and y >= right
    bool queryRange(int left, int right) {
        auto it = store.lower_bound({left, left});
        if (it != store.end() && it->first == left && it->second >= right) return true;
        if (it != store.begin()) {
            it = prev(it);
            if (it->second >= right) return true;
        } 
        return false;
    }
    
    void removeRange(int left, int right) {
        auto it = store.lower_bound({left, right});
        if (it != store.begin()) {
            it = prev(it);
            
            int l = it->first, r = it->second;
            if (r > left) {
                store.erase(it);
                store.emplace(l, left);
            }
            if (r > right) {
                store.emplace(right, r);
            }
        }

        for (auto it = store.lower_bound({left, left}); 
             it != store.end() && it->first < right;
             it = store.lower_bound({left, left})) 
        {
            if (it->second <= right) {
                store.erase(it);
            } else {
                int tmp = it->second;
                store.erase(it);
                store.emplace(right, tmp);
                break;
            }
        }
    }
};

int main() {
    RangeModule rg;
    rg.addRange(10, 20);
    rg.removeRange(14, 16);
    println("{}", rg.queryRange(10, 14));
    println("{}", rg.queryRange(13, 15));
    println("{}", rg.queryRange(16, 17));
}
