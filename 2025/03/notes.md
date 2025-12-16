int overflow; use int64_t (at least 64 bits is safe)

*new constaints:large strings
3232221546315133223433433342253232332422524653333335332433322333355343313233335255322525232232347253

1. choose largest number from left repeat 12 times
---
iterate number by number, goal is to check if prev index is worth replacing
check if curr > prev
8111...111 98
12 | 88

---
2. dynamic programming paradigm
memoization, build up?
(INDEX "think substring", BATTERIES) -> largest
foo(s, n) = max(s[0] + [for all i>=1] foo(i,n-1), foo(i, n))
int64_t foo(string STR, int BATTERIES)
	// iterate through STR
	// check each STR[i] + foo(SUBSTR, BATTERIES-1)

for each index, calculate (BATTERIES 1->11) and memoize

BASE CASES: check that size >= BATTERIES
BATTERIES = 0, largest is 0
BATTERIES = 1, largest is largest int in substring
BATTERIES = 2, largest of STR[i] + (foo(substring(i+1, end, 1))

RUNTIME: 11 loops, of size N

For the hashmap:
Array of Arrays
(INDEX) -> ARRAY of longs -> (BATTERIES) -> returns correct long long
init to -1, if -1, compute otherwise return long long.

est. x*10^12+
use long long

2147483648 negative values
0
2147483647
--- toy case walkthrough

12345
batteries 2
1 | (2345, 1) memoize (2345,1) (345,1) (45,1) (5,1)

RECURSION
(2345, 2)
2 | (345,1) <- memoized
RECURSION
(345,2)
3 | (45,1) <- memoized
RECURSION
(45,2) <- could also make this a basecase (substr_len == batteries)
4 | (5,1) <- memoized/basecase
(5,2) <- basecase return 0


12345; batteries 3
1 | (2345,2) memoize (345,1) (45,1) (5,1)

2345; batteries 2
2 | (345,1)

---
* Moving down = current brute-force; concerned about stack overflow
* building up from right->left (batteries,1->12) (building-up) should prevent stack overflows

12
11
10
9
8
7
.
.
.
4
3
2
1
---
* DATA_TYPE = int64_t; we want -1 to indicate an empty space (want 0 for calculation is invalid (45,3))
* "HASHMAP" = array<int,array<int, int64_t>> = MAP[INDEX][# OF BATTERIES] -> int64_t largest of (INDEX,BATT#)
space-complexity: N:= length of input string. SPACE := O(N)
* time-complexity: in-terms of function, O(N)

class:
	string
	map
	foo(builds/uses map) := lookup / calculate
	solver(build-up using foo)
	
foo(string, batteries): 	
	if map[foo(string,batteries)] != 1; return val;
	else
		largest = MAX( 	s[0] | foo(s[1:], batteries-1),
				foo(s[1:], batteries)	)
		store largest in foo(string,batteries)
		return largest

map (string, batteries)
Algorithm:
check if map(string,batteries) has an entry; if it does, use the value
otherwise, we need to calculate

the answer to (string,batteries) is the max of:
	s[0] | map(s[1:],batteries-1),
	map(s[1:], batteries)

the question is how to build a cpp hashtable that lets me look up the tuple string and number
Batteries -> String? (IE array (size 12) -> hashtable(string to string)