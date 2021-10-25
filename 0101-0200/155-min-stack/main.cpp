#include <vector>

class MinStack
{
	std::vector<int> _nums;
	std::vector<size_t> _mins; // _mins[ii] < _mins[ii+1]; _nums[_mins[ii]] > _nums[_mins[ii+1]]

public:
	MinStack() {}

	void push(int val)
	{
		_nums.push_back(val);
		if (_mins.size() == 0) {
			_mins.push_back(0);
			return;
		}

		if (val < _nums.at(*--_mins.end())) {
			_mins.push_back(_nums.size() - 1);
		}
	}

	void pop()
	{
		_nums.pop_back();
		if (*--_mins.end() >= _nums.size()) {
			_mins.pop_back();
		}
	}

	int top()
	{
		return *--_nums.end();
	}

	int getMin()
	{
		return _nums.at(*--_mins.end());
	}
};
