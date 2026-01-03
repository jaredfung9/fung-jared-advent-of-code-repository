## 2025-Day11 Part 1 Outline
* Build two hashmaps
* First maps name -> vector of children names
* Second maps name -> number of paths to out from this node.
## Build the first one by iterating through file
* Track second list containing list of names that only map to out
## Build the second one by initializing base cases then recursively building up
* Optimize with memoization
## Use DFS to find all paths to out