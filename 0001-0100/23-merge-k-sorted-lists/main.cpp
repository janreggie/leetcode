#include <initializer_list>
#include <iostream>
#include <string>
#include <vector>

struct ListNode
{
	int val;
	ListNode* next;
	ListNode()
	  : val(0)
	  , next(nullptr)
	{}
	ListNode(int x)
	  : val(x)
	  , next(nullptr)
	{}
	ListNode(int x, ListNode* next)
	  : val(x)
	  , next(next)
	{}
	ListNode(std::vector<int> l)
	{
		if (l.size() == 0) {
			next = nullptr;
			return;
		}
		val = *l.begin();

		if (l.size() == 1) {
			next = nullptr;
			return;
		}
		next = new ListNode(std::vector(l.begin() + 1, l.end()));
	}
};

std::string
sprint(ListNode* l)
{
	if (l == nullptr) {
		return "null";
	}

	return std::to_string(l->val) + " -> " + sprint(l->next);
}

class Solution
{
public:
	ListNode* mergeKLists(const std::vector<ListNode*>& lists)
	{
		const size_t k = lists.size();
		if (k == 0) {
			return nullptr;
		}
		if (k == 1) {
			return lists[0];
		}

		std::vector<ListNode*> nextLists((k + 1) / 2);
		for (size_t ii = 0; ii < k; ii += 2) {
			ListNode* l1 = lists[ii];
			ListNode* l2 = (ii + 1 < k) ? lists[ii + 1] : nullptr;
			nextLists[ii / 2] = mergeTwo(l1, l2);
		}

		return mergeKLists(nextLists);
	}

private:
	ListNode* mergeTwo(ListNode* l1, ListNode* l2)
	{
		if (l1 == nullptr) {
			return l2;
		}
		if (l2 == nullptr) {
			return l1;
		}

		const int v1 = l1->val, v2 = l2->val;
		if (v1 < v2) {
			l1->next = mergeTwo(l1->next, l2);
			return l1;
		} else {
			l2->next = mergeTwo(l1, l2->next);
			return l2;
		}
	}
};

bool
isEqual(ListNode* l1, ListNode* l2)
{
	if (l1 == nullptr) {
		return l2 == nullptr;
	}
	if (l2 == nullptr) {
		return l1 == nullptr;
	}

	return (l1->val == l2->val) && isEqual(l1->next, l2->next);
}

std::ostream&
operator<<(std::ostream& os, ListNode* lc)
{
	os << sprint(lc);
	return os;
}

struct Testcase
{
	const std::vector<std::vector<int>> _lists;
	const std::vector<int> _expected;
};

int
doStuff()
{
	const std::vector<Testcase> testcases{
		{ { {} }, {} },
		{ { {}, {} }, {} },
		{ { { 1, 2 }, { 2 } }, { 1, 2, 2 } },
		{ { {}, { 1, 2, 3, 4 } }, { 1, 2, 3, 4 } },
		{ { { 1, 3, 5, 7 }, { 2, 4, 6, 8 } }, { 1, 2, 3, 4, 5, 6, 7, 8 } },
		{ { { 1, 4, 5 }, { 1, 3, 4 }, { 2, 6 } }, { 1, 1, 2, 3, 4, 4, 5, 6 } }
	};

	for (const Testcase& tc : testcases) {
		std::vector<ListNode*> lists(tc._lists.size());
		for (size_t ii = 0; ii < lists.size(); ++ii) {
			const std::vector<int>& ll = tc._lists.at(ii);
			if (ll.size() == 0) {
				lists[ii] = nullptr;
			} else {
				lists[ii] = new ListNode(tc._lists[ii]);
			}
		}
		ListNode* expected = (tc._expected.size() == 0 ? nullptr : new ListNode(tc._expected));

		std::cout << "Merging the following:" << std::endl;
		for (size_t ii = 0; ii < lists.size(); ++ii) {
			std::cout << "\t" << sprint(lists[ii]) << std::endl;
		}
		std::cout << "okay, we're doing something" << std::endl;
		std::cout << "Expected: " << expected << std::endl;

		Solution soln;
		ListNode* actual = soln.mergeKLists(lists);
		std::cout << "Actual: " << actual << std::endl;
		if (!isEqual(expected, actual)) {
			return 1;
		}

		delete (expected);
		for (size_t ii = 0; ii < lists.size(); ++ii) {
			delete (lists[ii]);
		}
	}

	return 0;
}

int
main()
{
	doStuff();
}
