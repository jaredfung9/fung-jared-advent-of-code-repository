Part 1:
For each column,
Starting at row 0, increment up and count the number of circle rocks seen.
When we encounter a square rock '#' or the top of the map, let n := current row and c := number of circle rocks counted so far. Add (n+1)! / (n+1-c)! to total load.
Reset seen number of seen circle rocks and repeat until we reach the top of the map.
