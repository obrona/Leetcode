// suppose we no land ride then water ride.
// for land ride, take shortest waterDuration among waterStart that start before end time
// and take smallest waterStart + waterDuration for all water riders that start after.

// we need to sort by landStart + landDuration
// then for water rides we need to sort by waterStart
// as we progress by landStart + landDuration in increasing order, we update the left min
// and use precomputed suffix min to get the right min.

import java.util.Arrays;

class Solution {

    int[] getSuffixMin(int[] arr) {
        int[] out = new int[arr.length];
        for (int i = arr.length - 1; i > -1; i--) {
            if (i == arr.length - 1) {
                out[i] = arr[i];
            } else {
                out[i] = Math.min(out[i + 1], arr[i]);
            }
        }
        return out;
    }

    int solve(int[] landStartTime, int[] landDuration, int[] waterStartTime, int[] waterDuration) {
        int[] aeArr = new int[landStartTime.length];
        for (int i = 0; i < landStartTime.length; i++) {
            aeArr[i] = landStartTime[i] + landDuration[i];
        }
        Arrays.sort(aeArr);

        int[][] temp = new int[waterStartTime.length][3];
        for (int i = 0; i < waterStartTime.length; i++) {
            temp[i] = new int[]{i, waterStartTime[i], waterDuration[i]};
        }
        Arrays.sort(temp, (x, y) -> x[1] - y[1]);

        int[] be = new int[waterStartTime.length];
        for (int i = 0; i < waterStartTime.length; i++) {
            be[i] = temp[i][1] + temp[i][2];
        }
        int[] suffixMin = getSuffixMin(be);

        int min = (int) 1e9;
        int minLeft = (int) 1e9;
        int p = 0;
        for (int x : aeArr) {
            while (p < be.length && temp[p][1] <= x) {
                minLeft = Math.min(minLeft, temp[p][2]);
                p++;
            }
            
            int before = x + minLeft;
            int after = (p == be.length) ? (int) 1e9 : suffixMin[p];
            
            min = Math.min(min, Math.min(before, after));
        }

        return min;
    }

    public int earliestFinishTime(int[] landStartTime, int[] landDuration, int[] waterStartTime, int[] waterDuration) {
        int landFirst = solve(landStartTime, landDuration, waterStartTime, waterDuration);
        int waterFirst = solve(waterStartTime, waterDuration, landStartTime, landDuration);
        return Math.min(landFirst, waterFirst);
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        int[] landStartTime = {2,8}, landDuration = {4,1}, waterStartTime = {6}, waterDuration = {3};
        int ans = sol.earliestFinishTime(landStartTime, landDuration, waterStartTime, waterDuration);
        System.out.println(ans);
    }
}