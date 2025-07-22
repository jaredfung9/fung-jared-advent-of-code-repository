from collections import deque
def generate_map(filename, side_len, bytes_to_read):
    map = [[0 for i in range(side_len)] for j in range(side_len)]
    f = open(filename, "r")
    for i in range(bytes_to_read):
        line = f.readline()
        tuple = line.strip().split(",")
        col, row = int(tuple[0]), int(tuple[1])
        if (0 <= col < side_len) and (0 <= row < side_len):
            map[row][col] = 1
    return (map, f)

def print_map(map, path=None):
    for row_ in enumerate(map):
        row = row_[0]
        for col_ in enumerate(row_[1]):
            col = col_[0]
            if path and (col, row) in path:
                print("O", end="")
            elif col_[1]:
                print("#", end="")
            else:
                print(".", end="")
        print()
    return 0

def get_neighbors(pos, max_row, max_col):
    x,y = pos
    deltas = [(0,1), (0,-1), (1,0), (-1,0)]
    neighbors = [(x + delta[0], y+ delta[1]) for delta in deltas]
    valid_neighbors = []
    for neighbor in neighbors:
        if (0 <=neighbor[0] < max_col) and (0 <= neighbor[1] < max_row):
            valid_neighbors.append(neighbor)
    return valid_neighbors

def bfs(start_pos, map):
    queue = deque([(start_pos[0],start_pos[1],[])]) #(x,y,path)
    visited = [[0 for i in range(len(map[0]))] for j in range(len(map))]
    while queue:
        x,y, path = queue.popleft()
        if not visited[y][x] and not map[y][x]:
            visited[y][x] = 1
            path = [] + path + [(x,y)]
            if (x == len(map) - 1) and (y == len(map[0]) -1):
                return path
            
            neighbors = get_neighbors((x,y), len(map), len(map[0]))
            for neighbor in neighbors:
                _x,_y = neighbor
                _path = [] + path
                queue.append((_x, _y, _path))
        else:
            continue
    return None

def dfs(start_pos, map):
    queue = deque([(start_pos[0],start_pos[1],[])]) #(x,y,path)
    visited = [[0 for i in range(len(map[0]))] for j in range(len(map))]
    while queue:
        x,y, path = queue.pop()
        if not visited[y][x] and not map[y][x]:
            visited[y][x] = 1
            path = [] + path + [(x,y)]
            if (x == len(map) - 1) and (y == len(map[0]) -1):
                return path
            
            neighbors = get_neighbors((x,y), len(map), len(map[0]))
            for neighbor in neighbors:
                _x,_y = neighbor
                _path = [] + path
                queue.append((_x, _y, _path))
        else:
            continue
    return None
def drop_byte(map, file):
    x,y = file.readline().strip().split(",")
    _x,_y  = int(x), int(y)
    map[_y][_x] = 1
    return (_x, _y)

def main():
    demo = ("demo_in.txt", 7, 12)
    real = ("input.txt", 71, 1024)
    input, map_len, bytes = real
    map, f = generate_map(input, map_len, bytes)
    #print_map(map)
    path = bfs((0,0), map)
    print("SHORTEST PATH LEN:", len(path) - 1)
    #print_map(map, path)
    while (bfs((0,0), map)):
        last_byte =drop_byte(map,f)
    print("FINISHING BYTE:", last_byte)
    return 0

if __name__ == "__main__":
    main()