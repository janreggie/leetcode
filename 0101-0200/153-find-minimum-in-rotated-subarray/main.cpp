#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
	int findMin(const vector<int> &nums)
	{
		if (nums.size() == 1) { return nums[0]; }
		return findMinRecursive(nums, 0, nums.size()-1);
	}

private:
	int findMinRecursive(const vector<int> &nums, int ii, int jj)
	{
		if (jj - ii == 1) { return min(nums[ii], nums[jj]); }

		int mid{(jj + ii) / 2};
		if (nums[mid] > nums[jj])
		{
			return findMinRecursive(nums, mid, jj);
		}
		return findMinRecursive(nums, ii, mid);
	}
};

int main()
{
	const vector<int> input{4,5,6,7,0,1,2};
	Solution soln;
	const int result{soln.findMin(input)};
	cout << result << endl;
}
