import java.util.List;

class Solution {
    Integer[][] store;

    void init(List<List<Integer>> triangle) {
        store = new Integer[triangle.size()][];
        for (int i = 0; i < triangle.size(); i++) {
            store[i] = new Integer[triangle.get(i).size()];
        }
    }

    int dp(int r, int c, List<List<Integer>> triangle) {
        if (r == triangle.size()) return 0;
        if (store[r][c] != null) return store[r][c];
        if (r == triangle.size() - 1) return triangle.get(r).get(c);

        int sum = triangle.get(r).get(c);
        int a = dp(r + 1, c, triangle);
        int b = c + 1 < triangle.get(r + 1).size() ? dp(r + 1, c + 1, triangle) : 0;
        sum += Math.min(a, b);

        return store[r][c] = sum;
    }

    public int minimumTotal(List<List<Integer>> triangle) {
        init(triangle);
        return dp(0, 0, triangle);
       
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        List<List<Integer>> triangle = List.of(
            List.of(2),
            List.of(3, 4),
            List.of(6, 5, 7),
            List.of(4, 1, 8, 3)
        );

        int ans = sol.minimumTotal(triangle);
        System.out.println(ans);
    }
}
