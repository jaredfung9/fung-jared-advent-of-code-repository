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
    def __init__(self, file):
        self._tilemap = []
        self._rows = 0
        self._cols = 0
        for line in file:
            if line == "\n":
                break
            else:
                self._tilemap.append(list(line.replace("\n", "")))
        self._rows = len(self._tilemap)
        if self._rows >= 1:
            self._cols = len(self._tilemap[0])
        return
    def rows(self):
        return self._rows
    def cols(self):
        return self._cols
    def get_row(self, i):
        return self._tilemap[i]
    def get(self, x, y):
        return self._tilemap[y][x]
    def set(self, value, x, y):
        self._tilemap[y][x] = value
    def print_map(self):
        for row in range(0, self.rows()):
            for col in range(0, self.cols()):
                print(self.get(col, row), end="")
            print()

def add_tuples(tuple_1, tuple_2):
    if (len(tuple_1) != len(tuple_2)):
        return None
    sum = []
    for i in range(0, len(tuple_1)):
        sum.append(tuple_1[i] + tuple_2[i])
    return tuple(sum)

class Guard():
    def __init__(self, tiles):
        self.dir, self.x, self.y = Direction.N, 0, 0
        for i in range(0, tiles.rows()):
            for j in range(0, tiles.cols()):
                char = tiles.get(i,j)
                if char in navi_map.keys():
                    self.x = i
                    self.y = j
                    self.dir = navi_map[char]
                    return
        return
    def current_loc(self):
        return (self.x, self.y)
    def turn_right(self):
        self.dir = self.dir.get_cw_dir()
    def valid_tile(self, tiles, coordinates):
        x,y = coordinates[0], coordinates[1]
        return (tiles.get(x,y) == ".")
    def move_to_tile(self, tiles, coordinates):
        tiles.set(".", self.x, self.y)
        tiles.set(icon_map[self.dir], coordinates[0], coordinates[1])
        self.x, self.y = coordinates
    def in_bounds(self, tiles, coordinates):
        rows, cols = tiles.rows(), tiles.cols()
        x, y = coordinates
        if (x < 0) or (x >= cols):
            return False
        if (y < 0) or (y >= rows):
            return False
        else:
            return True
    def move(self, tiles):
        next = add_tuples(self.current_loc(), self.dir.value)
        if (not self.in_bounds(tiles, next)):
            return 0
        while (not self.valid_tile(tiles, next)):
            self.turn_right()
            next = add_tuples(self.current_loc(), self.dir.value)
        self.move_to_tile(tiles, next)
        return 1
    
def init_map(file):
    tiles = Tiles(file)
    guard = Guard(tiles)
    return (tiles, guard)

def MakeYourMove(guard, tiles, visualize=False):
    if guard.move(tiles):
        if visualize:
            tiles.print_map()
            print()
        return 1
    else:
        return 0

class Visited():
    visited = []
    def __init__(self, tiles):
        self.visited = [0 for i in range(0, tiles.rows())]
    def check_visited(self, coordinates):
        return (self.visited[coordinates[1]] & (1 << coordinates[0])) != 0
    def set_visit(self, coordinates):
        self.visited[coordinates[1]] += (1 << coordinates[0])

def count_guard_steps():
    f = open("input6.txt", "r")
    tiles, guard = init_map(f)
    visited = Visited(tiles)
    visited.set_visit(guard.current_loc())
    count = 1
    while (MakeYourMove(guard, tiles)):
        if not visited.check_visited(guard.current_loc()):
            visited.set_visit(guard.current_loc())
            count += 1
    print(count)
    f.close()

def calculate_visited_tiles(file):
    visited_tiles = []
    tiles, guard = init_map(file)
    while (MakeYourMove(guard, tiles)):
        if guard.current_loc() not in visited_tiles:
            visited_tiles.append(guard.current_loc())
    return visited_tiles

def detect_loop(map_data):
    tiles, guard = map_data
    timeout = 10000

    # Attempt to simulate an infinite loop
    visited = Visited(tiles)
    visited.set_visit(guard.current_loc())
    consecutive = 0
    loop_detected = False
    while (MakeYourMove(guard, tiles)):
        if not visited.check_visited(guard.current_loc()):
            visited.set_visit(guard.current_loc())
            consecutive = 0
        else:
            consecutive += 1
            if consecutive >= timeout:
                loop_detected = True
                break
    return loop_detected
def try_roadblock(map_data, coordinates):
    tiles = map_data[0]
    x,y = coordinates
    tiles.set("O", x, y)
    result = detect_loop(map_data)
    return result

def estimate_obstructions():
    filename = "input6.txt"
    f = open(filename, "r")
    visited_tiles = calculate_visited_tiles(f)
    f.close()

    blocks = 0
    for tile in visited_tiles:
            f = open(filename, "r")
            map_data = init_map(f)
            f.close()
            if (try_roadblock(map_data, tile)):
                blocks += 1
    print(blocks)
estimate_obstructions()
