#include <unordered_map>
#include <vector>

class Solution
{
	std::unordered_map<size_t, int> _memo;

public:
	int maxProfit(const std::vector<int>& prices)
	{
		const size_t n = prices.size();
		if (n <= 1) {
			return 0;
		}
		if (n == 2) {
			return std::max(0, prices[1] - prices[0]);
		}

		// Otherwise, let's iterate.
		// * There is a O(n) solution here. We just need to find it...
		int buy = 0;              // Something is bought
		int sell = prices[n - 1]; // Being sold
		int cooldown = 0;         // We're on cooldown

		for (size_t ii = n - 2; ii < n; --ii) {
			const int obuy = buy, osell = sell, ocooldown = cooldown;
			buy = std::max(obuy, -prices[ii] + osell);
			sell = std::max(osell, prices[ii] + ocooldown);
			cooldown = obuy;
		}

		return std::max(buy, cooldown);
	}
};
