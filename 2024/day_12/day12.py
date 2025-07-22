import numpy as np
def file_to_list(filename):
    _list = []
    f = open(filename, "r")
    for line in f:
        _list.append(line.replace("\n", ""))
    f.close
    return _list

cardinal_deltas = [(0,1), (0,-1), (-1,0), (1,0)]
def explore_region(row, col, tiles, visited):
    if visited[row][col]:
        return None
    visited[row][col] = 1
    tile_val = tiles[row][col]
    area = 1
    fences = 0
    for delta in cardinal_deltas:
        adj_row, adj_col = row+delta[0], col+delta[1]
        if (adj_row < 0) or (adj_row >= len(tiles)) or (adj_col < 0) or (adj_col >= len(tiles[0])):
            fences += 1
        else: 
            adj_val = tiles[adj_row][adj_col]
            if adj_val != tile_val:
                fences += 1
            elif not visited[adj_row][adj_col]:
                result = explore_region(adj_row, adj_col, tiles, visited)
                area += result[0]
                fences += result[1]
    return (area, fences)

def part1():
    print("PART 1:")
    filename = "input.txt"
    tiles = file_to_list(filename)
    rows, cols = len(tiles), len(tiles[0])
    visited = np.zeros((rows,cols))
    cost = 0
    for row in range(rows):
        for col in range(cols):
            results = explore_region(row, col, tiles, visited)
            if results:
                cost += results[0] * results[1]
    print(cost)
    return 

class Tile():
    def __init__(self, val, row, col, tilemap):
        self._val, self.row, self.col = val, row, col
        self.tilemap = tilemap
        self._n = False
        self._s = False
        self._e = False
        self._w = False
    
    def __repr__(self):
        return str(self._val)
    def mark_north_edge(self):
        val = 0
        if not self._n:
            val = 1
        self._n = True
        east_tile = self.get_east_tile()
        while east_tile and east_tile._val == self._val:
            ne_tile = east_tile.get_north_tile()
            if ne_tile and ne_tile._val == self._val:
                break
            east_tile._n = True
            east_tile = east_tile.get_east_tile()
        
        west_tile = self.get_west_tile()
        while west_tile and west_tile._val == self._val:
            nw_tile = west_tile.get_north_tile()
            if nw_tile and nw_tile._val == self._val:
                break
            west_tile._n = True
            west_tile = west_tile.get_west_tile()
        return val
    
    def mark_south_edge(self):
        val = 0
        if not self._s:
            val = 1
        self._s = True
        east_tile = self.get_east_tile()
        while east_tile and east_tile._val == self._val:
            se_tile = east_tile.get_south_tile()
            if se_tile and se_tile._val == self._val:
                break
            east_tile._s = True
            east_tile = east_tile.get_east_tile()
        
        west_tile = self.get_west_tile()
        while west_tile and west_tile._val == self._val:
            sw_tile = west_tile.get_south_tile()
            if sw_tile and sw_tile._val == self._val:
                break
            west_tile._s = True
            west_tile = west_tile.get_west_tile()
        return val
    
    def mark_east_edge(self):
        val = 0
        if not self._e:
            val = 1
        
        self._e = True
        north_tile = self.get_north_tile()
        while north_tile and north_tile._val == self._val:
            ne_tile = north_tile.get_east_tile()
            if ne_tile and ne_tile._val == self._val:
                break
            north_tile._e = True
            north_tile = north_tile.get_north_tile()

        south_tile = self.get_south_tile()
        while south_tile and south_tile._val == self._val:
            se_tile = south_tile.get_east_tile()
            if se_tile and se_tile._val == self._val:
                break
            south_tile._e = True
            south_tile = south_tile.get_south_tile()
        return val
    
    def mark_west_edge(self):
        val = 0
        if not self._w:
            val = 1
        
        self._w = True
        north_tile = self.get_north_tile()
        while north_tile and north_tile._val == self._val:
            nw_tile = north_tile.get_west_tile()
            if nw_tile and nw_tile._val == self._val:
                break
            north_tile._w = True
            north_tile = north_tile.get_north_tile()

        south_tile = self.get_south_tile()
        while south_tile and south_tile._val == self._val:
            sw_tile = south_tile.get_west_tile()
            if sw_tile and sw_tile._val == self._val:
                break
            south_tile._w = True
            south_tile = south_tile.get_south_tile()
        return val

    def get_north_tile(self):
        adj_row, adj_col = self.row-1, self.col
        if not self.valid_index((adj_row, adj_col)):
            return None
        return self.tilemap[adj_row][adj_col]
    def get_south_tile(self):
        adj_row, adj_col = self.row+1, self.col
        if not self.valid_index((adj_row, adj_col)):
            return None
        return self.tilemap[adj_row][adj_col]
    def get_east_tile(self):
        adj_row, adj_col = self.row, self.col+1
        if not self.valid_index((adj_row, adj_col)):
            return None
        return self.tilemap[adj_row][adj_col]
    def get_west_tile(self):
        adj_row, adj_col = self.row, self.col-1
        if not self.valid_index((adj_row, adj_col)):
            return None
        return self.tilemap[adj_row][adj_col]

    def valid_index(self, coordinate):
        row,col = coordinate
        valid_row = (row >=0) and (row < len(self.tilemap))
        valid_col = (col >=0) and (col < len(self.tilemap[0]))
        return (valid_row) and (valid_col)
    def matching_tile(self, adjacent_tile):
        if adjacent_tile and adjacent_tile._val != self._val:
            return True
        return False
def build_tilemap(filename):
    f = open(filename, "r")

    tilemap = []
    row = 0
    for line in f:
        row_list = []
        line = line.replace("\n", "")
        col = 0
        for char in line:
            row_list.append(Tile(char, row, col, tilemap))
            col += 1
        tilemap.append(row_list)
        row += 1
    f.close()
    return tilemap

def count_tile_sides(tile):
    sides = 0
    if (not tile.get_north_tile()) or (tile.get_north_tile()._val != tile._val):
        sides += tile.mark_north_edge()
    if (not tile.get_south_tile()) or (tile.get_south_tile()._val != tile._val):
        sides += tile.mark_south_edge()
    if (not tile.get_east_tile()) or (tile.get_east_tile()._val != tile._val):
        sides += tile.mark_east_edge()
    if (not tile.get_west_tile()) or (tile.get_west_tile()._val != tile._val):
        sides += tile.mark_west_edge()
    return sides

def bulk_explore_tile(tile, visited):
    if visited[tile.row][tile.col]:
        return None
    visited[tile.row][tile.col] = 1

    area, sides = 1, 0
    sides += count_tile_sides(tile)
    adj_tiles = [tile.get_north_tile(), tile.get_south_tile(), tile.get_east_tile(), tile.get_west_tile()]
    for adj_tile in adj_tiles:
        if not adj_tile:
            continue
        if adj_tile._val == tile._val:
            result = bulk_explore_tile(adj_tile, visited)
            if result:
                area += result[0]
                sides += result[1]
    return (area, sides)
def part2():
    print("PART 2:")
    filename = "input.txt"
    tiles = build_tilemap(filename)
    rows, cols = len(tiles), len(tiles[0])
    visited = np.zeros((rows,cols))
    cost = 0
    for row in range(rows):
        for col in range(cols):
            result = (bulk_explore_tile(tiles[row][col], visited))
            if result:
                print(result)
                cost += result[0] * result[1]
    print(cost)
    return 
part1()
part2()