#include <bits/stdc++.h>
using namespace std;

// greedy solution. 
// At time t, among all tasks that is free, always do the task with the largest remaining count.
// suppose not, so we take B instead of A, we can swap the B's and the A's and the solution is still valid.
// must do tasks with most remaining count first, eg BA...A vs AB..A, n = 3.

// so we have 2 priority queue, the task queue and the ready queue.
// the ready queue stores the ready to start task sorted in decreasing remaining count.
// the task queue is sorted by increasing next free time.

struct metadata {
    int remaining;
    int next_free_time;
    char task;

    //metadata() {}

    //metadata(int r, int n, char t): remaining(r), next_free_time(n), task(t) {}
};

struct metadata_cmp {
    bool operator()(const metadata& p1, const metadata& p2) {
        if (p1.next_free_time != p2.next_free_time) {
            return p1.next_free_time > p2.next_free_time;
        }
        return false;
    }
};

priority_queue<metadata, vector<metadata>, metadata_cmp> process(const vector<char>& tasks) {
    unordered_map<char, int> store;
    for (char c : tasks) store[c]++;

    vector<pair<char,int>> arr(store.begin(), store.end());
    sort(arr.begin(), arr.end(), [] (auto& p1, auto& p2) { return p1.second > p2.second; });

    priority_queue<metadata, vector<metadata>, metadata_cmp> q;
    for (auto p : arr) {
        q.emplace(p.second, 1, p.first);
    }

    return q;

}

class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        auto q = process(tasks);

        auto special_cmp = [] (auto& m1, auto& m2) { return m1.remaining < m2.remaining; };
        priority_queue<metadata, vector<metadata>, decltype(special_cmp)> ready(special_cmp);
        int curr_time = 1;

        auto pop_into_ready = [&] (int curr_time) {
            while (!q.empty()) {
                auto m = q.top();
                if (m.next_free_time > curr_time) break;
                q.pop();
                ready.push(m);
            }
        };

        while (!q.empty() || !ready.empty()) {
            pop_into_ready(curr_time);
            if (ready.empty()) {
                curr_time = q.top().next_free_time;
                continue;
            }

            auto m = ready.top();
            //println("{} {}", m.task, m.remaining);
            ready.pop();
            if (m.remaining > 1) {
                q.emplace(m.remaining - 1, curr_time + 1 + n, m.task);
            }

            curr_time++;
        }

        return curr_time - 1;
    }
};

int main() {
    Solution sol;
    vector<char> tasks = {'A','A','A','A','B','C','D','G'};
    int n = 1;

    int ans = sol.leastInterval(tasks, n);
    cout << ans << endl;
}