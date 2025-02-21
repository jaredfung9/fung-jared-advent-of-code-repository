class Tilemap():
    master_tiles = None
    def __init__(self, filename):
        self._tilemap = []
        f = open(filename, "r")
        for line in f:
            new_row = []
            for char in line.replace("\n", ""):
                new_row.append(char)
            self._tilemap.append(new_row)
        f.close()
        
    def generate_master_tiles(filename):
        Tilemap.master_tiles = Tilemap(filename)
    
    def set_tile(self, x, y, val):
        self._tilemap[y][x] = val

    def get_tile(self, x, y):
        return self._tilemap[y][x]
    
    def move_tile(self, x, y, _x, _y):
        self.set_tile(_x, _y, self.get_tile(x, y))
        self.set_tile(x, y, '.')
        return
    
    def print_tiles(tilemap):
        for row in tilemap._tilemap:
            for tile in row:
                print(tile, end="")
            print()
        print("---")

    def enlarge_tilemap(tilemap):
        big_map = []
        char_dict = { "#" : ("#", "#"), "O" : ("[","]"), "@" : ("@","."), "." : (".",".")}
        for row in tilemap._tilemap:
            big_row = []
            for char in row:
                big_row.append(char_dict[char][0])
                big_row.append(char_dict[char][1])
            big_map.append(big_row)
        tilemap._tilemap = big_map

deltas = {'v' : (0,1), '<':(-1,0), '>':(1,0), '^':(0,-1)}

def attempt_move(x, y, move_char, tilemap=None):
    if not tilemap:
        tilemap = Tilemap.master_tiles
    delta = deltas[move_char]
    _x, _y = x + delta[0], y + delta[1]
    next_val = tilemap.get_tile(_x, _y)
    
    if next_val == '#':
        return False
    elif next_val == 'O':
        pushed = attempt_move(_x, _y, move_char)
        if pushed:
            tilemap.move_tile(x,y,_x,_y)
        return pushed
    else:
        tilemap.move_tile(x,y,_x,_y)
    return True

def attempt_move_plus(x, y, move_char, tilemap=None):
    if not tilemap:
        tilemap = Tilemap.master_tiles
    delta = deltas[move_char]
    _x, _y = x + delta[0], y + delta[1]
    next_val = tilemap.get_tile(_x, _y)
    
    if next_val == '#':
        return False
    elif next_val in ['[', ']']:
        pushed = attempt_move_block(_x, _y, move_char)
        if pushed:
            tilemap.move_tile(x,y,_x,_y)
        return pushed
    else:
        tilemap.move_tile(x,y,_x,_y)
    return True

# for ea. delta: deltas[0] = input_pos delta, deltas[1] = partner_pos delta
up_deltas = {'[':[(0,-1), (1,-1)], ']':[(0,-1),(-1,-1)]}
down_deltas = {'[':[(0,1), (1,1)], ']':[(0,1),(-1,1)]}
left_deltas = {']':[(-1,0),(-2,0)]}
right_deltas = {'[':[(1,0),(2,0)]}

all_deltas = {'^':up_deltas, 'v':down_deltas, '>':right_deltas, '<':left_deltas}
partner_deltas = {'[':(1,0), ']':(-1,0)} # used for find partner block's tile

def find_blocks_to_move(x,y,move_char,tilemap=None):
    if not tilemap:
        tilemap = Tilemap.master_tiles
    delta_list = all_deltas[move_char][tilemap.get_tile(x,y)]
    next_pos = []
    for delta in delta_list:
        next_pos.append((x+delta[0], y+delta[1]))
    
    partner_delta = partner_deltas[tilemap.get_tile(x,y)]
    partner_pos = (x + partner_delta[0], y + partner_delta[1])
    
    blocks_to_move = []
    for pos in next_pos:
        if pos == partner_pos:
            continue
        next_char = tilemap.get_tile(pos[0], pos[1])
        if next_char == '#':
            return (False, [])
        elif next_char in ['[', ']']:
            pushed, _blocks_to_move = find_blocks_to_move(pos[0],pos[1],move_char,tilemap)
            if not pushed:
                return (False, [])
            blocks_to_move += (_blocks_to_move)
    blocks_to_move += [((partner_pos),next_pos[1]), ((x,y),next_pos[0]) ]
    return (True, blocks_to_move)

# x,y must point to [ or ] character (ie. a block)
def attempt_move_block(x,y, move_char, tilemap=None):
    if not tilemap:
        tilemap = Tilemap.master_tiles
    delta_list = all_deltas[move_char][tilemap.get_tile(x,y)]

    next_pos = []
    for delta in delta_list:
        next_pos.append((x+delta[0], y+delta[1]))

    partner_delta = partner_deltas[tilemap.get_tile(x,y)]
    partner_pos = (x + partner_delta[0], y + partner_delta[1])

    blocks_to_move = []
    for pos in next_pos:
        next_char = tilemap.get_tile(pos[0], pos[1])
        if next_char == '#':
            return False
        elif next_char in ['[', ']']:
            if pos == partner_pos:
                continue
            pushed, _blocks_to_move = find_blocks_to_move(pos[0],pos[1], move_char)
            if not pushed:
                return False
            for block in _blocks_to_move:
                if block not in blocks_to_move:
                    blocks_to_move.append(block)
            

    
    blocks_to_move.append((partner_pos, next_pos[1]))
    blocks_to_move.append(((x,y), next_pos[0]))

    for block_move in blocks_to_move:
        if len(block_move) != 2:
            print("HERE")
            return False
        start_x, start_y = block_move[0]
        next_x, next_y = block_move[1]
        tilemap.move_tile(start_x, start_y, next_x, next_y)
    return True

class Robot():
    def __init__(self, _x, _y):
        self.x, self.y = _x, _y
    def find_starting_robot(tilemap):
        y = 0
        for row in tilemap._tilemap:
            x = 0
            for char in row:
                if char == "@":
                    return (x, y)
                x += 1
            y += 1
        return None
    def robot_move(self, move_char, tilemap=None):
        if not tilemap:
            tilemap = Tilemap.master_tiles
        moved = attempt_move(self.x, self.y, move_char, tilemap)
        if moved:
            delta = deltas[move_char]
            self.x, self.y = self.x + delta[0], self.y + delta[1]
        return
    
    def robot_move_plus(self, move_char, tilemap=None):
        if not tilemap:
            tilemap = Tilemap.master_tiles
        moved = attempt_move_plus(self.x, self.y, move_char, tilemap)
        if moved:
            delta = deltas[move_char]
            self.x, self.y = self.x + delta[0], self.y + delta[1]
        return
    def __repr__(self):
        return "("+str(self.x)+","+str(self.y)+")"
def print_master():
    Tilemap.print_tiles(Tilemap.master_tiles)

def move_and_print(robot, move_char):
    robot.robot_move(move_char)
    print_master()
    return

def get_instruction_str(filename):
    f = open(filename, "r")
    inst_str = ""
    for line in f:
        inst_str += line
    f.close()
    return inst_str.replace("\n","")

def count_GPS(tilemap):
    sum_GPS = 0
    y = 0
    for row in tilemap._tilemap:
        x = 0
        for char in row:
            if char == "O":
                sum_GPS += 100*y + x
            elif char == "[":
                sum_GPS += 100*y + x
            x += 1
        y += 1
    return sum_GPS


def part1():
    print("PART 1:")
    map_in = "map_input.txt"
    Tilemap.generate_master_tiles(map_in)
    #print_master()
    _x, _y = Robot.find_starting_robot(Tilemap.master_tiles)
    myRobot = Robot(_x, _y)
    for char in (get_instruction_str("inst_input.txt")):
        myRobot.robot_move(char)
    #print_master()
    print(count_GPS(Tilemap.master_tiles))


def part2():
    print("PART 2:")
    map_in = "map_input.txt"
    new_tiles = Tilemap(map_in)
    Tilemap.enlarge_tilemap(new_tiles)
    Tilemap.master_tiles = new_tiles
    starting_pos = Robot.find_starting_robot(new_tiles)
    myRobot = Robot(starting_pos[0], starting_pos[1])
    Tilemap.print_tiles(new_tiles)

    test_string = "vvv<v^^>>>>>>^>"
    for char in (get_instruction_str("inst_input.txt")):
        myRobot.robot_move_plus(char)
    Tilemap.print_tiles(new_tiles)
    print(count_GPS(Tilemap.master_tiles))
part1()
part2()