#include <vector>

class Solution
{
	size_t _n;
	std::vector<int> _nums;
	std::vector<bool> _result;

public:
	bool canJump(const std::vector<int>& nums)
	{
		_n = nums.size();
		_nums = nums;
		_result = std::vector<bool>(_n);
		_result[_n - 1] = true;

		for (size_t ind = _n - 2; ind < _n; --ind) {
			_result[ind] = canJump(ind, _nums[ind]);
		}

		return _result[0];
	}

private:
	bool canJump(size_t ind, size_t jumps)
	{
		if (ind >= _n - 1) {
			return true;
		}
		if (_result[ind]) {
			return true;
		}
		if (jumps <= 0) {
			return false;
		}
		return canJump(ind + 1, jumps - 1);
	}
};
