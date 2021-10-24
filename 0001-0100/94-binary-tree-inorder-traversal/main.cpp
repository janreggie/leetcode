#include <stack>
#include <utility>
#include <vector>

struct TreeNode
{
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode()
	  : val(0)
	  , left(nullptr)
	  , right(nullptr)
	{}
	TreeNode(int x)
	  : val(x)
	  , left(nullptr)
	  , right(nullptr)
	{}
	TreeNode(int x, TreeNode* left, TreeNode* right)
	  : val(x)
	  , left(left)
	  , right(right)
	{}
};

class Solution
{
public:
	std::vector<int> inorderTraversal(TreeNode* root)
	{
		std::stack<std::pair<TreeNode*, bool>> stack;
		std::vector<int> result;

		// Let's put the leftmost nodes in the stack
		for (TreeNode* it = root; it != nullptr; it = it->left) {
			stack.push({ it, false });
		}

		while (!stack.empty()) {
			const auto top = stack.top();
			stack.pop();

			// Check if we've already been through here
			if (top.second) {
				for (TreeNode* it = top.first->right; it != nullptr; it = it->left) {
					stack.push({ it, false });
				}
				continue;
			}

			result.push_back(top.first->val);
			stack.push({ top.first, true });
		}

		return result;
	}
};
