#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool containsDuplicate(const vector<int>& nums) {

		if (nums.size() <= 1) { return false; }
		if (nums.size() == 2) { return nums[0]==nums[1]; }

		vector<int> sortedNums(nums);
		sort(sortedNums.begin(), sortedNums.end());
		
		int previous{sortedNums[0]};
		for (size_t ii{1}; ii < sortedNums.size(); ++ii) {
			if (previous == sortedNums[ii]) { return true; }
			previous = sortedNums[ii];
		}

		return false;
    }
};

int main() {

	Solution soln;
	const vector<int> nums{1,2,3,1};
	cout << soln.containsDuplicate(nums) << endl;
}