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
