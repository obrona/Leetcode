#include <bits/stdc++.h>
using namespace std;

// for each element, get the largest element from the left and the largest element to the right.
// because the amount of water contained at index i 
// is max(0, min(largest elem from left, largest elem from right) - height[i])

class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        vector<int> left(n, 0), right(n, 0);

        int l = 0;
        for (int i = 1; i < n; i++) {
            left[i] = l = max(l, height[i - 1]);
        }

        int r = 0;
        for (int i = n - 2; i > -1; i--) {
            right[i] = r = max(r, height[i + 1]);
        }

        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += max(0, min(left[i], right[i]) - height[i]);
        }
        return sum;
    }
};

int main() {
    Solution sol;

    vector<int> height = {0,1,0,2,1,0,1,3,2,1,2,1};

    int ans = sol.trap(height);
    cout << ans << endl;
}