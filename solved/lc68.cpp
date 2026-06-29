#include <bits/stdc++.h>
using namespace std;

// just greedily add more words until total_char_len + word_cnt - 1 > maxWidth.
// then do some math to distribute the number of spaces in between the words.

string helper(const vector<string>& words, int max_width) {
    if (words.size() == 1) {
        string s = words[0];
        s.append(max_width - s.size(), ' ');
        return s;
    }
    
    int cnt = 0;
    for (auto& w : words) cnt += w.size();

    int c = max_width - cnt;
    int d = c / (words.size() - 1);
    int r = c % (words.size() - 1);

    string out = "";
    for (int i = 0; i < words.size(); i++) {
        out.append(words[i]);
        if (i != words.size() - 1) {
            int space_cnt = d + (r-- > 0);
            out.append(space_cnt, ' ');
        }
    }
    return out;
}

class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> out;
        for (int i = 0; i < words.size();) {
            int cnt = 0, total_len = 0;
            int p = i;
            while (p < words.size()) {
                int new_cnt = cnt + 1, new_total_len = total_len + words[p].size();
                if (new_total_len + new_cnt - 1 > maxWidth) break;
                cnt = new_cnt;
                total_len = new_total_len;
                p++;
            }

            // handle last line.
            if (p == words.size()) {
                string s = "";
                for (int j = i; j < p; j++) {
                    s.append(words[j]);
                    if (j < p - 1) s.append(1, ' ');
                }
                s.append(max(0, maxWidth - (int) s.size()), ' ');
                out.push_back(s);
            } else {
                vector<string> subarray(words.begin() + i, words.begin() + p);
                out.push_back(helper(subarray, maxWidth));
            }

            i = p;
        }  
        return out; 
    }
};

int main() {
    Solution sol;
    vector<string> words = {"Science","is","what","we","understand","well","enough","to","explain","to","a","computer.","Art","is","everything","else","we","do"};
    int maxWidth = 20;

    auto ans = sol.fullJustify(words, maxWidth);
    for (auto w : ans) cout << w << endl;
    cout << endl;
}