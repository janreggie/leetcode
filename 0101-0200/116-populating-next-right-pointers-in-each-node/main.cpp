class Node
{
public:
	int val;
	Node* left;
	Node* right;
	Node* next;

	Node()
	  : val(0)
	  , left(nullptr)
	  , right(nullptr)
	  , next(nullptr)
	{}

	Node(int _val)
	  : val(_val)
	  , left(nullptr)
	  , right(nullptr)
	  , next(nullptr)
	{}

	Node(int _val, Node* _left, Node* _right, Node* _next)
	  : val(_val)
	  , left(_left)
	  , right(_right)
	  , next(_next)
	{}
};

class Solution
{
public:
	Node* connect(Node* root)
	{
		return connect(root, nullptr);
	}

private:
	Node* connect(Node* left, Node* right)
	{
		if (left == nullptr) {
			return left;
		}
		left->next = right;
		connect(left->left, left->right);
		if (right == nullptr) {
			return left;
		}
		connect(left->right, right->left);
		connect(right->left, right->right);
		return left;
	}
};
