#!/usr/bin/env python

# KNAPSACK Problem description (from wikipedia)
#
# In the following, we have n kinds of items, 1 through n. Each kind of item i 
# has a value vi and a weight wi. We usually assume that all values and weights 
# are nonnegative. To simplify the representation, we can also assume that the 
# items are listed in increasing order of weight. The maximum weight that we 
# can carry in the bag is W.
#
# The most common formulation of the problem is the 0-1 knapsack problem, which 
# restricts the number xi of copies of each kind of item to zero or one. 
# Mathematically the 0-1-knapsack problem can be formulated as:
# maximize SUM(vi * xi)[i= 1 to n]
# subject to SUM(wi * xi)[i = 1 to n] <= W, xi belongs to {0,1}
# 
# The bounded knapsack problem restricts the number xi of copies of each kind 
# of item to a maximum integer value ci. Mathematically the bounded knapsack 
# problem can be formulated as:
# maximize SUM(vi * xi)[i = 1 to n]
# subject to SUM(wi * xi)[i = 1 to n] <= W, xi belongs to {0, 1, ...., ci}
# 
# The unbounded knapsack problem (UKP) places no upper bound on the number of 
# copies of each kind of item.
# 
# Of particular interest is the special case of the problem with these 
# properties:
# * it is a decision problem,
# * it is a 0-1 problem,
# * for each kind of item, the weight equals the value: wi = vi.
# 
# Notice that in this special case, the problem is equivalent to this: given 
# a set of nonnegative integers, does any subset of it add up to exactly W? 
# Or, if negative weights are allowed and W is chosen to be zero, the problem 
# is: given a set of integers, does any nonempty subset add up to exactly 0? 
# This special case is called the subset sum problem. In the field of 
# cryptography, the term knapsack problem is often used to refer specifically 
# to the subset sum problem.
# 
# If multiple knapsacks are allowed, the problem is better thought of as the 
# bin packing problem.

def unittest(testfunc, inpTuple, solution):
    print "--Testing--"
    print inpTuple
    print "Expecting: " + str(solution)
    actualSol = testfunc(*inpTuple)
    if actualSol == solution

##
# Unbound knapsack problem first.
# Lets first describe the optimal substructure for this problem. From the 
# notation in the description; we can formulate the recursion as follows:
# UKP(W, vi, wi) = 0 if W <= wi for i = 0..n
# UKP(W, vi, wi) = max( UKP(W - wi, vi, wi), UKP(W, v[i-1], w[i-1]) )
# if UKP(Wi) is the maximum value of the knapsack with capacity Wi, then
# UKP(Wj) = 0 if Wj <= 0
# UKP(Wj) = max( UKP(Wj-1), (max( UKP(Wj- wi) + vi) for all wi <= Wj) )
def knapsackUnbound(W, weightSeq, valueSeq):
    pass

def utKnapsackUnbound
