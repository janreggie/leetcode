#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
	bool isInterleave(const string& s1, const string& s2, const string& s3) {

		if (s1.size() + s2.size() != s3.size()) { return false; }

		vector<vector<bool>> dp(s1.size()+1, vector<bool>(s2.size()+1));
		dp[0][0] = true;
		for (size_t ii{0}; ii < s1.size(); ++ii) { dp[ii+1][0] = dp[ii][0] && (s1[ii] == s3[ii]); }
		for (size_t jj{0}; jj < s2.size(); ++jj) { dp[0][jj+1] = dp[0][jj] && (s2[jj] == s3[jj]); }

		for (size_t ii{1}; ii <= s1.size(); ++ii) {
			for (size_t jj{1}; jj <= s2.size(); ++jj) {
				dp[ii][jj] = ((dp[ii-1][jj] && (s3[ii+jj-1] == s1[ii-1])) || (dp[ii][jj-1] && (s3[ii+jj-1] == s2[jj-1])));
			}
		}

		return dp[s1.size()][s2.size()];
	}
};

int main() {
	const string s1 = "aabcc";
	const string s2 = "dbbca";
	const string s3 = "aadbbcbcac";
	Solution soln;
	bool result = soln.isInterleave(s1, s2, s3);
	cout << (result ? "true" : "false") << endl;
}
