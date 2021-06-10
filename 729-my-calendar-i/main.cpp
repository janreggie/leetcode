#include <cassert>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <utility>

// Hey, this looks similar to the think-cell interview question!

class MyCalendar {

	std::map<int,bool> _timeslots;
	void add(int start, int end) {
		_timeslots[start] = true;
		_timeslots[end] = false;
	}

public:
	MyCalendar() : _timeslots{std::map<int,bool>()} { }

	bool book(int start, int end) {

		if (end <= start) { return false; }

		if (_timeslots.size() == 0) { 
			add(start, end);
			return true;
		}

		// [start,end) at the very last of _timeslots
		//
		auto it{--(_timeslots.end())};
		if (it->first <= start) {
			if (it->first == start) { _timeslots.erase(start); }
			else { _timeslots[start] = true; }
			_timeslots[end] = false;
			return true;
		}

		// [start,end) at the very start of _timeslots
		//
		it = _timeslots.begin();
		if (it->first >= end) {
			if (it->first == end) { _timeslots.erase(end); }
			else { _timeslots[end] = false; }
			_timeslots[start] = true;
			return true;
		}

		// Check if `start` and `end` are not in the middle of existing intervals
		//
		auto startIter{_timeslots.upper_bound(start)};
		auto endIter{_timeslots.lower_bound(end)};
		if (startIter->second == false || endIter->second == false) {
			return false;
		}

		// Check if startIter, endIter are one and the same.
		// If so, that means there is an "empty gap".
		//
		if (startIter != endIter) { return false; }

		--startIter; // for later

		if (startIter->first == start && endIter->first == end) {
			_timeslots.erase(start);
			_timeslots.erase(end);
			return true;
		} 
		if (startIter->first == start) {
			_timeslots.erase(start);
			_timeslots[end] = false;
			return true;
		}
		if (endIter->first == end) {
			_timeslots.erase(end);
			_timeslots[start] = true;
			return true;
		}
		add(start,end);
		return true;
	}

	void mapDetails() {
		for (const auto& ts : _timeslots) {
			std::cout << ts.first << ":" << ts.second << std::endl;
		}
	}

};

struct Testcase {
	const std::vector<std::pair<std::pair<int,int>, bool>> _points; // pair<params, expected>
	Testcase(const std::vector<std::pair<std::pair<int,int>, bool>>& pts) : _points{pts} {};

	static std::string viewPoint(const std::pair<int,int>& pt) {
		return "(" + std::to_string(pt.first) + "," + std::to_string(pt.second) + ")";
	}

	static std::string viewBool(bool bb) {
		return bb ? "true" : "false";
	}

	std::string details() const {

		std::string result;
		for (const auto& pt : _points) {
			result += viewPoint(pt.first) + ": " + viewBool(pt.second) + ", ";
		}
		return result;
	}

	void test() const {
		std::cout << "Testing " << this->details() << std::endl;
		MyCalendar cal;
		for (const auto& pt : _points) {

			bool actual{cal.book(pt.first.first, pt.first.second)};
			cal.mapDetails();
			std::cout << viewPoint(pt.first) << "->" << "Expected: " << viewBool(pt.second) << ", Actual: " << viewBool(actual) << std::endl;
			assert(pt.second==actual);
		}
	}
};

int main() {

	std::vector<Testcase> testCases{
		Testcase({{{10,20},true}, {{15,25},false}, {{20,30},true}})
	};
	for (const Testcase& tc : testCases) {
		tc.test();
	}
}

