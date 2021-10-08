#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Trie
{
	bool _exists; // Check if the empty word exists.
	std::vector<std::shared_ptr<Trie>> _children;

public:
	Trie()
	  : _exists{ false }
	  , _children{ std::vector<std::shared_ptr<Trie>>(26) }
	{
	}

	void insert(const std::string& word)
	{
		insert(word.begin(), word.end());
	}

	bool search(const std::string& word) const
	{
		return search(word.begin(), word.end());
	}

	bool startsWith(const std::string& prefix) const
	{
		return startsWith(prefix.begin(), prefix.end());
	}

private:
	void insert(const std::string::const_iterator begin, const std::string::const_iterator end)
	{
		if (begin == end) {
			_exists = true;
			return;
		}

		const size_t ind = getInd(begin);
		if (!_children[ind]) {
			_children[ind] = std::shared_ptr<Trie>(new Trie());
		}
		_children[ind]->insert(begin + 1, end);
	}

	bool search(const std::string::const_iterator begin, const std::string::const_iterator end) const
	{
		if (begin == end) {
			return _exists;
		}

		size_t ind = getInd(begin);
		if (!_children[ind]) {
			return false;
		}
		return _children[ind]->search(begin + 1, end);
	}
	bool startsWith(const std::string::const_iterator begin, const std::string::const_iterator end) const
	{
		if (begin == end) {
			return true;
		}
		size_t ind = getInd(begin);
		if (!_children[ind]) {
			return false;
		}
		return _children[ind]->startsWith(begin + 1, end);
	}

	static size_t getInd(const std::string::const_iterator it)
	{
		return *it - 'a';
	}
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */

int
main()
{
	Trie* obj = new Trie();
	obj->insert("apple");
	std::cout << obj->search("apple") << std::endl;
	std::cout << obj->startsWith("app") << std::endl;

	delete (obj);
}