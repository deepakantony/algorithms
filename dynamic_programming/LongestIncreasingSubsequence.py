# Longest Increasing subsequence

# Problem Definition: 
# Given a sequence , find the largest subset such that for every 
# i < j, ai < aj.
#

import sys

def longestIncreasingSubsequence(seq):
    assert seq

    seqLen = len(seq)
    # first element is the longest in the beginning
    (longestIndex, longestLength) = (0, 1)
    # position of the current elements' increasing sequence
    memoiz = (longestIndex, longestLength)
    for index in xrange(1, seqLen):
        # if current element keeps the current sequence increasing
        if seq[index] > seq[index-1]:
            memoiz = (memoiz[0], memoiz[1] + 1)
            if memoiz[1] > longestLength:
                (longestIndex, longestLength) = memoiz
        else:
            memoiz = (index, 1)

    return seq[longestIndex:(longestIndex+longestLength)]

def unitTest(seq, sol):
    print "Testing: " + str(seq)
    if longestIncreasingSubsequence(seq) == sol:
        print "OK"
    else:
        print "FAILED"

def main():
    unitTest([1,2,3,4,5,6,2,3,4,5,6,7,8,2,3,4,5,6,3,5,6,10], [2,3,4,5,6,7,8])
    unitTest([9,8,7,6,5,4,3,2,1,0], [9])
    unitTest([], [])

if __name__ == "__main__":
    main()

