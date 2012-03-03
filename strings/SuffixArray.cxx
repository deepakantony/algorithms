#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

class SuffixArray
{
public:
	SuffixArray(); // default initialization for adding strings later
	SuffixArray(const string &inpStr); // init with a string

	void add(const string &inpStr);
private:
	void updateSuffixArray(const string &inpStr);

	struct SANode {
		int strIdx; // string index
		int leftIndex; // starting position of the suffix
		int lcp; // longest common prefix
		long long index; // when queried this will be the
	};

	set<SANode> suffixSet; // this eliminates duplicates
	set<SANode> suffixVec; // random access
	vector<string> stringList; // list of strings and suffixs
};
