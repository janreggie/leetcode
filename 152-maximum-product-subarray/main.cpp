#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxProduct(const vector<int>& nums) {
		
		if (nums.size() == 0) { return 0; }
		if (nums.size() == 1) { return nums[0]; }

		// vector<int> nums(_nums);
		// while (true) {
		// 	vector<int> betterNums{groupTogether(nums)};
		// 	if (betterNums.size() < nums.size()) { nums = betterNums; }
		// 	else { break; }
		// }

		int product{1};
		for (int num : nums) { product *= num; }
		if (product > 0) { return product; }

		const list<vector<int>> splitGroups{splitByZeroes(nums)};
		int record{product};
		for (const vector<int>& group : splitGroups) {
			record = max(record, maximumFromGroup(group));
		}

		return record;
    }
    
    vector<int> groupTogether(const vector<int>& nums) {
		vector<int> result(0);
		int groupProduct{nums[0]};
		int groupParity{parity(groupProduct)};

		for (size_t ii{1}; ii < nums.size(); ++ii) {

			int num{nums[ii]};
			int numParity{parity(num)};

			if (numParity != groupParity) {
				result.push_back(groupProduct);
				groupProduct = num;
				groupParity = numParity;
			} else {
				groupProduct *= num;
				groupParity = parity(groupProduct);
			}
		}

		result.push_back(groupProduct); // ultimate pushback

		return result;
	}

	list<vector<int>> splitByZeroes(const vector<int>& nums) {
		list<vector<int>> result;
		vector<int> group;

		for (int num : nums) {
			if (num == 0) {
				if (group.size() != 0) {
					result.push_back(group);
					group = vector<int>(0);
				}
			} else {
				group.push_back(num);
			}
		}

		if (group.size() != 0) {
			result.push_back(group);
		}

		return result;
	}

	// Assume no zeroes! Returns 0 if length is zero.
	//
	int maximumFromGroup(const vector<int>& nums) {

		if (nums.size() == 0) { return 0; }
		if (nums.size() == 1) { return nums[0]; }

		int product{1};
		for (int num : nums) { product *= num; }
		if (product >= 0) { return product; } // Also avoid division by zero bs

		int prefix{1}; // product of first n terms until it becomes negative
		for (size_t ii{0}; ii < nums.size(); ++ii) {
			prefix *= nums[ii];
			if (prefix < 0) break;
		}
		int suffix{1}; // product of last n terms until it becomes negative
		for (size_t ii{nums.size()-1}; ; --ii) {
			suffix *= nums[ii];
			if (suffix < 0) break;
		}

		return max(product/prefix, product/suffix);
	}

	int parity(int num) {
		if (num == 0) return 0;
		if (num > 0) return 1;
		return -1;
	}
};

int main() {

	const vector<int> input{2,-5,-2,-4,3};
	Solution soln;
	const int result{soln.maxProduct(input)};
	cout << result << endl;
}