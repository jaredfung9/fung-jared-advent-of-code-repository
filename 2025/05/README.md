# ADVENT OF CODE 2025 DAY 05
# PART 1
## Preliminary Thoughts
INPUT: List of ranges <newline> Item IDs  
PROCESSING: Can easily split into two files; ranges and queries  
## Algorithm Basics
1. Process Input - split into two files
1. Load ranges into memory
1. Iterate through queries, for each query iterate through ranges, count valid IDs

## Brute-force Method
1. Process Input  
use basic pair struct, load into a vector
1. Process Queries
use vector to iterate through loaded ranges;  
if a query is in a range, increment count and continue to the next query  
---
# oops pre-mature optimization
## Brainstorming 
* Goal: process ranges and combine or cull entries as needed.
* Consider three ranges: A:= (10,14), B:= (16-20) & C:= (12-18).  
* We can see that AuBuC is the inclusive range (10,20).
* Probably need to explore join algorithms: join-based tree algorithms -> maybe leverage binary trees?
* Can we load the ranges into a tree structure and traverse the tree to check valid IDs?

## Tree Brainstorming
* A:= (10,14), B:= (16-20) & C:= (12-18)
* Load Order: A > B > C
* When we load B, we initially have a disjoint set (no overlap with A)
* When we load C, we should ideally recognize that we have a connection from A to B via C
---
# PART 2
## Prompt Analysis
* Goal is to count the cardinality of the union of all sets
* Can we use bits to represent each member? Unlikely, we have extremely large inputs.
* Inclusive-Exclusive principle: |AuB| = |A| + |B| - |AnB|
* If we can figure out a way to quickly calculate |AnB| of all the sets, we can repeat the process.
* Quick browsing of wiki page for IEP: Sum all of the cardinalities, need to recursively calculate the all combinations of |AuB|, all combinations of |AuBuC|,...,
* IEP might not work since ideally we want to sequentially read in the sets one by one and update our count as necessary.
* Building some sort of tree might be useful.
* Let's build a binary tree. The left and right child will rep. the MIN and MAX range which we update as we read in values. Let roots with -1 indicate that we can check a range.
* To check for an overlapping range, we can continually traverse the binary tree until we find a range that has MIN in it. Then we continually traverse the tree until we either find a valid range for MAX or reach the end. We squish the tree by replacing the first MIN range's right child with MAX or the found right child

## Build the binary tree and use it to check if we've already counted a range.
* Interval trees? Center based?
* Sort the range by start and end?
* What if we first sort the ranges by the starting range then "build-up"?
* SO: https://stackoverflow.com/questions/4542892/possible-interview-question-how-to-find-all-overlapping-intervals
* Basically, throw everything into an array, marking if an interval is the start or end. Sort. Then iterate through.

## Walkthrough
* Ranges: (3,5), (10,14), (16,20), (12,18)
* Label each as starting and endpoint and place all into a single array. then sort: [3S, 5E, 10S, 14E, 16S, 20E, 12S, 18E] ->
[3S, 5E, 10S, 12S, 14E, 16S, 18E, 20E] ->
[3S, 5E, 10S, 14E, 16S, 18E, 20E]

## Just sort by starting point, and walk from left-to-right, combining as necessary

(3,5) (10,14), (16,20), (12,18)
(3,5) (10,14) (12,18) (16,20)
(a) (3,5) (10,14)
(b) (3,5) (10,18) // we read in (12,18)
(c) (3,5) (10,20) // we read in (16,20)

then we iterate through the list one more time to count the cardinality

1. Place all ranges into Range Struct (start, end)
1. Custom Comparer (lhs, rhs) needs to return true when (lhs less than rhs)
1. Feed into algorithm's sort std::sort(v.begin(), v.end(), &customComp)

sources:
1. https://stackoverflow.com/questions/873715/c-sort-with-structs
1. https://stackoverflow.com/questions/4542892/possible-interview-question-how-to-find-all-overlapping-intervals
