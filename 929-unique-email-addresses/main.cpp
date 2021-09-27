#include <string>
#include <unordered_set>
#include <vector>

class Solution
{
public:
	int numUniqueEmails(const std::vector<std::string>& emails)
	{
		std::unordered_set<std::string> unique_emails;
		for (const std::string& email : emails) {
			unique_emails.insert(getLocalAndDomain(email));
		}

		return unique_emails.size();
	}

private:
	// Returns `local_name@domain_name`
	std::string getLocalAndDomain(const std::string& email)
	{
		std::string result;
		size_t ind = 0;

		// Iterate through local_name part
		for (; email.at(ind) != '@'; ++ind) {
			const char ch = email.at(ind);
			if (ch == '+') {
				break;
			}
			if (ch == '.') {
				continue;
			}
			result += ch;
		}

		// skip after '+'
		while (email.at(ind) != '@') {
			++ind;
		}

		// Now, add the rest of the email.
		for (; ind < email.length(); ++ind) {
			result += email.at(ind);
		}

		return result;
	}
};
