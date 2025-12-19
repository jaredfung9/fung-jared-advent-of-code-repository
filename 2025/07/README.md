# Advent of Code 2025: Day 07

## Brainstorming
* Bitmasks
1. Convert input into binary.
1. Read in input as binary (Read in line; use stoi)

a := current beam path

b := continuing beams
c := split_beams

b = a - a&b
---
Probably easier to just work in strings and use standard indexing
## Bit-mask solution:

a:= current beams
b:= next_row (splitters)
c:= a&b

## Check for beam collisions and build splits
1. use & to detect hits with splitters
1. use << and >> to build bitmasks to for beam splits
1. use | to combine rows
1. subtract beam collisions from current beams
1. add split beams back to current beams
1. read in next row

### Bits
* After investigating the main input file, using the bitmask solution would require using an integer that has at least 141 bits.
* Therefore, a bitset works better.
* Might have to divide the set into individual int_blocks (from right to left).
### Strings
* At this point, it's better to just roll a quick custom class

# Manifold class
* string beams
* ifstream input

string collisions(string next_row) // Given 
public:
void printCurrentBeam();
int update(); // Returns -1 if EOF, otherwise calculates the next row of beams.
