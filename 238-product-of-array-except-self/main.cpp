#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(const vector<int>& nums) {

		long productOfAll{1};
		int zeroCount{0};
		size_t lastZeroIndex{0};

		for (size_t ii{0}; ii < nums.size(); ++ii) {
			if (nums[ii] == 0) {
				++zeroCount;
				lastZeroIndex = ii;
			} else {
				productOfAll *= nums[ii];
			}
		}

		vector<int> result(nums.size());
		if (zeroCount > 1) { return result; }
		if (zeroCount == 1) {
			result[lastZeroIndex] = productOfAll;
			return result;
		}

		for (size_t ii{0}; ii < result.size(); ++ii) {
			result[ii] = int(productOfAll/nums[ii]);
		}
		return result;
    }
};

int main() {
	vector<int> nums{1,2,3,4};
	Solution soln;
	vector<int> result{soln.productExceptSelf(nums)};

	for (int num: result) {
		cout << num << endl;
	}
}