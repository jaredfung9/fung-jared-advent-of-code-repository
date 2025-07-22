import numpy as np

def build_lists(filename):
    listset = []
    file = open(filename,"r")
    for line in file:
        line = line.replace("\n","")
        my_list = []
        for char in line:
            my_list.append(int(char))
        listset.append(my_list)
    file.close()
    return listset

def get_moves(position):
    i,j = position
    deltas = [(0,1),(0,-1),(1,0),(-1,0)]
    moves = []
    for delta in deltas:
        moves.append((i + delta[0], j + delta[1]))
    return moves

# max_x/y is the number of rows/cols.
def valid_index(move, max_i, max_j):
    i,j = move
    valid_i = (i >= 0) and (i < max_i)
    valid_j = (j >= 0) and (j < max_j)
    return valid_i and valid_j
    
def valid_move(grid, pos, move):
    i,j = pos
    _i,_j = move
    if not valid_index(move, len(grid), len(grid[0])):
        return False
    height, _height = grid[i][j], grid[_i][_j]
    return ((_height - height) == 1)
def peaks_reached(pos, grid, visited):
    i,j = pos
    if visited[i][j]:
        return 0
    else:
        visited[i][j] = 1
        height = grid[i][j]
        if height == 9:
            return 1
        possible_moves = get_moves(pos)
        moves = []
        for pos_move in possible_moves:
            if valid_move(grid, pos, pos_move):
                moves.append(pos_move)
        peaks = 0
        for move in moves:
            peaks += peaks_reached(move, grid, visited)
        return peaks

def part1():
    print("PART 1:")
    input = "input.txt"
    grid = np.array(build_lists(input))
    
    trailheads = []
    i = 0
    for row in grid:
        j = 0
        for col in row:
            if grid[i][j] == 0:
                trailheads.append((i,j))
            j += 1
        i += 1

    
    total_peaks = 0
    for trailhead in trailheads:
        visited = np.zeros((len(grid), len(grid[0])))
        reached = peaks_reached(trailhead, grid, visited)
        total_peaks += reached
    print(total_peaks)

def trail_finder(pos, grid, trail):
    i,j = pos
    if pos in trail:
        return 0
    else:
        if grid[i][j] == 9:
            return 1
        trail.append(pos)       
        possible_moves = get_moves(pos)
        moves = []
        for pos_move in possible_moves:
            if valid_move(grid, pos, pos_move):
                moves.append(pos_move)
        peaks = 0
        for move in moves:
            _trail = trail.copy()
            peaks += trail_finder(move, grid, _trail)
        return peaks
    
def part2():
    print("PART2:")
    input = "input.txt"
    grid = np.array(build_lists(input))
    
    trailheads = []
    i = 0
    for row in grid:
        j = 0
        for col in row:
            if grid[i][j] == 0:
                trailheads.append((i,j))
            j += 1
        i += 1

    
    total_peaks = 0
    for trailhead in trailheads:
        trail = []
        reached = trail_finder(trailhead, grid, trail)
        total_peaks += reached
    print(total_peaks)
    return
part1()
part2()