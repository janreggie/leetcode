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
};

class Solution
{
public:
	ListNode* removeNthFromEnd(ListNode* head, int n)
	{
		int length = 0;
		for (ListNode* it = head; it != nullptr; it = it->next) {
			++length;
		}

		int to_remove = length - n;
		if (to_remove == 0) {
			return head->next;
		}

		ListNode* it = head;
		for (int ii = 0; ii < to_remove - 1; ++ii) {
			it = it->next;
		}
		it->next = it->next->next;
		return head;
	}
};
