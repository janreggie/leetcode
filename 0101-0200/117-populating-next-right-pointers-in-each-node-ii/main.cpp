#include <utility>
#include <vector>

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
	std::vector<std::vector<Node*>> _levels;

public:
	Node* connect(Node* root)
	{
		iterate(root, 0);
		for (const auto& lv : _levels) {
			for (size_t ii = 0; ii < lv.size() - 1; ++ii) {
				lv.at(ii)->next = lv.at(ii + 1);
			}
		}

		return root;
	}

private:
	void iterate(Node* root, size_t level)
	{
		if (root == nullptr) {
			return;
		}
		while (_levels.size() <= level) {
			_levels.push_back({});
		}
		_levels.at(level).push_back(root);
		iterate(root->left, level + 1);
		iterate(root->right, level + 1);
	}
};
