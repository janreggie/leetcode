#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxSubArray(const vector<int>& nums) {
        
        int currentPsum{nums[0]};
        int maximumPsum{nums[0]};
        
        for (size_t ii{1}; ii < nums.size(); ++ii) {
            currentPsum = max(nums[ii], currentPsum+nums[ii]);
            maximumPsum = max(currentPsum, maximumPsum);
        }
        
        return maximumPsum;
	}
};
