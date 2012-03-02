# Longest Increasing subsequence

# Problem Definition: 
# Given a sequence , find the largest subset such that for every 
# i < j, ai < aj.
#

import sys


# 
# This problem requires us to use dynamic programming technique.
# 
# We should identify a sub structure similar to a DAG (directed acyclic graph)
# that we formulate into a recursive function.
# 
# Let S[0 to n] be the full sequence. If LIS(i) is the size of the longest 
# sequence that S[i] is the last element of, we have:
# 
# LIS(i) = 1 if i = 0 or S[j] > S[i] for all j < i
# LIS(i) = 1 + max(List(j)) for all j < i and S[j] < S[i]
# 
# This is O(n^2) algorithm
def longestIncreasingSubsequence(seq):
    if not seq: return (0, [])

    LIS = [1] # first element of the sequence 
    prev = [-1] # this is the end of any sequence construction involving this element
    maxLIS = 1
    maxIndex = 0
    for index in xrange(1, len(seq)):
        # Find the max and prev position
        maxVal = 0
        prevIndex = -1
        for j in xrange(index-1, -1, -1):
            if seq[j] < seq[index] and LIS[j] > maxVal:
                maxVal = LIS[j]
                prevIndex = j
        LIS.append(1+maxVal)
        prev.append(prevIndex)
        if (1+maxVal) > maxLIS:
            maxLIS = 1 + maxVal
            maxIndex = index
    
    if __debug__: print str(LIS) + "  " + str(maxLIS)
    if __debug__: print str(prev) + "  " + str(maxIndex)

    liSeq = [] # The sequence itself
    while prev[maxIndex] != -1:
        liSeq.append(seq[maxIndex])
        maxIndex = prev[maxIndex]
    liSeq.append(seq[maxIndex])
    liSeq.reverse()
    return (maxLIS, liSeq)

def unitTest(seq, sol):
    print "Testing: " + str(seq) + " - Expecting: " + str(sol)
    actualSol = longestIncreasingSubsequence(seq) 
    if actualSol == sol:
        print "OK"
    else:
        print "FAILED - Got: " + str(actualSol)

def main():
    unitTest([1,2,3,4,5,6,2,3,4,5,6,7,8,2,3,4,5,6,3,5,6,10], (9, [1,2,3,4,5,6,7,8,10]))
    unitTest([1,2,1,3], (3, [1,2,3]))
    unitTest([9,8,7,6,5,4,3,2,1,0], (1,[9]))
    unitTest([], (0,[]))

if __name__ == "__main__":
    main()

# This is a useless function i wrote; this was a mistake
def longestIncreasingConsecutiveSubsequence(seq):
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


