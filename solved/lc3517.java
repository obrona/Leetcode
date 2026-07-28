// get the left half, then sort in increasing order.
// the right half is just the mirror image.

import java.util.Arrays;

class Solution {
    public String smallestPalindrome(String s) {
        Character middle = (s.length() % 2 == 1) ? s.charAt(s.length() / 2) : null;

        char[] leftHalf = s.substring(0, s.length() / 2).toCharArray();
        Arrays.sort(leftHalf);

        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < leftHalf.length; i++) sb.append(leftHalf[i]);
        if (middle != null) sb.append(middle);
        for (int i = leftHalf.length - 1; i >= 0; i--) sb.append(leftHalf[i]);

        return sb.toString();
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        String s = "babab";
        String ans = sol.smallestPalindrome(s);
        System.out.println(ans);
    }
}