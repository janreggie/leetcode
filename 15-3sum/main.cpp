#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
	vector<vector<int>> threeSum(const vector<int>& nums) {

		const size_t len{nums.size()};
		if (len <= 2) { return vector<vector<int>>{}; }

		vector<int> sortedNums(nums);
		sort(sortedNums.begin(), sortedNums.end());

		vector<vector<int>> triplets;
		for (size_t ii{0}; ii < len && sortedNums[ii] <= 0; ++ii) {
			int expectSum{-sortedNums[ii]};
			size_t jj{ii+1}, kk{len-1};
			while (jj < kk) {
				int actualSum{sortedNums[jj]+sortedNums[kk]};
				if (actualSum == expectSum) {
					appendToResult(triplets, sortedNums[ii], sortedNums[jj], sortedNums[kk]);
					++jj;
					--kk;
				}
				else if (actualSum < expectSum) { ++jj; }
				else { --kk; }
			}
		}
		return triplets;
    }

private:
	void appendToResult(vector<vector<int>>& result, int a, int b, int c) {
		vector<int> toAdd{a,b,c};
		const size_t len{result.size()};
		if (len == 0) { return result.push_back(toAdd); }

		for (size_t ii{len-1}; ii <= len-1; --ii) {
			if (result[ii][0] != a) { break; }
			if (result[ii] == toAdd) { return; }
		}
		result.push_back(toAdd);
	}
};

int main() {
	const vector<int> input{-1,0,1,2,-1,-4};
	Solution soln;
	vector<vector<int>> output{soln.threeSum(input)};
	for (const auto& triplet : output) {
		for (const int& vv : triplet) cout << vv << " ";
		cout << endl;
	}
}
