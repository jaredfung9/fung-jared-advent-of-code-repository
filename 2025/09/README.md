# COMPRESSION ALGORITHM
## Observations
1. Very big range. In order to store the true map, we would require 100000x100000 memory addresses. (The range of each coordinate is from 1000-100000).
1. There are only a handful of actual points (~500). Additionally, many of these points are paired due to the nature of the problem.
1. In this problem, we have a lot of empty space in between the actual points. Instead of saving 10000 empty spaces and checking all 10000 when we want to check if an area is valid, we can combine these 10000 empty spaces into a single tile.
1. When we want to calculate the original area, we can map from our compressed coordinates back into the original domain.
## Forming a Bijection
* KEY NOTE: The order of original points matters as it indicates the connections that form the perimeter.
1. First, sort each point by rows and remove duplicates. Build a vector, starting from i = 1; iterate through the row coordinate and assign each coordinate to vector[i], incrementing i by 2 each time. Using the original coordinate as a key, save i as the value in a hashmap. Once we reach the end, increment i by 1 to add a final empty row/col.
* EX: Original Y-coords {1000, 10000, 100000} -> {1, 3, 5}
* Observe that the map we would need to store the original would need to be at least 100000 tall. Our compression would only need to be 5 tall.
1. Repeat for cols.
1. The vectors form a map from (COMPRESSED, ORIGINAL) by accessing each indice.
1. The hashmap forms a map from (ORIGINAL, COMPRESSED).
### PROOFS
1. Onto: We iterated through the entire inputs and only removed duplicates.
1. One-to-One: We removed duplicates, so all that remains in our sorted point list are unique values. Each value is assigned a unique odd number. All even indices are buffers representing all the empty space. (Edge case: if there is no empty space in the original, we have a phantom empty space. We may have to verify empty space before inserting a buffer indice.)
* The 0th row/col and ith row/col are guaranteed to be empty spaces.
* Therefore, we have formed a bijection between (ORIGINAL, COMPRESSED).

## Algorithms
### Input Processing
#### Coordinate Compression
* See **Forming a Bijection** Above
* Hashmap CompressedRow(ORIGINAL -> COMPRESSED)
* Hashmap CompressedCol(ORIGINAL -> COMPRESSED)
* Vector OriginalRow(COMPRESSED -> ORIGINAL)
* Vector OriginalCol(COMPRESSED -> ORIGINAL)
* int M = final i value
#### Valid tiles
1. MxM array VALIDMAP
1. Using CompressedRow/Col, Initialize the starting point in VALIDMAP.
1. Iterate through our input list, converting each original value into the compressed plane. Walk from the previous point to the next point, marking each traversed point as valid. We can tell which direction to travel by comparing (x1,y1) to (x2, y2).
1. Continue until we reach the end of input. Then, walk from the final point back to the starting point.
1. Initialize an buffer MxM array starting from (0,0) run BFS and mark tiles if they are not marked in our original array (IE, mark non-perimeter tiles). Since (0,0) is guaranteed to be outside our created perimeter, running BFS will return a map indicating all INVALID tiles.
* MxM INVALID_map
### Area Verification
1. We are interested in all the rectangles formed by selecting two red tiles (our input). In order to verify that all the area's tiles are red-green, we only need to check that all of a given area's perimeter tiles are valid (All inner tiles are guaranteed to be red-green). Check that each tile is NOT in the INVALID map.
1. First, we select two tiles to be opposite corners. We can easily find the other two corners at (x1,y2) and (x2, y1). We will verify an area is valid by attempting to walk from each corner to an adjacent one until we arrive at our starting corner.

#### ORIGINAL PART 2 BRAINSTORMS
/* Brainstorm: It is possible to initialize a 100000x100000 bool map to indicate if a tile is valid. 
Input list walks us around the perimeter. Maybe we can identify valid ranges for each row and column. 
Leverage the fact that each line indicates a move (we only move by a column or row) to identify the min and max of each row and column.
It seems like each row and column has a pair of points.
consider the following case study:

    ...#X#
    ...X.X
    #XX#.X
    X....X
    #XXXX#

Points:
    (0,0)
    (5,0)
    (5,4)
    (3,4)
    (3,2)
    (0,2)

Ranges  
Col         Row
0 : 0,2     0 : 0,5
5 : 0,4     4 : 3,5
3 : 2,4     2 : 0,3

Invalid Area:
(0,2) (3,4)
Valid Area:
(0,2) (5,0)

Corners
(x1,y1) (x2, y2) -> (x1,y2) (x2,y1)
[(0,2) (3,4)] (0,4) (3,2) <- calculate other corners
[(0,2) (5,0)] (0,0) (5,2)
check if each corner is in range

Is it okay to return validCols | validRows or do we need both Cols and Rows to be valid?
A valid area will pass at least one range check.
An invalid area is unable to pass any test because it neither has a valid row or col.
*/

/* Contains a set of valid row and col ranges.
Can be used to check if a corner is in range. */
// class Ranges {
// };