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
	void updateVector();
	string substring(long long idx);
	void print() const;
private:
	void updateSuffixArray(const string &inpStr);

	struct SANode 
	{
		SANode() 
			: leftIndex(-1), strIdx(-1), lcp(0), index(0){}
		SANode(vector<string> *sl) 
			: leftIndex(-1), strIdx(-1), lcp(0), index(0) {}
		int strIdx; // string index
		int leftIndex; // starting position of the suffix
		int lcp; // longest common prefix
		long long index; // when queried this will be used to do the binary search
	};

	int findLCP(const SANode &prev, const SANode &cur) const;
	bool nodeHasStringIndex(const SANode &node, long long idx) const;
	bool nodeIsLTIndex(const SANode &node, long long idx) const;
	string constructStringInNode(const SANode &node, int prefixIndex) const;

	struct NodeCmp
	{
		NodeCmp(vector<string> &sl) : stringList(sl) {}
		bool operator() (const SANode &ths, const SANode &other) const; // this will be used by set for sorting	
		vector<string> &stringList;
	} nc;
	void printNode(const SANode &node) const;

	set<SANode,NodeCmp> suffixSet; // this eliminates duplicates
	vector<SANode> suffixVec; // random access
	long long substringsMaxIndex; // number of distinct substrings - 1
	vector<string> stringList; // list of strings and suffixs
};

SuffixArray::SuffixArray()
	: nc(stringList), suffixSet(nc)
{
}

SuffixArray::SuffixArray(const string &inpStr)
	: nc(stringList), suffixSet(nc)
{
	updateSuffixArray(inpStr);
}

void SuffixArray::add(const string &inpStr)
{
	updateSuffixArray(inpStr);
}

void SuffixArray::updateVector()
{
	suffixVec.clear();
	if(suffixSet.empty())
		return;

	// add it to the vector
	suffixVec.push_back(*suffixSet.begin());
	auto it = suffixSet.begin();
	SANode prev = *it;
	SANode cur;
	++it;
	while(it != suffixSet.end())
	{
		cur = *it;
		cur.lcp = findLCP(prev, cur);
		cur.index = 0ll + prev.index + stringList[prev.strIdx].size() - 
			(prev.lcp + prev.leftIndex);
		suffixVec.push_back(cur);

		prev = cur;
		++it;
	}
	substringsMaxIndex = 0ll + prev.index + stringList[prev.strIdx].size() - 
			(prev.lcp + prev.leftIndex) - 1ll;
}

string SuffixArray::substring(long long idx)
{
	if(idx < 0 || idx > substringsMaxIndex)
		return string("INVALID");

	string res;
	// binary search the suffixVec for the substring[idx]
	long long left = 0;
	long long right = suffixVec.size();
	long long middle = left + (right - left)/2;
	while(left < right)
	{
		if(nodeHasStringIndex(suffixVec[middle], idx))
		{
			int prefixIndex = idx - suffixVec[middle].index + 
				suffixVec[middle].leftIndex + suffixVec[middle].lcp + 1;
			//cout << prefixIndex << endl;
			res = constructStringInNode(suffixVec[middle], prefixIndex);
			break;
		}
		else if (nodeIsLTIndex(suffixVec[middle], idx))
		{
			left = middle + 1;
		}
		else 
		{
			right = middle;
		}
		middle = left + (right - left)/2;
	}
	return res.size() > 0 ? res : string("INVALID");
}

void SuffixArray::print() const
{
	for(auto it = suffixVec.begin(); it != suffixVec.end(); ++it)
		printNode(*it);
}

void SuffixArray::updateSuffixArray(const string &inpStr)
{
	int curIndex = stringList.size();
	stringList.push_back(inpStr);
	for(int leftIndex = 0; leftIndex < inpStr.size(); ++leftIndex)
	{
		SANode newNode(&stringList);
		newNode.strIdx = curIndex;
		newNode.leftIndex = leftIndex;
		suffixSet.insert(newNode);
	}
}

int SuffixArray::findLCP(const SANode &prev, const SANode &cur) const
{
	int LCP = 0;
	for(auto it_this = stringList[prev.strIdx].begin()+prev.leftIndex,
			it_other = stringList[cur.strIdx].begin()+cur.leftIndex;
		it_this != stringList[prev.strIdx].end() || 
			it_other != stringList[cur.strIdx].end(); 
		++it_this, ++it_other)
	{
		if(*it_this == *it_other)
			++LCP;
		else
			break;
	}

	return LCP;
}

bool SuffixArray::nodeHasStringIndex(const SANode &node, long long idx) const
{
	if (node.index <= idx && 
		(node.index + stringList[node.strIdx].size() 
		 - node.leftIndex - node.lcp) > idx)
		return true;
	// else
	return false;
		
}

bool SuffixArray::nodeIsLTIndex(const SANode &node, long long idx) const
{
	return node.index < idx;
}

string SuffixArray::constructStringInNode(const SANode &node, int prefixIndex) const
{
	string res;
	for(auto it = stringList[node.strIdx].begin() + node.leftIndex;
		it != stringList[node.strIdx].begin() + prefixIndex; ++it)
		res += *it;

	return res;
}

bool SuffixArray::NodeCmp::operator()(const SANode &ths, const SANode &other) const
{
	for(auto it_this = stringList[ths.strIdx].begin()+ths.leftIndex,
			it_other = stringList[other.strIdx].begin()+other.leftIndex;
		it_this != stringList[ths.strIdx].end() && 
			it_other != stringList[other.strIdx].end(); 
		++it_this, ++it_other)
	{
		if(*it_this > *it_other)
		{
			return false;
		}
		else if(*it_this < *it_other)
		{
			return true;
		}
	}

	return (stringList[ths.strIdx].size() - ths.leftIndex < 
			stringList[other.strIdx].size() - other.leftIndex) ? true : false;

}

void SuffixArray::printNode(const SANode &node) const
{
	string res;
	for(auto it = stringList[node.strIdx].begin() + node.leftIndex;
		it != stringList[node.strIdx].end(); ++it)
	{
		res += *it;
	}
	cout << "(" << res << ", index:" << node.index << ", lcp: " << node.lcp << ")" 
		 << endl;
}

void unitTests()
{
	SuffixArray sa("abracadabra");
	sa.updateVector();
	sa.print();
	sa.add("abra");
	cout << endl;
	sa.updateVector();
	sa.print();
	cout << endl;
	sa.add("cadavarzebra");
	sa.updateVector();
	sa.print();

	cout << sa.substring(0) << endl;
	cout << sa.substring(109) << endl;
	cout << sa.substring(110) << endl;
	cout << sa.substring(111) << endl;
	cout << sa.substring(112) << endl;
	cout << sa.substring(113) << endl;
	cout << sa.substring(114) << endl;
	cout << sa.substring(1) << endl;
	cout << sa.substring(3) << endl;
	cout << sa.substring(4) << endl;
	cout << sa.substring(11) << endl;
}

int main(int argc, char *argv[])
{
	unitTests();
	return 0;
}
