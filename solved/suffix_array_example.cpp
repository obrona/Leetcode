#include <bits/stdc++.h>
using namespace std;

struct SuffixArray {
    int domain;
    vector<int> sa, lcp;

    SuffixArray(int domain, const vector<int>& arr): domain(domain), sa(arr.size(), 0), lcp(arr.size(), -1) {
        get_sa(arr);
        get_lcp(arr);
    }

    void _radix_sort(vector<array<int, 3>>& arr) {
        static vector<vector<array<int,3>>> bins(domain + 10, vector<array<int,3>>());
        
        for (int i = 2; i >= 1; i--) {
            for (auto it = arr.begin(); it != arr.end(); it++) {
                bins[(*it)[i]].push_back(*it);
            }

            arr.clear();
            for (auto& bin : bins) {
                arr.insert(arr.end(), bin.begin(), bin.end());
                bin.clear();
            }
        }

        for (auto& bin : bins) bin.clear();
    }

    void _compress_rank(vector<array<int,3>>& arr) {
        array<int,3> prev = arr[0];
        arr[0][1] = 1;
        arr[0][2] = 0;
        
        for (auto it = arr.begin() + 1; it != arr.end(); it++) {
            auto tmp = *it;
            if ((*it)[1] == prev[1] && (*it)[2] == prev[2]) {
                (*it)[1] = (*(it - 1))[1];
            } else {
                (*it)[1] = (*(it - 1))[1] + 1;
            }
            (*it)[2] = 0;
            prev = tmp;
        }
    }


    void _extend_rank(vector<array<int,3>>& arr, int pow) {
        vector<int> pos_to_rank(arr.size(), 0);
        for (auto& p : arr) {
            pos_to_rank[p[0]] = p[1];
        }

        for (auto& p : arr) {
            int next = p[0] + (1 << pow);
            if (next >= arr.size()) {
                p[2] = 0;
            } else {
                p[2] = pos_to_rank[next];
            }
        }
    }

    void get_sa(const vector<int>& arr) {
        vector<array<int,3>> store;
        for (int i = 0; i < arr.size(); i++) {
            store.push_back({i, arr[i], ((i + 1) >= arr.size()) ? 0 : arr[i + 1]});
        }

        int pow = 1;
        while (1) {
            _radix_sort(store);
            _compress_rank(store);
            _extend_rank(store, pow);
            if ((1 << pow) >= arr.size()) break;
            pow++;
        }

        for (int i = 0; i < store.size(); i++) {
            sa[i] = store[i][0];
        }
    }

    void get_lcp(const vector<int>& arr) {
        vector<int> pos_to_idx(sa.size(), 0);
        for (int i = 0; i < sa.size(); i++) {
            pos_to_idx[sa[i]] = i;
        }

        int h = 0;
        for (int i = 0; i < arr.size(); i++) {
            if (pos_to_idx[i] == 0) {
                h = 0;
                continue;
            }

            h = max(0, h - 1);
            int prev = sa[pos_to_idx[i] - 1];
            while (max(h + i, h + prev) < arr.size() && arr[h + i] == arr[h + prev]) {
                h++;
            }

            lcp[pos_to_idx[i]] = h;
        }
    }
};

// returns the domain too and compresses (modifies) arr.
int _compress(vector<int>& arr) {
    auto tmp = arr;
    sort(tmp.begin(), tmp.end());
    
    int cnt = 1;
    unordered_map<int,int> store;
    store[tmp[0]] = cnt;
    for (int i = 1; i < tmp.size(); i++) {
        if (tmp[i] != tmp[i - 1]) cnt++;
        store[tmp[i]] = cnt;
    }

    for (int& x : arr) {
        x = store[x];
    }

    return cnt;
}

void test() {
    vector<int> arr = {2, 2, 3, 2, 2, 1};
    int d = _compress(arr);
    SuffixArray sa(d, arr);

    for (int x : sa.sa) cout << x << " "; cout << endl;
    for (int x : sa.lcp) cout << x << " "; cout << endl;
}

int main() {
    test();
}