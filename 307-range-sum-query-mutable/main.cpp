#include <cassert>
#include <iostream>
#include <string>
#include <vector>

std::ostream& operator<<(std::ostream& os, const std::vector<int>& v) {

	if (v.size() == 0) { os << "{}"; return os; }
	os << "{" << v.at(0);
	for (size_t ii{1}; ii < v.size(); ++ii) {
		os << "," << v.at(ii);
	}
	os << "}";
	return os;
}

class NumArray {

	// Buckets are a way to store numbers and the "sums" in their buckets
	// without manually consulting too many times.
	// For example, if _buckets were of length 1024, and BUCKET_SIZE=10,
	// _buckets.at(0) would store the actual 1024 numbers,
	// _buckets.at(1) would store 102 buckets wherein _buckets[1][ii] == Sum from _buckets[0][ii*10] to _buckets[0][ii*10+9] inclusive
	// _buckets.at(2) would store 10 buckets which stores the sums of _buckets.at(1), and so on.

	static constexpr size_t BUCKET_SIZE{2};
	std::vector<std::vector<int>> _buckets;

public:
	NumArray(const std::vector<int>& nums) {

		_buckets = {nums};

		// Populate the buckets to make it easier for us to count the partial sums
		//
		for (size_t bucketCount{nums.size()/BUCKET_SIZE}; bucketCount > 0; bucketCount /= BUCKET_SIZE) {

			std::vector<int> partialSums(bucketCount);
			for (size_t ii{0}; ii<bucketCount; ++ii) {
				int partialSum{0};
				for (size_t jj{ii*BUCKET_SIZE}; jj < (ii+1)*BUCKET_SIZE; ++jj) {
					partialSum += _buckets.at(_buckets.size()-1).at(jj);
				}
				partialSums.at(ii) = partialSum;
			}
			_buckets.push_back(partialSums);
		}
	}

	void update(int index, int val) {

		const int old{_buckets.at(0).at(index)};
		_buckets.at(0).at(index) = val;
		index /= BUCKET_SIZE;

		for (size_t ii{1}; ii<_buckets.size(); ++ii) {

			if (_buckets.at(ii).size() <= (size_t)index) { break; } // At the "last element" since we don't consider those
			_buckets.at(ii).at(index) += (val-old);
			index /= BUCKET_SIZE;
		}
	}

	int sumRange(int left, int right) {

		return sumRange((size_t)left, (size_t)right);
	}

private:
	int sumRange(size_t left, size_t right) {

		int result{_buckets.at(0).at(right)};

		// Compute the sum [0,right):
		//
		for (size_t depth{0}; right > 0; ++depth) {

			size_t next{right/BUCKET_SIZE};
			for (size_t ii{next*BUCKET_SIZE}; ii<right; ++ii) {
				result += _buckets.at(depth).at(ii);
			}
			right = next;
		}

		// Compute the sum [0, left)
		//
		for (size_t depth{0}; left > 0; ++depth) {

			size_t next{left/BUCKET_SIZE};
			for (size_t ii{next*BUCKET_SIZE}; ii<left; ++ii) {
				result -= _buckets.at(depth).at(ii);
			}
			left = next;
		}

		return result;
	}
};

struct Testcase {

	const std::vector<std::string> _commands;  // {"NumArray", "sumRange", "update", "sumRange"}
	const std::vector<std::vector<int>> _args; // {{1,3,5},{0,2},{1,2},{0,2}}
	const std::vector<int> _expected;          // {0, 9, 0, 8}

	void test() const {

		assert(_commands.size() == _args.size());

		NumArray na(_args.at(0));
		std::cout << "Initialized NumArray with arguments " << _args.at(0) << std::endl;

		for (size_t ii{1}; ii < _commands.size(); ++ii) {

			assert(_args.at(ii).size() == 2);
			const int x{_args.at(ii).at(0)}, y{_args.at(ii).at(1)};

			if (_commands.at(ii) == "update") {
				std::cout << "NumArray.update(" << x << "," << y << ")" << std::endl;
				na.update(x,y);
				continue;
			}

			if (_commands.at(ii) == "sumRange") {
				std::cout << "NumArray.sumRange(" << x << "," << y << ")" << " expects " << _expected.at(ii) << std::endl;
				int actual{na.sumRange(x,y)};
				std::cout << "\tActual: " << actual << std::endl;
				assert(_expected.at(ii) == actual);
				continue;
			}

			std::cout << "Unexpected command " << _commands.at(ii) << std::endl;
			assert(false);
		}

		std::cout << "Execution successful" << std::endl;
	}
};

int main() {

	const std::vector<Testcase> testcases{
		{
			{"NumArray", "sumRange", "update", "sumRange"},
			{{1, 3, 5}, {0, 2}, {1, 2}, {0, 2}},
			{0, 9, 0, 8},
		},
		{
			{"NumArray", "sumRange"},
			{{1,2,3,4,5,6,7,8,9}, {1,4}},
			{0, 14},
		},
		{
			{"NumArray","sumRange","update","update","update","update","sumRange"},
			{{5,18,13},{0,2},{1,-1},{2,3},{0,5},{0,-4},{0,2}},
			{0, 36, 0, 0, 0, 0, -2},
		},
	};

	for (const Testcase& tc : testcases) {
		tc.test();
	}
}
