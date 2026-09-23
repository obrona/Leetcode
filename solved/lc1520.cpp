#include <bits/stdc++.h>
using namespace std;

// let dp(i) = max number of non overlapping substring from str[i:]
// subtrings need to contain all occurence of a character.
// suppose we are at dp(i) and we want to take a substring starting at index i.
// the character of str[i] the 1st occurence is here and the last occurence is j.
// then we take max of arr[i, j]
// if the end pointer has to shift, it can introduce new characters, which mean the end pointer can shift again.
// but each extension must introduce a new character not seen before.
// at most 26 characters so only extend 26 times.
// a substring s[i:j] is valid if the max end = j and the min start = i.
// at index i, if it is possible to build a valid substring, we always take the shortest one.
// this is easy to prove why.

// since we need to build the solution, we need to build a routing table.

struct sparse_table {
    int max_pow;
    vector<vector<int>> table;
    function<int(int,int)> reducer;

    sparse_table() {}

    sparse_table(const vector<int>& arr, function<int(int,int)> reducer): reducer(reducer) {
        max_pow = bit_width(arr.size());
        table = vector(arr.size(), vector(max_pow, -1));

        for (int i = 0; i < arr.size(); i++) {
            table[i][0] = arr[i];
        }

        for (int p = 1; p < max_pow; p++) {
            for (int i = 0; i < arr.size(); i++) {
                int left = table[i][p - 1];
                int right_idx = i + (1 << (p - 1));
                int right = right_idx >= arr.size() ? 0 : table[right_idx][p - 1];
                table[i][p] = reducer(left, right);
            }
        }
    }

    int query(int l, int r) {
        int len = r - l + 1;
        int p = bit_width((size_t) len) - 1;
        return reducer(table[l][p], table[r - (1 << p) + 1][p]);
    }
};

struct take {
    int start_idx, end_idx;
};

struct notake {};

struct result {
    int num_of_substrings, total_length_of_substrings;
    int next;
    variant<take, notake> action;
};

class Solution {
public:
    string s;
    vector<int> end;
    sparse_table max_st, min_st;

    vector<optional<result>> dp_store;

    result dp(int i) {
        if (i == s.size()) {
            return result {
                .num_of_substrings = 0,
                .total_length_of_substrings = 0,
                .next = i,
                .action = notake{}
            };
        }

        auto& ans = dp_store[i];
        if (ans) return ans.value();

        auto no_take = dp(i + 1);

        bool valid = true;
        int end_idx = i;
        while (1) {
            int next_end_idx = max_st.query(i, end_idx);
            int next_start_idx = min_st.query(i, next_end_idx);
            
            if (next_start_idx < i) {
                valid = false;
                break;
            }

            if (end_idx == next_end_idx) {
                break;
            }
            
            end_idx = next_end_idx;
        }
        
        // cannot take substring starting at index i
        if (!valid) {
            ans = result{
                .num_of_substrings = no_take.num_of_substrings,
                .total_length_of_substrings = no_take.total_length_of_substrings,
                .next = i + 1,
                .action = notake{}
            };
        } 
        
        // can take substring starting at index i.
        else {
            auto take_res = dp(end_idx + 1);
            int num_of_substrings = 1 + take_res.num_of_substrings;
            int total_length_of_substrings = end_idx - i + 1 + take_res.total_length_of_substrings;

            if (num_of_substrings > no_take.num_of_substrings 
                || num_of_substrings == no_take.num_of_substrings 
                   && total_length_of_substrings < no_take.total_length_of_substrings
            ) {
                ans = result{
                    .num_of_substrings = num_of_substrings,
                    .total_length_of_substrings = total_length_of_substrings,
                    .next = end_idx + 1,
                    .action = take{i, end_idx}
                };
            } else {
                ans = result{
                    .num_of_substrings = no_take.num_of_substrings,
                    .total_length_of_substrings = no_take.total_length_of_substrings,
                    .next = i + 1,
                    .action = notake{}
                };
            }
        }

        return ans.value();
    }

    vector<string> reconstruct() {
        vector<string> store;
        int curr_state = 0;

        while (curr_state != s.size()) {
            auto res = dp(curr_state);

            visit([&store, this] (const auto& v) {
                using T = decay_t<decltype(v)>;
                
                if constexpr (is_same_v<T, take>) {
                    store.push_back(s.substr(v.start_idx, v.end_idx - v.start_idx + 1));
                }
            }, res.action);

            curr_state = res.next;
        }

        return store;
    }


    vector<string> maxNumOfSubstrings(string s) {
        unordered_map<char, pair<int,int>> store;
        for (int i = 0; i < s.size(); i++) {
            if (!store.contains(s[i])) {
                store[s[i]] = {i, i};
            } else {
                store[s[i]].second = i;
            }
        }

        vector<int> min_arr(s.size()), max_arr(s.size());
        for (int i = 0; i < s.size(); i++) {
            min_arr[i] = store[s[i]].first;
            max_arr[i] = store[s[i]].second;
        }

       

        max_st = sparse_table(max_arr, [] (int x, int y) { return max(x, y); });
        min_st = sparse_table(min_arr, [] (int x, int y) { return min(x, y); });

        dp_store = vector(s.size(), optional<result>());

        this->s = move(s);

        auto res = reconstruct();
        return res;
    }
};