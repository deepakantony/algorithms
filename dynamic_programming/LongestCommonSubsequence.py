#!/usr/bin/env python

# Problem description:
# Given 2 sequences (although this could be N sequences), find the longest
# subsequence common to bo the input sequences.
# A subsequence is not necessarily continuos.
#



def memoizeLCS(seq1, seq2, i, j, LCS):
    if i <= 0 or j <= 0: return 0
    i1 = i-1
    j1 = j-1
    if LCS[i1][j1] != -1:
        return LCS[i1][j1]
    if seq1[i1] == seq2[j1]:
        LCS[i1][j1] = 1 + memoizeLCS(seq1, seq2, i1, j1, LCS)
        return LCS[i1][j1]
    
    LCS[i1][j1] = max( memoizeLCS(seq1, seq2, i1, j, LCS),
                       memoizeLCS(seq1, seq2, i, j1, LCS) )
    return LCS[i1][j1]

def reconstructLCS(seq1, seq2, LCS):
    seq = []
    seq1Index = 0
    seq1Len = len(seq1)
    seq2Index = 0
    seq2Len = len(seq2)
    while seq1Index < seq1Len and seq2Index < seq2Len:
        if seq1[seq1Index] == seq2[seq2Index]:
            seq.append(seq1[seq1Index])
            seq1Index += 1
            seq2Index += 1
        elif (seq1Index + 1) < seq1Len and (seq2Index + 1) < seq2Len and \
                LCS[seq1Index+1][seq2Index] >= LCS[seq1Index][seq2Index+1]:
            seq1Index += 1
        else: seq2Index += 1

    return "".join(seq) if type(seq1) is str else seq

# Lets first identify the optimal substructure for this problem.
# Let X and Y be two sequences. Let, Xi be a subsequence of X such that 
# Xi = X[0..i-1] with size i. So if 'n' is the length of seq X and 'm' is the 
# length of seq Y, then we're finding LCS(Xn, Yn).
# So,
# LCS(Xi, Yj) = 0 if i == 0 or j == 0
# LCS(Xi, Yj) = 1 + LCS(Xi-1, Yj-1) if X[i-1] == Y[j-1] assuming indices start at 0
# LCS(Xi, Yj) = max(LCS(Xi-1, Yj), LCS(Xi, Yj-1)) if X[i-1] != Y[j-1]
def longestCommonSubsequence(seq1, seq2):
    if not seq1 or not seq2: return None
    LCS = []
    for i in xrange(len(seq1)):
        LCS.append([])
        for j in xrange(len(seq2)):
            LCS[i].append(-1)
    print memoizeLCS(seq1, seq2, len(seq1), len(seq2), LCS)
    commonSeq = reconstructLCS(seq1, seq2, LCS)
    return (len(commonSeq), commonSeq)

def unittest(seq1, seq2, sol):
    actualSol = longestCommonSubsequence(seq1, seq2)

    print 
    print "--Testing--"
    print "Seq1: " + str(seq1)
    print "Seq2: " + str(seq2)
    print "Expecting: " + str(sol)
    if actualSol == sol:
        print "OK"
    else:
        print "FAILED - Actual Output: " + str(actualSol)


def main():
    unittest('kannada', 'canada', (5,'anada'))
    unittest('empty bottle', 'nematode knowledge', (7,'emt ole'))
    unittest([1,2,3], [1,3,2,4], (2,[1,3]))
    unittest([1,2,3], [4,5,6,7,8,9,10], (0,[]))
    unittest('', '', None)
    unittest('', 'abcd', None)
    unittest('efgh', '', None)

if __name__ == "__main__":
    main()
