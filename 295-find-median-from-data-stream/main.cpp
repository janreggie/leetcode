#include <iostream>
#include <vector>
#include <set>

class MedianFinder
{

	std::multiset<int> _left;
	std::multiset<int> _right;

	void info() {

		std::cout << "Left is as follows: ";
		for (const auto& it : _left) { std::cout << it << ","; }
		std::cout << std::endl;
		std::cout << "Right is as follows: ";
		for (const auto& it : _right) { std::cout << it << ","; }
		std::cout << std::endl;
	}

public:
	/** initialize your data structure here. */
	MedianFinder() : _left{}, _right{}
	{
	}

	void addNum(int num)
	{
		if (_left.size() == 0)
		{
			_left.insert(num);
			return;
		}

		// Insert the number to the appropriate "bucket".
		//
		if ((_left.size()+_right.size()) % 2 == 0) // i.e., even
		{
			if (*(_right.begin()) < num)
			{
				_left.insert(*_right.begin());
				_right.erase(_right.begin());
				_right.insert(num);
			}
			else
			{
				_left.insert(num);
			}

		} else // i.e., odd
		{
			if (*(_left.rbegin()) > num)
			{
				_right.insert(*_left.rbegin());
				_left.erase(--_left.end()); // can't take in rbegin
				_left.insert(num);
			}
			else
			{
				_right.insert(num);
			}
		}
	}

	double findMedian() const
	{
		if (_left.size() > _right.size()) {
			return *_left.rbegin();
		}

		return (double)(*_left.rbegin() + *_right.begin()) / 2;
	}
};

struct Testcase
{
	const std::vector<std::string> _fxns;
	const std::vector<int> _params;
};

int main()
{
	std::multiset<int> st;
	st.insert(1);
	st.insert(4);
	st.insert(3);
	st.insert(4);
	st.insert(5);
	st.erase(4);

	for (const auto& it : st) {
		std::cout << it << std::endl;
	}
}
