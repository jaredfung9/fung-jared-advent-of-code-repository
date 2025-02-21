from functools import lru_cache
numeric_keypad = [
    ["7", "8", "9"],    # 0
    ["4", "5", "6"],    # 1
    ["1", "2", "3"],    # 2
    ["X", "0", "A"]     # 3
]
    # 0    1    2
numeric_start = (2,3)
direction_keypad = [
    ["X", "^", "A"],
    ["<", "v", ">"]
]
direction_start = (2, 0)

delta_to_dir = {
    (-1,0) : "<",
    (1,0) : ">",
    (0,1) : "v",
    (0,-1) : "^",
    (0,0) : "A"
}
dir_to_delta = {
    "<" : (-1,0),
    ">" : (1,0),
    "v" : (0,1),
    "^" : (0,-1),
    "A" : (0,0)
}
deltas = [(-1,0),(0,1), (0,-1), (1,0) ]

def dir_to_pos(dir):
    for j, row in enumerate(direction_keypad):
        for i, col in enumerate(row):
            if col == dir:
                return (i,j)
"""Returns a list of valid moves"""
def get_moves(pos, keypad):
    x,y = pos
    num_rows, num_cols = len(keypad), len(keypad[0])
    moves = []
    for delta in deltas:
        _x, _y = x + delta[0], y + delta[1]
        if (0 <= _x < num_cols) and (0 <= _y < num_rows):
            if keypad[_y][_x] != "X":
                moves.append(delta)
    return moves

"""Returns a list of moves for a shortest path to target_char"""
def BFS(start, target_char, tilemap):
    visited = [[0 for i in range(len(tilemap[0]))] for j in range(len(tilemap))]
    queue = deque()
    queue.append(
        (start, [])
    )
    while queue:
        pos, prev_moves = queue.popleft()
        x, y = pos
        if visited[y][x]:
            continue
        if tilemap[y][x] == target_char:
            return (prev_moves + ["A"])
        moves = get_moves(pos, tilemap)
        for move in moves:
            dx,dy = move
            _x,_y = x + dx, y + dy
            queue.append(((_x,_y), [] + prev_moves + [delta_to_dir[move]]))
        visited[y][x] = 1
    return None
   
#   Returns a dict where [CHAR][CHAR2] returns the shortest path from CHAR to CHAR2 on a
# directional keypad.
def calculate_shortest_dir_paths():
    all_edge_weights = dict()
    for start in "A<>^v":
        _edge_weights = dict()
        for end in "A<>^v":
            _edge_weights[end] = BFS(dir_to_pos(start),end,direction_keypad)
        all_edge_weights[start] = _edge_weights
    return all_edge_weights

# Helper function, given CHAR that is in TILES, returns coordinates (X, Y) where CHAR is in TILES
# Returns NONE if CHAR is not within TILES
def find_char(char, tiles):
    for j, row in enumerate(tiles):
        for i, col in enumerate(row):
            if col == char:
                return (i,j)
    return None      

def print_keypad(keypad):
    for row in keypad:
        print(row)

def pos_to_char(pos, keypad):
    x,y = pos
    return keypad[y][x]
def last_move(pos1, pos2):
    x,y = pos1
    _x,_y = pos2
    return delta_to_dir[(_x - x, _y - y)]

# Given two positions (CURR and NEXT) and a tilemap TILES, returns a list of paths from CURR to NEXT
def generate_paths(curr, next, tiles):
    if curr == next:
        return ["A"]
    x,y = curr
    _x, _y = next
    dx, dy = abs(x - _x), abs(y - _y)
    horizontal_mv = ">" if x < _x else "<"
    vertical_mv = "v" if y < _y else "^"
    horizontal_moves = dx*horizontal_mv
    vertical_moves = dy*vertical_mv
    paths = set([horizontal_moves + vertical_moves, vertical_moves + horizontal_moves])

    for path in list(paths):
        pos = curr
        for mv in path:
            x,y = pos
            dx,dy = dir_to_delta[mv]
            _x,_y = x + dx, y + dy
            pos = (_x, _y)
            if pos_to_char((_x,_y), tiles) == "X":
                paths.remove(path)
                break
            
    return [path + "A" for path in paths]

def solution(input_codes):
    paths = {}
    for keypad in (numeric_keypad, direction_keypad):
        for j, row in enumerate(keypad):
            for i, char in enumerate(row):
                if char != "X":
                    for _j, _row in enumerate(keypad):
                        for _i, _char in enumerate(_row):
                            if _char != "X":
                                paths[(char, _char)] = generate_paths((i,j), (_i,_j), keypad)
    
    @lru_cache(maxsize=None)
    def expand_code(code, layers_remaining):
        if layers_remaining == 0:
            return len(code)

        prev_char = "A"
        total = 0
        for char in code:
            total += min(expand_code(path, layers_remaining-1) for path in paths[(prev_char, char)])
            prev_char = char
        return total
    
    results = []
    for code in input_codes:
        results.append((code, expand_code(code, 26)))
    return results
def read_codes(filename):
    f = open(filename,"r")
    codes=[]
    for line in f:
        codes.append(line.strip())
    f.close()
    return codes
def main():
    codes = read_codes("input.txt")
    keypad = numeric_keypad
    start, end = "A", "8"    
    results = solution(codes)
    total = 0
    for result in results:
        num = int(result[0].lstrip("A0").rstrip("A"))
        total  += num * result[1]
        print(result, num)
    print(total)
if __name__ == "__main__":
    main()

# REFERENCE: https://github.com/mattbillenstein/aoc/blob/main/2024/21/p.py
# Algorithm sketch
# 1. Generate all paths from one point to another
# 2. Recursively expand (upwards) ALL paths, memoize the results and keep the minimum
# ROBOTS:
# dir_pad [USER]    min of all codes at this level is the answer
# dir_pad           ^
# dir_pad           ^
# .                 ^
# .                 ^
# .                 ^
# dir_pad      <- using paths generated from num_pad, iterate character by character, expanding upwards. MEMOIZE RESULTS
# num_pad      <- generate all paths from NUM_A to NUM_B
# example: paths ALWAYS returns a sequence of ^v<>A. (NUM, NUM) only occurs on first layer

# PATH GENERATION
# (x,y) -> (_x, _y)
# if (x < _x), move > else move <
# if (y < _y), move v else move ^
# number of these moves = nx and ny
# n* = difference between x and _x, ect.
# all paths =  make all of our lateral movements first followed by horizontal or vice versa nx[<>] and ny[^v] 
# step through path to ensure we do not hit panic space
# IE) ["<<<vvv" or "vvv<<<"]