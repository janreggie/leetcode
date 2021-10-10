#include <iostream>
#include <vector>

class Solution
{
public:
	int rob(const std::vector<int>& nums)
	{
		const size_t n = nums.size();
		if (n == 0) {
			return 0;
		}
		if (n == 1) {
			return nums[0];
		}
		return std::max(
		  robLinear(std::vector(nums.begin(), nums.end() - 1)),
		  robLinear(std::vector(nums.begin() + 1, nums.end())));
	}

private:
	int robLinear(const std::vector<int>& nums)
	{
		const size_t n = nums.size();
		if (n == 0) {
			return 0;
		}
		if (n == 1) {
			return nums[0];
		}

		std::vector<int> dp(n);
		dp[n - 1] = nums[n - 1];
		dp[n - 2] = std::max(nums[n - 2], nums[n - 1]);
		for (size_t ind = n - 3; ind < n; --ind) {
			dp[ind] = std::max(nums[ind] + dp[ind + 2], dp[ind + 1]);
		}

		return std::max(dp[0], dp[1]);
	}
};

int
main()
{

	const std::vector<int> houses{ 5, 6, 131, 4, 6, 696, 7, 420 };
	Solution soln;
	std::cout << soln.rob(houses) << std::endl;
}
