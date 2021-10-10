#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> twoSum(const vector<int>& nums, int target) {

		vector<int> sortedNums(nums);
		sort(sortedNums.begin(), sortedNums.end());
		const pair<int,int> addends{findTwoSum(sortedNums, target, 0, sortedNums.size()-1)};

		vector<int> result(2);
		result[0] = findIndexOf(nums, addends.first);
		result[1] = findIndexOf(nums, addends.second);
		if (result[0] == result[1]) { result[1] = findIndexOf(nums, addends.second, result[0]+1); }
		return result;
    }

private:
	pair<int,int> findTwoSum(const vector<int>& sortedNums, int target, int i1, int i2) {

		if (i1 >= int(sortedNums.size()) || i2 < 0) { throw overflow_error("indices out of bounds"); }

		const int sum{sortedNums[i1]+sortedNums[i2]};
		if (sum == target) return pair<int,int>(sortedNums[i1], sortedNums[i2]);
		if (sum > target) { --i2; }
		if (sum < target) { ++i1; }
		return findTwoSum(sortedNums, target, i1, i2);
	}

	int findIndexOf(const vector<int>& nums, int n, int startAt = 0) {
		for (int ii{startAt}; ii < int(nums.size()); ++ii) {
			if (nums[ii] == n) { return ii; }
		}
		return -1;
	}
};

int main() {
	cout << "Running..." << endl;

	const std::vector<int> input{-1, -2, -3, -4, -5};
	const int target{-8};
	Solution soln;
	const vector<int> answer{soln.twoSum(input, target)};

	cout << answer[0] << endl << answer[1] << endl;
}
