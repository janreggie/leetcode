#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
	int search(const vector<int>& nums, int target) {
		return searchRotated(nums, target, 0, nums.size()-1);
	}

private:
	int searchRotated(const vector<int>& nums, int target, int ii, int jj) {

		cout << "searchRotated on indices " << ii << "," << jj << endl;

		if (ii == jj) { return target == nums[ii] ? ii : -1; }
		if (target == nums[ii]) { return ii; }
		if (target == nums[jj]) { return jj; }
		if (nums[ii] < nums[jj]) { return searchOrdinary(nums, target, ii, jj); } // In case if it's actually sorted

		int mid{(ii+jj)/2};
		if (nums[mid] == target) { return mid; }

		if (nums[mid] > nums[ii]) { // the "Drop" is after mid
			cout << "target:" << target << ",nums[mid]:" << nums[mid] << ",nums[jj]:" << nums[jj] << endl;
			if (target > nums[mid] || target <= nums[jj]) { return searchRotated(nums, target, mid+1, jj); }
			return searchOrdinary(nums, target, ii, mid);

		} else { // The "Drop" is below mid
			if (target < nums[mid] || target >= nums[ii]) { return searchRotated(nums, target, ii, mid); }
			return searchOrdinary(nums, target, mid, jj);
		}
	}

	int searchOrdinary(const vector<int>& nums, int target, int ii, int jj) {

		cout << "searchOrdinary on indices " << ii << "," << jj << endl;

		if (ii == jj) { return target == nums[ii] ? ii : -1; }
		if (target == nums[ii]) { return ii; }
		if (target == nums[jj]) { return jj; }

		int mid{(ii+jj)/2};
		if (target == nums[mid]) { return mid; }
		if (target < nums[mid]) { return searchOrdinary(nums, target, ii, mid); }
		return searchOrdinary(nums, target, mid+1, jj);
	}
};

int main() {
	Solution soln;
	const vector<int> nums{3,5,1};
	const int target{2};
	cout << soln.search(nums, target) << endl;
}