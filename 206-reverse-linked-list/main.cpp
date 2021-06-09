#include <iostream>
#include <string>
#include <vector>

struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}

	ListNode(const std::vector<int>& vv) {
		if (vv.size() == 0) { return; }
		this->val = vv.at(0);
		this->next = new ListNode(std::vector<int>(vv.begin()+1,vv.end()));
	}
	
	std::string details() {
	
	        return std::to_string(this->val) + " -> " + (this->next == nullptr ? "null" : this->next->details());
	}
};

class Solution {
public:
	ListNode* reverseList(ListNode* head) {

		return iter(head, nullptr);
	}

private:
	ListNode* iter(ListNode* original, ListNode* reversed) {

		if (original == nullptr) { return reversed; }
		return iter(original->next, new ListNode(original->val, reversed));
	}
};

int main() {

	ListNode* head = new ListNode(std::vector<int>{1,2,3,4,5});
	std::cout << head->details() << std::endl;
	Solution soln;

	std::cout << soln.reverseList(head)->details() << std::endl;
}
