# Given two strings str1 and str2, return the shortest string that has both str1 and str2 as subsequences. If there are multiple valid strings, return any of them.
# A string s is a subsequence of string t if deleting some number of characters from t (possibly 0) results in the string s.


# Example 1:

# Input: str1 = "abac", str2 = "cab"
# Output: "cabac"
# Explanation:
# str1 = "abac" is a subsequence of "cabac" because we can delete the first "c".
# str2 = "cab" is a subsequence of "cabac" because we can delete the last "ac".
# The answer provided is the shortest such string that satisfies these properties.


class Solution:
    def shortestCommonSupersequence(self, A: str, B: str) -> str:
        def lcs():
            m, n = len(A), len(B)
            dp = [[""] * (n + 1) for _ in range(m + 1)]

            for i in range(m):
                for j in range(n):
                    if A[i] == B[j]:
                        dp[i + 1][j + 1] = dp[i][j] + A[i]
                    else:
                        dp[i + 1][j + 1] += max(dp[i + 1]
                                                [j], dp[i][j + 1], key=len)

            return dp[-1][-1]

        res, i, j = '', 0, 0

        # dp[M][N] is the length of the LCS of s and t, and M + N - dp[M][N] is the length of the shortest common supersequence
        for c in lcs():
            while A[i] != c:
                res += A[i]
                i += 1

            while B[j] != c:
                res += B[j]
                j += 1

            res += c
            i, j = i + 1, j + 1

        return res + A[i:] + B[j:]
