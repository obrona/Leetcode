#include <bits/stdc++.h>
using namespace std;

// simple greedy.
// just add the largest available number.

class Solution {
public:
    string maxSumOfSquares(int num, int sum) {
        string out;
        for (int i = 0; i < num; i++) {
            int d = min(sum, 9);
            sum -= d;
            out.push_back('0' + d);
        }
        return (sum == 0) ? out : "";
    }
};