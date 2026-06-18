// just try all possible pairs.

class Solution {
    public int earliestFinishTime(int[] landStartTime, int[] landDuration, int[] waterStartTime, int[] waterDuration) {
        int best = 999999999;
        
        for (int i = 0; i < landStartTime.length; i++) {
            for (int j = 0; j < waterStartTime.length; j++) {
                int a = landStartTime[i], ae = landDuration[i];
                int b = waterStartTime[j], be = waterDuration[j];
                
                // either a go first or b go first.
                int afirst = Math.max(b, a + ae) + be;
                int bfirst = Math.max(a, b + be) + ae;
                //System.out.printf("%d %d %d %d\n", i, j, afirst, bfirst);
                best = Math.min(best, Math.min(afirst, bfirst));

            }
        }

        return best;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        int[] landStartTime = {2,8};
        int[] landDuration = {4,1};
        int[] waterStartTime = {6};
        int[] waterDuration  = {3};

        int ans = sol.earliestFinishTime(landStartTime, landDuration, waterStartTime, waterDuration);
        System.out.println(ans);
    }
}