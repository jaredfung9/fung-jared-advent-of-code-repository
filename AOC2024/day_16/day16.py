from heapq import heappush, heappop
from collections import deque
class TileMap:
    def __init__(self, filename):
        self.tilemap = []
        f = open(filename, "r")
        for line in f:
            self.tilemap.append(line.replace("\n", ""))
        f.close()
        self.rows= len(self.tilemap)
        self.cols =len(self.tilemap[0]) 
    
    def get(self, x, y):
        return self.tilemap[y][x]
    
class GraphNode:
    next_id = 0
    def __init__(self, x, y, tilemap):
        self.neighbors = [] # Neighbor Positions
        self.id = GraphNode.next_id
        GraphNode.next_id += 1
        self.char = tilemap.get(x,y)
        self.x = x
        self.y = y
        self.tuple = (self.x, self.y)
    def __repr__(self):
        return str(self.tuple)
    def __le__(self, other):
        return self.id <= other.id
    def __lt__(self,other):
        return self.id < other.id
    

class Graph:
    def __init__(self, tilemap):
        self.tilemap = tilemap
        self.nodes = []
        self.start = None
        self.end = None

        deltas = [(0,1), (0,-1), (1,0), (-1,0)]
        for row in range(tilemap.rows):
            for col in range(tilemap.cols):
                _node = GraphNode(col, row, tilemap)
                
                if _node.char == "#":
                    continue
                else:
                    if _node.char == "S":
                        self.start = _node
                    if _node.char == "E":
                        self.end = _node
                    for delta in deltas:
                        _x, _y = col + delta[0], row + delta[1]
                        if tilemap.get(_x,_y) != "#":
                            _node.neighbors.append((_x,_y))
                    self.nodes.append(_node)
    def getNode(self, pos):
        for node in self.nodes:
            if (node.x == pos[0]) and (node.y == pos[1]):
                return node
        return None

class BFSQueue:
    def __init__(self):
        self.queue = deque()
    def isEmpty(self):
        return len(self.queue) <= 0
    def push(self, node, path, points, dir):
        self.queue.append((node, path, points, dir))
    def pop(self):
        return self.queue.pop()


class pathNode:
    next_id = 0
    def __init__(self, curr_pos, curr_dir, path, points):
        self.id = pathNode.next_id
        pathNode.next_id += 1
        self.curr_pos = curr_pos
        self.curr_dir = curr_dir
        self.path = path
        self.points = points
    def unpack(self):
        return self.curr_pos, self.curr_dir, self.path, self.points
    def __lt__(self, other):
        return self.points < other.points
    def __le__(self, other):
        return self.points <= other.points
    def __eq__(self, other):
        return self.id == other.id
    def __repr__(self):
        return str(self.id)

class dijkstraHeap:
    def __init__(self):
        self.heap = []
        return
    def isEmpty(self):
        return len(self.heap) <= 0
    def push_node(self, pathNode, priority):
        heappush(self.heap, (priority, pathNode))
    def pop_node(self):
        return heappop(self.heap)

direction_maps = {"N":(0,-1), "S":(0,1), "E":(1,0), "W":(-1,0)}
def dijkstra(_graph):
    start = pathNode(_graph.start.tuple, "E", [], 0)
    tilemap = _graph.tilemap
    visited = dict()
    for node in _graph.nodes:
        visited[node.tuple] = False

    heap = dijkstraHeap()
    heap.push_node(start, 0)
    while not heap.isEmpty():
        current_node = heap.pop_node()[1]
        pos, curr_dir, path, points = current_node.unpack()
        curr_char = tilemap.get(pos[0], pos[1])
        if curr_char == "E":
            return (points, path)
        for dir in direction_maps:
            delta = direction_maps[dir]
            _x, _y = pos[0] + delta[0], pos[1] + delta[1]
            _char = tilemap.get(_x, _y)
            if _char == "#":
                continue
            else:
                if visited[(_x, _y)]:
                    continue
                visited[(_x,_y)] = True
                _pos = (_x, _y)
                _dir = dir
                _path = [] + path + [_pos]
                _points = points
                if _dir == curr_dir:
                    _points += 1
                else:
                    _points += 1000 # Rotate 90 degrees CW/CCW
                    _points += 1 # Make Your Move
                _pathNode = pathNode(_pos, _dir, _path, _points)
                heap.push_node(_pathNode, _points)
    return None

def print_tiles(tiles, path=[]):
    for i in range(tiles.rows):
        for j in range(tiles.cols):
            if (j,i) in path:
                print("O",end="")
            else:
                print(tiles.get(j,i), end="")
        print()

def part1():
    print("PART 1:")
    tiles = TileMap("demomap.txt")
    #print_tiles(tiles)
    _graph = Graph(tiles)
    result = dijkstra(_graph)
    path = result[1]
    #print_tiles(tiles,path)
    print("POINTS:", result[0])

delta_to_dir_map = {(0,1):"S", (0,-1):"N", (1,0):"E", (-1,0):"W"}
def calculate_path_points(path):
    if len(path) <= 0:
        return 0
    prev_node = path[0]
    prev_pos = prev_node.tuple
    prev_dir = "E"
    _path = path[1:]
    points = 0
    for node in _path:
        pos = node.tuple
        delta = (pos[0] - prev_pos[0], pos[1] - prev_pos[1])
        dir = delta_to_dir_map[delta]
        if prev_dir == dir:
            points += 1
        else:
            points += 1000
            points += 1

        prev_pos = pos
        prev_dir = dir
    return points

class DijkstraNode():
    next_id = 0
    def __init__(self, position, dir):
        self.id = DijkstraNode.next_id
        DijkstraNode.next_id += 1
        self.pos = position
        self.dir = dir
    def __lt__(self, other):
        return self.id < other.id
    def __le__(self, other):
        return self.id <= other.id
    
# Given GRAPH and NODE and DIR (current facing), returns a list of pairs (NEXT_NODE, NEXT_DIR, POINTS TO NODE)
def get_neighbor_pairs(graph, dist, pos, dir):
    pairs = []
    x,y = pos
    for _dir in direction_maps:
        delta = direction_maps[_dir]
        _x,_y = x + delta[0], y + delta[1]
        if graph.tilemap.get(_x,_y) == "#":
            continue
        
        _points = dist[(x, y, dir)] + 1
        if _dir != dir:
            _points += 1000

        pairs.append(((_x,_y), _dir, _points))
    return pairs
def dijkstra2(graph, start):
    dist = {} # (x,y) -> shortest_path to START
    prev = {} # previous dijkstraNode node before  on shortest path
    Q = dijkstraHeap()  # min_priority queue (points, node)
    x,y = start
    for dir in ["N", "S", "W", "E"]:
        dist[(x, y, dir)] = 0
        dijkstraNode = DijkstraNode((x, y), dir)
        Q.push_node(dijkstraNode, 0)
    
    while not Q.isEmpty():
        # u = ([points], DijkstraNode(pos[(x,y)], dir {N E S W}))
        u = Q.pop_node()[1]
        pos, dir = u.pos, u.dir
        neighbor_pairs = get_neighbor_pairs(graph, dist, pos, dir)
        for neighbor_pair in neighbor_pairs:
            next_pos, next_dir, alt = neighbor_pair
            _x,_y = next_pos
            if not dist.get(((_x,_y, next_dir))) or alt < dist[(_x,_y, next_dir)]:
                dist[_x,_y, next_dir] = alt
                prev[(_x,_y, next_dir)] = (u)
                _next_dijkstra = DijkstraNode(next_pos, next_dir)
                Q.push_node(_next_dijkstra, alt)
    
    return dist, prev


def part2():
    print("PART 2:")
    tiles = TileMap("demomap.txt")
    _graph = Graph(tiles)
    best_score, best_path = dijkstra(_graph)
    dist_to_start, prev = dijkstra2(_graph, (_graph.start.tuple))
    dist_to_end, prev2 = dijkstra2(_graph, (_graph.end.tuple))
    print(best_score)
    best_nodes = []
    directions = ["N", "S", "E", "W"]
    for node in _graph.nodes:
        x,y = node.x, node.y
        for dir1 in directions:
            _start_cost = dist_to_start.get((x, y, dir1))
            if not _start_cost:
                continue
            for dir2 in directions:
                _end_cost = dist_to_end.get((x,y, dir2))
                if not _end_cost:
                    continue
                if _start_cost + _end_cost == best_score:
                    if node not in best_nodes:
                        best_nodes.append(node)
    print(len(best_nodes))
#print_tiles(tiles, [node.tuple for node in best_nodes])
part1()
part2()