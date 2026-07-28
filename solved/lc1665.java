import java.util.Arrays;

// sort the tasks in decreasing minimum - actual energy.
// sorting in decreasing mininum energy only is wrong, consider [999, 999] and [1, 10]
// we must do the [1, 10] then [999, 999] so that total energy used is just 1000.

// proof ?
// let the tasks be [m1-d1, m1], [m2-d2, m2] ... [mn-dn, mn]
// the contraints on e are 
// m1 + sum(m2 - d2 ... mn - dn) <= e
// m2 + sum(m3 - d3 ... mn - dn) <= e
// mn <= e.
// as long e satisfy this contraints, e is valid.

// e = max(mi + sum(mi+1 - di+1, mi+2 - di+2 ... mn - dn))
// consider index i, i + 1 and di > di+1
// 1st contrainst mi + k + mi+1 - di+1 becomes mi+1 + k + mi - di, which is better.
// for the 2nd constraint mi+1 + k vs mi + k, it could be that mi + k is higher,

// case work for the different cases mi < mi+1, mi > mi+1.
// just sub in some numbers for [mi, di] [mi+1, di+1] to convince yourself.
// this means processing in decreasing difference is the optimal way.
// will show you that the effective constraint decreases.
// eg (14, 2) vs (9, 10) tuple[i] represents contraint i


class Solution {
    public int minimumEffort(int[][] tasks) {
        Arrays.sort(tasks, (x, y) -> x[1] - x[0] - (y[1] - y[0]));

        int e = 0;
        int sum = 0;
        for (int i = tasks.length - 1; i >= 0; i--) {
            e = Math.max(e, tasks[i][1] + sum);
            sum += tasks[i][0];
        }
        return e;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        int[][] tasks = {{1,3}, {2,4}, {10,11}, {10,11}, {8,9}};

        int ans = sol.minimumEffort(tasks);
        System.out.println(ans);
    }
}