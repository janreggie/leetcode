#include <algorithm>
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
	std::vector<int> _preorder;

public:
	TreeNode* bstFromPreorder(const std::vector<int>& preorder)
	{
		_preorder = preorder;
		return call(1, _preorder.size(), _preorder.at(0));
	}

private:
	// Return a TreeNode* with root `root` and children from `_preorder[a:b]`.
	TreeNode* call(size_t a, size_t b, int root)
	{
		if (a > b) {
			return nullptr;
		}
		if (a == b) {
			return new TreeNode(root);
		}

		// We know that _preorder[ind] > root, so that's where we split.
		const size_t ind = std::distance(
		  _preorder.begin(),
		  std::lower_bound(_preorder.begin() + a, _preorder.begin() + b, root));
		TreeNode* result = new TreeNode(root);
		if (ind == b) {
			result->left = call(a + 1, b, _preorder.at(a));
			return result;
		}
		result->left = call(a + 1, ind, _preorder.at(a));
		result->right = call(ind + 1, b, _preorder.at(ind));
		return result;
	}
};
