
# Grid navigation (i, j)
""" Example Grid
 0 1 2
0
1
2
"""
# Given a filename, opens the file and returns the boundaries (# of rows, # of cols).
def map_boundaries(filename):
    file = open(filename, "r")
    rows, cols = 0,0
    for line in file:
        if line == '\n':
            break
        rows += 1
        line = line.replace("\n", "")
        cols = len(line)
    file.close()
    return (rows, cols)

# Returns a dictionary where key returns a list of nodes that have a tower with that frequency.
def sort_nodes(filename):
    file = open(filename, "r")
    ignore = {".", "#"}
    towers = dict()
    
    j = 0
    for line in file:
        line = line.replace("\n", "")
        i = 0
        for char in line:
            if char not in ignore:
                if char not in towers:
                    new_node_list = [(i,j)]
                    towers[char] = new_node_list
                else:
                    towers[char].append((i,j))
            i += 1
        j += 1
    file.close()
    return towers
""" Returns a list containing pairs of nodes. [A B C] -> [(A,B), (A,C), (B,C)]"""
def get_pairs(node_list):
    pair_list = []
    if len(node_list) <= 1:
        return pair_list
    node_a = node_list[0]
    for node_b in node_list[1:]:
        pair_list.append((node_a, node_b))
    results = pair_list + get_pairs(node_list[1:])
    return results

"example: ((1,1), (2,3)) -> (-1, -2)"
def calculate_vector(pair):
    return (pair[1][0] - pair[0][0], pair[1][1] - pair[0][1])

"""Returns (x1,y1) +/- (x2,y2) = (x1 +/- x2, y1 +/- y2)"""
def add_vectors(vec0, vec1):
    return (vec0[0] + vec1[0], vec0[1] + vec1[1])
def sub_vectors(vec0, vec1):
    return (vec0[0] - vec1[0], vec0[1] - vec1[1])

"""Given a list of towers with the same frequency, returns a list of possible antinodes."""
def calculate_possible_antinodes(node_list):
    pairs = get_pairs(node_list)
    antinodes = []
    for pair in pairs:
        vector = calculate_vector(pair)
        antinodes.append(sub_vectors(pair[0], vector))
        antinodes.append(add_vectors(pair[1], vector))
    return antinodes


def in_bound(boundary_pair, point):
    x,y = point
    bound_x, bound_y = boundary_pair
    valid_x = (x >= 0) and (x < bound_x)
    valid_y = (y >= 0) and (y < bound_y)
    return valid_x and valid_y

def part1():
    print("PART 1:")
    filename = "input8.txt"
    boundary_pair = map_boundaries(filename)
    towers = sort_nodes(filename)
    
    antinodes = []
    for freq in towers:
        node_list = towers[freq]
        potential_antinodes = calculate_possible_antinodes(node_list)
        for node in potential_antinodes:
            if (in_bound(boundary_pair, node)) and (node not in antinodes):
                antinodes.append(node)
    print(len(antinodes))

"""Similar to calculate_possible_antinodes, but requires boundaries of the map.
Returns a list of ALL antinodes that are within bounds of the map, including 
antinodes from resonate harmonics."""
def calculate_reson_antinodes(node_list, boundary_pair):
    pairs = get_pairs(node_list)
    antinodes = []

    for pair in pairs:
        antinodes.append(pair[0])
        antinodes.append(pair[1])
        vector = calculate_vector(pair)
        antinode_0 = sub_vectors(pair[0], vector)
        while (in_bound(boundary_pair, antinode_0)):
            antinodes.append(antinode_0)
            antinode_0 = sub_vectors(antinode_0, vector)
        antinode_1 = add_vectors(pair[1], vector)
        while (in_bound(boundary_pair, antinode_1)):
            antinodes.append(antinode_1)
            antinode_1 = add_vectors(antinode_1, vector)
    return antinodes

def print_antinodes(boundary_pair, antinodes):
    for j in range(0, boundary_pair[0]):
        for i in range(0, boundary_pair[1]):
            pair = (i,j)
            if pair in antinodes:
                print("#",end="")
            else:
                print(".",end="")
        print()
def part2():
    print("PART 2:")
    filename = "input8.txt"
    boundary_pair = map_boundaries(filename)
    towers = sort_nodes(filename)

    antinodes = []
    for freq in towers:
        node_list = towers[freq]
        _anitnodes = calculate_reson_antinodes(node_list, boundary_pair)
        for antinode in _anitnodes:
            if antinode not in antinodes:
                antinodes.append(antinode)

    print(len(antinodes))
part1()
part2()