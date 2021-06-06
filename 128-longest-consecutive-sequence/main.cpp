#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestConsecutive(const vector<int>& nums) {
        
        if (nums.size() < 2) { return (int)(nums.size()); }
        
        unordered_set<int> numbers;
        unordered_set<int> starts;
        
        for (const int& num : nums) {
            numbers.insert(num);
        }
        
        for (const int& num : numbers) {
            if (numbers.count(num+1) != 0 && numbers.count(num-1) == 0) {
                starts.insert(num);
            }
        }

        int record{1};
        for (const int& start : starts) {
            int current{1};
            for (int num{start+1}; numbers.count(num) != 0; ++num) {
                ++current;
            }
            record = max(record, current);
        }
        
        return record;
    }
};

int main() {

	const vector<int> nums{100,4,200,1,3,2};
	Solution soln;
	cout << soln.longestConsecutive(nums) << endl;
}
