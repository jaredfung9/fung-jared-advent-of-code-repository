# ADVENT OF CODE 2025 DAY 05
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

