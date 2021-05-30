#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
	int maxProduct(const vector<string>& unorderedWords) {

		// Sort all words to make things easier for me
		//
		vector<string> words(unorderedWords);
		for (size_t ii{0}; ii < words.size(); ++ii) {
			if (words[ii].size() > 1) {
				sort(words[ii].begin(), words[ii].end());
			}
		}
		sort(words.begin(), words.end());

		if (words.size() == 2) {
			return product(words[0], words[1]);
		}

		if (words[0][0] == words[words.size()-1][0]) { // That is, there is a common letter across all!!
			return 0;
		}

		// What is ii such that words[0][0] == words[1][0] == ... == words[ii-1][0] != words[ii][0]?
		// That value will be the value of pivot
		//
		size_t pivot{0};
		for (; pivot < words.size(); ++pivot) {
			if (words[pivot][0] != words[0][0]) { break; }
		}

		int bestProduct{0};
		for (size_t ii{0}; ii<words.size(); ++ii) { // <words.size() because it's possible for ii,jj to be above pivot!
			for (size_t jj{pivot}; jj<words.size(); ++jj) {
				bestProduct = max(bestProduct, product(words[ii],words[jj]));
			}
		}

		return bestProduct;
	}

	int product(const string& word1, const string& word2) {
		size_t i1{0}, i2{0};
		while (i1 < word1.size() && i2 < word2.size()) {
			if (word1[i1] == word2[i2]) { return 0; }
			if (word1[i1] < word2[i2]) { ++i1; }
			else { ++i2; }
		}
		return word1.size() * word2.size();
	}
};

int main() {
	vector<string> words{"sxqkhiiuayvrxflkvvlgxlfsf","zczajmnelp","vauqbvnjhlmtrkyfrqktnrqvcuhnesneqmrwljmcdejyiaagjoklcsgzmvaothfuqhzlk","ujiimrsqsnjhmpii","gnuvmhznwixqrbzrxqlbwfuvvexecpikzcnvvabavp","hcljqoxdmzhvcgbqcrgbcylo","xawkqqymgcswlyhbqoameboyivpxwisrmjnrjjqzuezzhbzjawipcvcodih","giftnnqfgpklhlp","qavjvzepsygoifwjpillwgmatkkhmzkpfilxljzyqlwwzclggbdujawihdelrylweptnvwmcahi","tzlmfooxbilugikrvyiugccvpthtxtelwqloyneqdoaxksxcfvvemisabidcyinpfheiwcsxqzbrkags","rjnvquhxutbclnqqcoucqqryfdybvrsnpjlsnzqsrvrja","rnyoybuctijzdwyhgzwlmnccwumgxwimdlthkmddltpaxwuncr","rjjkznrfmdctxgqysgbthrbantjelzkwrjsahvus","hrsnwajufffxfvbmtndskjiqbhtmtpfimenvrdfrsykeaukknzydlkthxpqjzfjarenb","myipzzldzbxsgemcvpyhskfi","rfibilsvzmclyhuoezlbatmcdvohgmomvdgkyxzuvyrefajdza","dawdblinnjjfnlxeiwlxwopoanfwtyauyjfgpzmmrrnmhivwuzcrxotjvksqupcznz","zsraljbiepjlqyiwltxdvtyrocpuabjoaixwnwdyn","ucxdojnhbabbrwuzrzwgzmuubsbrqgbujogqmjvtsvxcxhlxdkjpehqvljskqxhsycpbxqzxiprhhjfoavvyamyqdpasaf","nscbfjdlshrtibcywfxjuxrwdrrpazldqvcngwcdwnzjojkjqaeywypfrvqeisjsjiyznhsqtjufuatudkqys","ffxkoedkmvgrjhfwgbpczwdwpesxgaeskmrmgdwsawhrj","vsprvmwklgtrqlbsgyjztwxiipgvdsbtsrhvvelqio","xlqdbymkvncgwxslppmayogfqpyfnglfblymeeyyqllcrnyrfyhjaszvkssibertsiasv","gtaydspmeeaovyoabgoqzpbyfzmwujkxxbaelqjjjlzmwuadrngtptlmictvz","kmxsgeshkinpvrcdoyqgcapdfrpuodavibwzosmpghnaezzznfnonvzxjunsnrtzqxzqpwlebtpdy","bswnpczojgjndhxzjengeyurfwgzademwwrzpwlspmthqkqnkeadcsvzwiieyctbcmwcwmxjhnbtpscaevxrgteuiupmkzsu","aoobmvfptvchbcsbvstvggwreqsfdgfofaktoklm","dpxuftgsghzxbzqwqfmsidtwudzdtjofcmizbgteawvzsmasnxxcugrajhhxglidwcikyxdmiplmwifnebuxucldyncmzgeky","ykvmtvtiuucjyvvcatpqvwjkegdbwvb","ijqurdyqvgzpkpijyjsgqrtqmiyftmvudodfmmxkaycazonmorbybm","uagbnnmmjfojfphkljvywulenajwuafmxhquutofadqnzaeknhwsit","xfphxillvroytxkszmabdzvakaqqzkw","vuobjvyydvywlbumgufphrqgmpayzypfnswwvanpewhezkcgfudvcqhkolocbxarvjtqpjgwnvbsrybcbhxhagojdxsxuplztf","tjazvlwpjnflycoklhjvhaqbtjvoibirxczvfajivonkxwbhxnflwg","pyajrhncpolqlokwsmsjmgirjzggrarwtqdtguroupombdzsxdqmjnhvhssjjfbn","bamvimh","krsaebjaoixguzteopzqyvtkwxdccmahnmzqgcdseiwaolyltrwqviprdxvbgsejgudegxlssbhlhbjnuww","llofualuohhinsgkojkqqniigtesiopojaalxfkwlxbpwiyzfydfkfamubaxpplvyvmoyk","ltzgjmmcf","srxfggdhxymcqvvnxndyfkklkcjnbhseachbatmwzapzrkksmpbjxdjmacctlcyuxabaxhtwdbncicocvtdpuhzyphxosb","gsqiofgomfkgvaeryvqqmpdmucvnccapxfqvtrizvdkcffv","rymbsvvcmebkihbsnosrvavjyeuewnmgmroybdwfwrfdmrgckyghcwiwgicbsolslmvecqbukdoms","oxckfkdrifnqwodukzzyiftt","wcnbecykxpyitgvtcgntillbdtaxgocgbnebpgbyoqzentj","ustckfejpowjdkvsvnutczdapnbbbjeexctarsdclpgtzignbdcjdbqcerwuooiuoyjjxgocwgpfzgbkiarjuuv","ipoizlbyfffodywwwgskqzyraphcsumlfulrwcqewlbedbzsuclpdnpqepdvjlllcxzeepocbavt","bxcwrvcjqfklsfhhsjmloretanhykreazhdxcugvcsfdzf","wnt","bwazagvbaiukqqqlwniaksorzrddoqdazcdunfsfvgxkaeqylznizuguhbhmevbchiy","bcxzqzcalbjlywodteyfncvpau","pdjlrbxfjypnlfncgvqyinugxiooispizbfvugmgjtguarumhktua","sokkifdlyncljcewmglhtdnmjnylzrvutgjgxevywaejbtqxzcioiocnedokvntsxapuenwmlzupzzsyx","tyicsdnrcplplaebpmscsftfceqgcwonwbhafdcblkutxksdawpfdepzblqvyxagzlcafqurnwfmlxzktgsibufljsqavjj","iqogyjpczksrxhzobkuwsmchgsqijzlwxqfqkvuhgg","ulwfsupevsgojjpvfuujflncyfiyyolnepfv","glridgrcgagbpnlbexoukbchznynvnjvhlimjdzddtnibovgzjwjeahkxuzdfjhxffgfoszyyfp","pyrbuljvjohaeqieronxnxvmowpziqtykxdchcsreftezkcsjpatqyswiok","bigfukspxqfgfuvknipnfduaqqyjaqamlzngjbivvofelbnuojtcjedevofviehstxuiifzfekd","tyntpnrihalkfdsnfxmuloumcfzjdo","etigwnmkuxiaxmhqua","rt","grfwewjfubxeisnvaiuutyhpkmqncytixlrh","zmjuymrbvovwfgwoiimephttlkflccjnkogmgatgppzqfgxxsuvdmghguhhiknnrvefqiipuarrhdxk","ugflyaslfhwuwbkmstuonyxktjubaqensqgaxtniqcdtgxgpbzxqqqzyvzuowwfsqiceekymmmumlfmzpmcceqc","wtbalucihyorwkvjrqizubjhgikwthdpdyuiglkttqucifbxbsfp","opbweokknnuv","rkxqwquwycjqvhkcfpkqdqfujkwrb","seijqsveszvdjpgwarxfcqkwhwhfaurzzzosvhxsvvlqlo","pmdzcvpameoepdeomzyxlbkaheomnudwbmozxcvcqfgcnjvkquwfucszpphlbngmqkgrybnzzwwwevowikilxrrii","qsmfrakyrvldpzonvogi","xwfihwvzprzbztkhcsvzwyusjyqtqqnzzxnqpftvujkyzsdthgpzltnhcodqnfbkhplojczwqvobmjzlwyxxogougtlndhme","dbjwxqlcdzaiwxndfkvbtntcgwiwudjjopajiyipitohrqdadhaudxtlkollqvzoshlpifrdkytogqjw","pytlutiapvghxzktonmunlnoqbrrklplirlbfvkrtxzbasckyyxsgzyadheavypxjvrwqenizzlsgwitoobddvulrha","cyykgckvwbzorzchsmzgtqaagluwblzcgycaxgsumudssmqhociqkeqleujyp","lcvjozucjmmjqihrbusskzez","pmnnsfpjhcpwkmcdbfvlxngcdmejcvxpktilhywpitxwsfavpmlmdczpyilnhakjkoscgyxllac","jiocwirozxpgk","ugprsabrwwmwlgpxketitrwcgktesghvammurujnsqodrackrthuyutymauscryziqdyyaqjjfmcdbj","wvfpfdbl","prggezcatvhanccrfdyzxzfcvzvvgcdpglcntiqdtrcosjvajxhwncm","yqbedsksmxxtelcjfuyohloymrdsvia","ievqdpmwpkeevgmpvlpbaeozgvzbflyjugdaxztlqht","gfosazzzncynyysgufpmpuiktsgbmhceyctadfhgzfhthwhummhwfpqzhqxyfphxtnaglmj","kqqkgscpssfwfzsmvgbzuucdeutybxnzchlcyuydquqrofdunijcezsfnhbgzzlkkdlxtztigzqxy","faqhsolsbjwyfuxetianfzduzhqnwzibmrsibukqzruiawqbliadielaubaf","xnpxlljkckhmuhdrecohitevqkkoerrrfxlygexekncfijypxbymldxxuzjtayyh","pknyfbudwfiouloupvijk","mafeuahkglqfytcfayillcjfvzporwdlpjwa","zpkfptxznenfbpxewwmnummedcsrqfc","vlowqsasgylppeolvzsnvheqsnlgfoqiomqgpydipljxlmfyohfmccndykquhczdacazugspuhppjxfrxm","sfwqycwbmmqxggteptaudtbznhqlrukomneotqoiglmbrlzezwrvkppgqessaenxmvigkwtbbnlzdnzmpfusywqz","vofgbgxkjbziaztamgenynymgtvwcaoueonyxsvszwkrhzvwiatlhdokivvsonuuejhuhrsqhxuvfa","muznkocycftgkjaojcqufejsxtlakiswirgyhjkmvwnpegtosopnkmucpdvtyazavdkuaimwdakxu","krtcfqtpmjdajrenjnolxattgtlrpfwpfnftzosckngkcnflqavfwfporfmwyqnttyxsrtiugteuvnbdrb","aqrhfmfxicrtaygstqhpmkdmropntnfcbfudwubfxuvoykhnfrdhxpk","zeadvimmwmbmfryptyaokgjenutemnwmraeigpmmtipsqjgunhjfumqczwdarqc","ffnidxpdbadyfzveeiaihmmrbwepobecszueaz","jhsdwztvasqkxztvtkhtndccbhtuhrlggreipudmhzioeavtkbvtdwbufnqkhizvqsyus","asfecibvscmsbxhblmzzgz","gxgazzyvobtzsixckticde"};
	Solution soln;
	cout << soln.maxProduct(words) << endl;
}
