#include <iostream>
#include <vector>

struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
	ListNode(const std::vector<int>& v, size_t ind = 0) {
		if (ind == v.size()-1) { 
			val = v.at(ind);
			return;
		}
		val = v.at(ind);
		next = new ListNode(v, ind+1);
	}
};

class Solution {
public:
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {

		if (l1 == nullptr) { return copy(l2); }
		if (l2 == nullptr) { return copy(l1); }

		if (l1-> val < l2 -> val) {
			return new ListNode(l1->val, mergeTwoLists(l1->next, l2));
		}
		return new ListNode(l2->val, mergeTwoLists(l1, l2->next));

	}

private:
	ListNode* copy(ListNode* ll) {
		
		if (ll == nullptr) { return nullptr; }
		ListNode* result{new ListNode(ll->val)};
		ListNode* res{result};
		ll = ll->next;
		while (ll != nullptr) {
			res->next = new ListNode(ll->val);
			ll = ll->next;
			res = res->next;
		}
		return result;
	}
};

int main() {

	ListNode* l1 = nullptr;
	ListNode* l2 = new ListNode({1,3,4});
	Solution soln;
	ListNode* l3 = soln.mergeTwoLists(l1,l2);
	while (l3 != nullptr) { 
		std::cout << l3->val << std::endl;
		l3 = l3->next;
	}
}
