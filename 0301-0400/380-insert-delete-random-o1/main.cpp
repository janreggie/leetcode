#include <cstdlib>
#include <iostream>
#include <unordered_map>
#include <vector>

class RandomizedSet
{
	std::vector<int> _nums;
	std::unordered_map<int, size_t> _indexes;

public:
	RandomizedSet()
	{}

	bool insert(int val)
	{
		if (_indexes.count(val) != 0) {
			return false;
		}
		_indexes[val] = _nums.size();
		_nums.push_back(val);
		return true;
	}

	bool remove(int val)
	{
		if (_indexes.count(val) == 0) {
			return false;
		}

		// Swap _nums[-1] and _nums[ind] where _nums[ind] == val.
		// Well, no need to write _nums[-1] since it'll be popped anyway.
		//
		const size_t ind = _indexes.at(val);
		const int final_elem = _nums[_nums.size() - 1];
		_nums[ind] = final_elem;
		_indexes[final_elem] = ind;
		_indexes.erase(val);
		_nums.pop_back();
		return true;
	}

	int getRandom()
	{
		const size_t ind = (std::rand() % _nums.size());
		return _nums.at(ind);
	}
};

int
main()
{
	RandomizedSet* obj = new RandomizedSet();
	bool param_1 = obj->insert(3);
	bool param_2 = obj->remove(2);
	int param_3 = obj->getRandom();
	std::cout << param_1 << " " << param_2 << " " << param_3 << std::endl;
}

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
