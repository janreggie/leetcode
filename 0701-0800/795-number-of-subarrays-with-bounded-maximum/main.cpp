#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
	int numSubarrayBoundedMax(const vector<int>& nums, int left, int right) {
		
		const vector<vector<size_t>> patterns{getPatterns(nums, left, right)};
		int result{0};

		for (const vector<size_t>& pattern : patterns) {
			result += countCombinationsInPattern(pattern);
		}
		return result;
	}
	
private:

	// getPatterns returns an array of "patterns",
	// where each "pattern" describes how nums is arranged.
	// e.g., nums={2,3,4,1,4,3,2,1,0,3}, left=2, right=4
	// patterns={{10,1,2}}.
	// There exists a subarray of length 10 where no number is greater than right,
	// and there are subarrays within of lengths 1 and 2 ({1},{1,0}) which consist of numbers less.
	//
	vector<vector<size_t>> getPatterns(const vector<int>& nums, int left, int right) {
		
		vector<vector<size_t>> result;
		vector<size_t> current; // current pattern
		
		for (size_t ii{0}; ii < nums.size(); ++ii) {
			
			const int num{nums.at(ii)};
			if (num > right) {
				if (current.size() > 0) {
					result.push_back(current);
					current = {};
				}
				continue;
			}
			
			if (current.size() == 0) {
				current.push_back(1);
				if (num < left) { current.push_back(1); }
				else { current.push_back(0); }
				continue;
			}

			++current.at(0);
			if (num >= left) {
				if (current.at(current.size()-1) != 0) {
					current.push_back(0);
				}
			} else {
				++current.at(current.size()-1);
			}
		}
		
		if (current.size() != 0) { result.push_back(current); }
		return result;
	}
	
	int countCombinationsInPattern(const vector<size_t>& pattern) {
	
		int result{gauss(pattern.at(0))};
		for (size_t ii{1}; ii < pattern.size(); ++ii) { result -= gauss(pattern.at(ii)); }
		return result;
	}
	
	// Sum from 1 to N
	int gauss(size_t n) {

		return (int)(n*(n+1)/2);
	}
};

int main() {

	const vector<int> nums{73,55,36,5,55,14,9,7,72,52};
	int left{32}, right{69};
	Solution soln;
	cout << soln.numSubarrayBoundedMax(nums,left,right) << endl;
}
