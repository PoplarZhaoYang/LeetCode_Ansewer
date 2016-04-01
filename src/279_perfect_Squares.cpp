/*******
 * **题意**:给你一个数n,问你求组合为它的平方数的最小的个数
 * **分析**:有小到大的枚举平方数,然后用完全背包的思想即可,复杂度$O(n)\sqrt{n}$
 */

class Solution {
public:
    int numSquares(int n) {
        int dp[1000000];
        for (int i = 0; i <= n; i++) dp[i] = int(1e10);
        dp[0] = 0;
        for (long long i = 1; i * i <= n; ++i) {
            for (int j = i * i; j <= n; j++) {
                dp[j] = min(dp[j], dp[j - i *i] + 1);
            }
        }
        return dp[n];
    }

};
