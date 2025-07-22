from enum import Enum

class Direction(Enum):
    N = (0,-1)
    E = (1, 0)
    S = (0,1)
    W = (-1, 0)
    
    def get_cw_dir(self):
        if self.name == "N":
            return Direction.E
        elif self.name == "E":
            return Direction.S
        elif self.name == "S":
            return Direction.W
        else:
            return Direction.N
navi_map = {"^": Direction.N, ">": Direction.E, "v": Direction.S, "<": Direction.W}
icon_map = {Direction.N:"^", Direction.E:">", Direction.S:"v", Direction.W:"<"}

class Tiles():
    valid_chars = {"."} # Characters which are navigatable

    """Initialize a Tiles object from a given file. _tilemap[y][x] returns True iff the tile is a valid move."""
    def __init__(self, file):
        self._tilemap = []
        self.rows, self.cols = 0, 0

        # Contains initial guard x, y, and direction
        self.guard_start = (0,0, Direction.N)
        y = 0
        for line in file:
            x = 0
            line = line.replace("\n", "")
            valid_tiles = []
            for char in line:
                valid_tiles.append((char in Tiles.valid_chars) or (char in navi_map.keys()))
                if char in navi_map.keys():
                    self.guard_start = (x, y, navi_map[char])
                x += 1
            self._tilemap.append(valid_tiles)
            y += 1
        self.rows, self.cols = len(self._tilemap), len(self._tilemap[0])
    
    def movable(self, x, y):
        return self._tilemap[y][x]
    def in_bounds(self, x, y):
        valid_x = (0 <= x) and (x < self.cols)
        valid_y = (0 <= y) and (y < self.rows)
        return valid_x and valid_y
    
    "Attempts to move guard on map. Returns (x,y) which is the guard's new coordinates iff a move was made"
    def move(self, guard):
        _x, _y = guard.next_tile()
        if not self.in_bounds(_x, _y):
            return None
        
        while (not self.movable(_x, _y)):
            guard.turn_right()
            _x, _y = guard.next_tile()

            if (not self.in_bounds(_x, _y)):
                return None
        
        guard.x, guard.y = _x,  _y
        return (_x, _y)
    
    """Sets/unsets _tilemap[y][x] to be equal to False, indicating (x,y) is impassable."""
    def set(self, x, y):
        self._tilemap[y][x] = False
    def unset(self, x,y):
        self._tilemap[y][x] = True
      
class Guard():
    def __init__(self, x, y, dir):
        self.x, self.y, self.dir = x, y, dir
    def loc(self):
        return (self.x, self.y)
    def turn_right(self):
        self.dir = self.dir.get_cw_dir()
        
    def next_tile(self):
        delta_x, delta_y = self.dir.value
        return (self.x + delta_x, self.y + delta_y)

def print_tiles(tiles, guard):
    print("-"*50)
    y = 0
    for row in tiles._tilemap:
        x = 0
        for col in row:
            if (x == guard.x) and (y == guard.y):
                print(icon_map[guard.dir],end="")
            elif col:
                print(".",end="")
            else:
                print("#",end="")
            x += 1
        y += 1
        print()
    print("-"*50)

def MakeYourMove(tiles, guard, visual=False):
    move = tiles.move(guard)
    if move and visual:
        print_tiles(tiles, guard)
    return move

# Simulates a run of a given map. Returns a list of distinct tiles visited.
# If TIMEOUT > 0, times out after the guard visits TIMEOUT tiles that have been visited in a row. 
# Returns -1 if the run times out
def simulate_full_run(tiles, visual=False):
    x,y,dir = tiles.guard_start
    guard = Guard(x,y,dir)
    if visual:
        print("START")
        print_tiles(tiles, guard)
    
    visited = []
    move = MakeYourMove(tiles, guard, visual)
    while (move):
        if move not in visited:
            visited.append(move)
        move = MakeYourMove(tiles, guard, visual)
    if visual:
        print("END")
    return visited

# Performance class for identifying if (x,y) has been visited.
class VisitedBitmap():
    def __init__(self, rows):
        self.bitmap = []
        for row in range(rows):
            self.bitmap.append(0)
    def check_visited(self, x,y):
        return 0 != ((self.bitmap[y]) & (1 << x))
    def set_visited(self, x,y):
        self.bitmap[y] += (1 << x)

# Attempts to find a loop by timing out after seeing TIMEOUT consecutive visited tiles.
# Returns 0 if a run completes, -1 if it times out.
def simulate_fast_run(tiles, timeout=500):
    x,y,dir = tiles.guard_start
    guard = Guard(x,y,dir)
    bitmap = VisitedBitmap(tiles.cols)

    move = MakeYourMove(tiles, guard)
    consecutive = 0
    while (move):
        _x, _y = move
        if not bitmap.check_visited(_x, _y):
            consecutive = 0
            bitmap.set_visited(_x, _y)
        else:
            consecutive += 1
            if consecutive >= timeout:
                return -1
        move = MakeYourMove(tiles, guard)
    return 0
    
def part1():
    print("PART 1:")
    f = open("input6.txt", "r")
    tiles = Tiles(f)
    f.close()
    print(len(simulate_full_run(tiles)) + 1)
    
def part2():
    print("PART 2:")
    f = open("input6.txt", "r")
    tiles = Tiles(f)
    f.close()

    visited_tiles = simulate_full_run(tiles)
    loops = 0
    for tile in visited_tiles:
        _x, _y = tile
        if (_x == tiles.guard_start[0]) and (_y == tiles.guard_start[1]):
            continue
        tiles.set(_x, _y)
        run_results = simulate_fast_run(tiles,150)
        tiles.unset(_x, _y)
        if run_results == -1:
            loops += 1
    print(loops)
            
    
part1()
part2()
