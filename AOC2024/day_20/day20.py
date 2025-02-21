def build_map(filename):
    f = open(filename, "r")
    tiles = [line.strip() for line in f]
    f.close()
    for line_ in enumerate(tiles):
        row, line = line_
        for char_ in enumerate(line):
            col, char = char_
            if char == "S":
                start = (col, row)
    return tiles, start

# Returns the next unvisited tile
def next_tile(pos, visited,tiles):
    deltas = [(0,1), (0,-1), (1,0), (-1,0)]
    visited[pos] = True
    x,y = pos
    for delta in deltas:
        _x,_y = x + delta[0], y + delta[1]
        if tiles[_y][_x] != "#":
            if not visited.get((_x,_y), False):
                return (_x, _y)
    return None

# Follows single path through race-track. For each tile, marks distance from start.
def build_path(start, tiles):
    visited = dict()
    visited[start] = True
    
    distances = dict()
    d=0
    next = start
    char = tiles[next[1]][next[0]]
    while char != "E":
        distances[next] = d
        next = next_tile(next, visited, tiles)
        char = tiles[next[1]][next[0]]
        d += 1
    distances[next] = d
    return distances

# Returns possible end tiles for using a viable cheat of picoseconds length.
def get_cheats(pos, tiles, picoseconds):
    x,y = pos
    end_pos = []
    for i in range(picoseconds+1):
        for j in range(picoseconds - i + 1):
            time_used = i + j
            pcx,pcy = j,i
            ncx,ncy = -j, -i
            deltas = [(pcx, pcy), (pcx,ncy), (ncx,pcy),(ncx,ncy)]
            for delta in deltas:
                cx,cy = delta    
                _x,_y = x + cx, y + cy
                if (0 <= _x < len(tiles[0])) and (0 <= _y < len(tiles)):
                    if tiles[_y][_x] != "#" and ((_x,_y),time_used) not in end_pos:
                        end_pos.append(((_x,_y), time_used))
    return end_pos

def build_cheat_map(start, tiles, picoseconds=2):
    distances = build_path(start, tiles)
    num_of_cheats = dict() # number of cheats which save X time
    visited = dict()
    visited[start] = True
    next = start
    char = tiles[next[1]][next[0]]
    while char != "E":
        cheat_tiles = get_cheats(next, tiles, picoseconds)
        for cheat_tuple in cheat_tiles:
            cheat, time_used = cheat_tuple
            if visited.get(cheat, False):
                continue
            d1 = distances[next]
            d2 = distances[cheat]
            time_saved = d2 - d1 - time_used # Takes two seconds to perform the cheat
            if time_saved > 0:
                if time_saved in num_of_cheats:
                    num_of_cheats[time_saved] += 1
                else:
                    num_of_cheats[time_saved] = 1
        next = next_tile(next, visited, tiles)
        char = tiles[next[1]][next[0]]
    return num_of_cheats
def main():
    demo = "demo_input.txt"
    real = "input.txt"
    input = real

    tiles, start = build_map(input)
    cheat_map = build_cheat_map(start, tiles, 20)
    
    #for key in sorted(cheat_map.keys()):
    #    if key >= 50:
    #        print(key, cheat_map[key])
    total = 0
    for key in cheat_map.keys():
        if key >= 100:
            total += cheat_map[key]
    print(total)
    return 0

"""Part 2 Brainstorm: use distance map, for i in range(# of row): (for j in range(# of col - i)) check if tile is valid -> calculate distance
    Cheat time used = i + j
    Time saved = Distance[Cheated Tile] + Distance[Starting Tile] - Cheat time used"""
if __name__ == "__main__":
    main()