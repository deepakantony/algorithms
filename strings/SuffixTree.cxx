// read up on suffix trees from Algorithm Design by Steven K Skiena; the
// paper by Ukkonen for linear time construction.

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class SuffixTree
{
public:
	SuffixTree(); // Empty tree for you to add strings later
	SuffixTree(const string &inpStr);

	void addString(const String &inpStr);
	void updateSuffixTree(int index); // index points to the string in listOfStrings
private:
	vector<string> listOfStrings; // support more than one string
	
	// Our tree's nodes
	struct STNode {
		vector<Node*> childList;
		int left, right; // string indexes
		long long numDistinctSubstrings; // 
	};
	STNode *root;
};
