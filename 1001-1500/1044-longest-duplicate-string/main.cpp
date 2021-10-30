// Well, this does a TLE. But it shoould work!

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class Solution
{

public:
	std::string longestDupSubstring(const std::string& s)
	{
		if (s.size() <= 1) {
			return "";
		}
		if (s.size() == 2) {
			if (s.at(0) == s.at(1)) {
				return s.substr(0, 1);
			}
			return "";
		}

		return iter(s, 0, s.size());
	}

private:
	// Find the answer that is of length [l1, l2).
	std::string iter(const std::string& s, size_t l1, size_t l2)
	{
		const size_t len = (l1 + l2) / 2;
		if (len == 0) {
			return "";
		}

		std::unordered_map<long long, size_t> hashes; // hashes[<hash>] = ind <-> <hash> is the hash of s[ind:ind+len]
		std::pair<bool, size_t> found = { false, 0 }; // { has answer been found, starting index of the answer }
		long long prev_hash = computeHash(s, len);
		hashes.insert({ prev_hash, 0 });

		for (size_t ii = len; ii < s.size(); ++ii) {
			const long long next_hash = computeHash(s, len, prev_hash, ii);
			if (hashes.count(next_hash) != 0) {
				const size_t ind1 = hashes.at(next_hash), ind2 = ii - len + 1;
				bool is_ok = true;

				for (size_t jj = 0; jj < len && is_ok; ++jj) {
					if (s.at(ind1 + jj) != s.at(ind2 + jj)) {
						is_ok = false;
					}
				}
				if (is_ok) {
					found = { true, ind1 };
					break;
				}
			}

			hashes.insert({ next_hash, ii - len + 1 });
			prev_hash = next_hash;
		}

		if (l1 == l2 - 1) {
			return found.first ? s.substr(found.second, len) : "";
		}

		if (found.first) {
			std::string try_longer = iter(s, len, l2);
			return (try_longer != "") ? try_longer : s.substr(found.second, len);
		}

		return iter(s, l1, len);
	}

	// Take the hash of the first len characters
	long long computeHash(const std::string& s, size_t len = SIZE_MAX)
	{
		long long hash = 0;
		long long p_pow = 1;
		len = std::min(len, s.size());
		for (size_t ii = 0; ii < len; ++ii) {
			const char c = s.at(ii);
			hash = (hash + (c - 'a' + 1) * p_pow) % _m;
			p_pow = (p_pow * _p) % _m;
		}
		return hash;
	}

	// prev_hash == computeHash(s[to_add-len:to_add]).
	// This will compute computeHash(s[to_add-len+1:to_add+1]) by adding s[to_add] into prev_hash.
	long long computeHash(const std::string& s, size_t len, long long prev_hash, size_t to_add)
	{
		prev_hash = (prev_hash - (s.at(to_add - len) - 'a' + 1)) % _m;
		prev_hash = (prev_hash * _p_inv) % _m;
		long long next_term = (s.at(to_add) - 'a' + 1);
		for (size_t ii = 0; ii < len - 1; ++ii) {
			next_term = (next_term * _p) % _m;
		}
		return (prev_hash + next_term) % _m;
	}

	static constexpr int _p = 31;
	static constexpr int _m = 1e9 + 9;
	static constexpr int _p_inv = 838709685;
};

int
main()
{
	const std::string s =
	  // "banana";
	  // "peftxylsseopntszwuwrugksyrizvatuwgiarugnmypheecnproenzyksusehuujvnpqwwqnuhdogeqnfnhdbhatcuaaniteuwhsmpmrzfxekstssaynzzvmqwdhwtnizwiejjkfovscneouvjsljzfkmtrhunaxgcaswfajczlnhacsajozjwpoqjtdcaqsubbntxlpayebjfbzjiaoiyjbmzktcnscxyhpdkfexnjfrngjesbtwnmasnwvauzlzkompxkgifxsavzfhwvdjausccrjfpnzordyfgjdyawqzbfbizqvecrbhupkdudvxdknkqwjynyrutzhcnmfabwwaerdirsnufhlktojnyrefumfhvkolrybjpadpowjoqhhbzqpmpcmrddtrplgezihshtvpnqxikgsiiqnmezybjzktpdzsmribdkvlfbvicrgnblqnaylcijqbxjcnmjdrsfpcdojwcanvkgfaappivqnocobyeavoifqgnroagelmfjprxkupbdrwnycnhffgchclumhpxnlbbbmfsjmqoxuwkzwwksraxhlvdvrnjmfqzdksnxyhbaquxidvlgpjhlskrvkbsizyfedhwqsrzlwkesslvduwksoreufeflbgodatiblhmmfeiwbtohurgprremycvkhecakofsmpiimdcecpcvuseiqkxifzktkfnaqnpshcfdrhgjalpwaqumixmrxwduhgxwtfxarwyfshsutxihpecwbgzghkfaukdfbyecpryqxooyjsurjstfwrpegyxtdbkoicorqe";
	  //   "zxcvdqkfawuytt";
	  "djpqwlrroqeuwwqgxnvdftzgsgnmpnhnhezixyhlydjjekpeczwtguowubfjsyohxaihmbjzfchmbnppouguvklmiaqkgomqzvvfubklwexbnzbdkvtxjnpzmfdgomvvsekluemjqaatkbhklusgxbezjghoddwcmirwrnnsgzjzwrnfyqgjylzgwhwipinohhzkywikevsqurnirnmmkgwpgvdswttwpingslbzxzsodqvlluqetfzfzbdhilaugrxewhomtwzjyldxzwtxmufbcrxtqfpcqscbbstplqczhumhedcmmgfkhdyetexcyrlvdrkgxzsncrpoomtqwnwozbteedjozikggwkbexbibruqdpekpjpzzymxpvtsderhjwxvyfahximykcndxskcjwewnfcbvymijwkrisjtzyiegysxpyfdrblxjquytzgvajmdvylemhqcctivjzmkdojbpvucgswycfnjkyoqvzlufphsrvhcbkxamqmaoveycykirpboguhrimemgkkbdmkyvalkpmktlkhwtaafuphdksucgianjkyztzyrndfjhkemdlgnmbucmqqyvjmzqlmgerhvzdtbjsagisjsqnrzqlmimtxumlngktcptgpcevpybghuycisxbemgpwptokdqvzp";
	//   "uirqkccmgnpbqwfkmplmfovxkjtgxbhwzqdlydunpuzxgvodnaanxpdiuhbitfllitaufvcmtneqmvibimvxmzvysignmsfykppdktpfhhcayfcwcrtjsgnyvzytevlqfabpjwxvjtfksztmdtrzgagdjtpeozzxppnkdbjayfbxqrqaefkcdbuvteobztucgdbcmlgnxldcwtzkvhwqxbsqlbsrbvesemhnbswssqvbiketdewfauvtzmyzrrqslzagjcyuznkpkgpkkinldxcjtuoumcbcttabfuzjbtoqjqbpnsemojbtctvdmobnuutcsfmhkrbwkmpdcdncqizgtlqekvqophqxewkpxpkrgjivrtarxtwbbfhfikbrdwohppyiyyztopksdmxvqiaafswyjfnlwntldwniypzaxrscyqfrlqehqgzaxxazfwtwjajsrmwuerdqklhwoqxptcvqoqbjwfqrewirtcbskmkaqgtcnxnsqmwgwjxruhyyjtbuivvepnxiwjmtlrvexjzevctflajibxkvmbzdfwoqobmhstgpshtxitwttpkdvfmfwtwsazfgzwbtmqrowrcesyyeuwunodesrzbmjbxnchaqptfgqlknuarhgnsbwnucdhckpbwhtwhejivrmuccbwnyenyvonquscneswngwbkjysxvdwbzymwxcrnexrxhmuwvycmsiazmqavgmyurbcmvdjplloidbzacunerwobvaxsromiiwzqxnrsjpyoacfxcmmogmokhpmhxzkdzmpjcrgaeihdhczrmxmfurjatuwxriiwtfojwvkkybcdmwayhnzrnqrynwtrvmtgtrxndlbtlhyzfjtbtvqujjuwpibuonuwjdfvnhdqqzlmwwheztjkrrzrroogovapywxkjsccjnseanhxijybintgbjwlkmdzuoeclfqatffgjvcbujovunnauprhoocxzghzvsmuyhsl";
	Solution soln;
	std::cout << soln.longestDupSubstring(s) << std::endl;
}
