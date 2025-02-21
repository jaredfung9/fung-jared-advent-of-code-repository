import os, re
from PIL import Image
import numpy as np

class Robot():
    all_robots = []
    max_row, max_col = 0,0
    def load_map(row, col):
        Robot.max_row = row
        Robot.max_col = col
    
    def __init__(self, x, y, dx, dy):
        self.x, self.y = x,y
        self.dx, self.dy = dx,dy
        Robot.all_robots.append(self)
    
    def next_state(self):
        self.x += self.dx
        self.y += self.dy
        self.x = self.x % Robot.max_col
        self.y = self.y % Robot.max_row
        return
    
    def __repr__(self):
        return str(self.x) + "," + str(self.y)

def load_robots(filename):
    f = open(filename, "r")
    for line in f:
        line=line.replace("\n","").replace("p=", "").replace("v=","")
        tokens = line.split(" ")
        pos_list = list(map(lambda x : int(x), tokens[0].split(",")))
        delta_list = list(map(lambda x : int(x), tokens[1].split(",")))
        x,y = pos_list
        dx,dy = delta_list
        Robot(x,y,dx,dy)
    f.close()
    return 
def print_robot(robot):
    for i in range(Robot.max_row):
        for j in range(Robot.max_col):
            if (i == robot.y) and (j == robot.x):
                print("1",end="")
            else:
                print(".", end="")
        print()

def move_all_robots():
    for robot in Robot.all_robots:
        robot.next_state()
    return

def get_map_string():
    pos_list = []
    for robot in Robot.all_robots:
        pos_list.append((robot.x, robot.y))
    string = ""
    for i in range(Robot.max_row):
        for j in range(Robot.max_col):
            pos_tuple = (j,i)
            if pos_tuple in pos_list:
                string += "#"
            else:
                string += " "
        string += '\n'
    string += "---------------------------------"
    return string

def count_robots_in_quadrant(start_col, start_row, end_col, end_row):
    total = 0
    for robot in Robot.all_robots:
        valid_col = (robot.x >= start_col) and (robot.x < end_col)
        valid_row = (robot.y >= start_row) and (robot.y < end_row)
        if valid_col and valid_row:
            total += 1
    return total

def part1():
    _input = "input.txt"
    _output = "OUT.txt"
    out = open(_output, "w")
    Robot.load_map(103, 101)
    load_robots(_input)
    mid_col = Robot.max_col // 2
    mid_row = Robot.max_row // 2

    for i in range(100):
        move_all_robots()
    quad1_bots = count_robots_in_quadrant(0,0,mid_col,mid_row)
    quad2_bots = count_robots_in_quadrant(mid_col+1, 0,Robot.max_col, mid_row)
    quad3_bots = count_robots_in_quadrant(0,mid_row+1,mid_col,Robot.max_row)
    quad4_bots = count_robots_in_quadrant(mid_col+1, mid_row+1, Robot.max_col, Robot.max_row)
    safety_factor = quad1_bots * quad2_bots * quad3_bots * quad4_bots
    print(safety_factor)

def output_frame(output):
    array = np.zeros((103,101))
    for robot in Robot.all_robots:
        array[(robot.y, robot.x)] = 255
    array = np.array(array, dtype=np.uint8)
    img = Image.fromarray(array)
    img.save(output)
    return

def part2():
    _input = "input.txt"
    Robot.load_map(103, 101)
    load_robots(_input)
    output = "frame"
    output_extension = ".png"
    for i in range(103*101):
        move_all_robots() 
        output_frame(output + str(i) + output_extension)
    return

#part1()
part2()