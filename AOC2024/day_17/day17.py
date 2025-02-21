reg_A = 0
reg_B = 0
reg_C = 0
ip = 0
mem = []

def initialize_registers(filename):
    f = open(filename, "r")
    global reg_A, reg_B, reg_C
    reg_A = int(f.readline().split(" ")[2])
    reg_B = int(f.readline().split(" ")[2])
    reg_C = int(f.readline().split(" ")[2])
    f.close()
    return

def print_registers():
    global reg_A, reg_B, reg_C
    print("REGISTERS:", reg_A, reg_B, reg_C)
    return 

def load_memory(filename):
    global mem
    f = open(filename, "r")
    str_mem = f.readline().split(" ")[1].split(",")
    f.close()
    mem = [int(x) for x in str_mem]
    return

def combo_operand(operand):
    global reg_A, reg_B, reg_C
    if operand <= 3:
        return operand
    elif operand == 4:
        return reg_A
    elif operand == 5:
        return reg_B
    elif operand == 6:
        return reg_C
    return -1

def adv(operand):
    global reg_A
    denom = pow(2, combo_operand(operand))
    reg_A = reg_A // denom
    return 
def bxl(operand):
    global reg_B
    reg_B = reg_B ^ operand
    return 
def bst(operand):
    global reg_B
    reg_B = combo_operand(operand) % 8
    return
def jnz(operand):
    global reg_A, ip
    if reg_A == 0:
        return
    ip = operand - 2 # all instructions increment the ip by 2
    return
def bxc(operand):
    global reg_B, reg_C
    reg_B = reg_B ^ reg_C
    return
def out(operand):
    print(int(combo_operand(operand))%8, end=",")
    return
def bdv(operand):
    global reg_B
    denom = pow(2, combo_operand(operand))
    reg_B = reg_A // denom
    return 
def cdv(operand):
    global reg_C
    denom = pow(2, combo_operand(operand))
    reg_C = reg_A // denom
    return 

func_map = {
    0:adv,
    1:bxl,
    2:bst,
    3:jnz,
    4:bxc,
    5:out,
    6:bdv,
    7:cdv
}
def execute_instruction():
    global ip, reg_A, reg_B, reg_C, mem
    opcode = mem[ip]
    operand = mem[ip+1]
    func = func_map[opcode]
    print(func, operand)
    func(operand)
    ip += 2
    return
def part1():
    print ("PART 1:")
    global reg_A, reg_B, reg_C, ip, mem
    demo = ("demo_inst.txt", "demo_reg.txt")
    real = ("input_inst.txt", "input_reg.txt")
    test = ("test_inst.txt", "test_reg.txt")
    copy_demo = ("copy_demo_inst.txt", "copy_demo_reg.txt")
    input_inst, input_reg = test

    initialize_registers(input_reg)
    print_registers()
    load_memory(input_inst)
    print(mem)
    
    mem_size = len(mem)
    while ip < mem_size:
        execute_instruction()
    print()
    print("FINISHED:")
    print_registers()

def initialize_system(A):
    global reg_A, reg_B, reg_C
    reg_A, reg_B, reg_C = A,0,0
    return

def run_test():
    adv(3)
    #out(4)
    return # jnz 0
def run_input():
    global reg_A
    if reg_A == 0:
        return
    bst(4)
    bxl(5)
    cdv(5)
    bxl(6)
    adv(3)
    bxc(1)
    #out(5)
    return # jnz 0

def test_input(input):
    global reg_A, reg_B, reg_C
    initialize_system(input)
    run_input()
    return reg_A, reg_B

def find_test_input_As(possible_final_As, target):
    input_As = []
    global reg_A, reg_B
    for final_A in possible_final_As:
        for i in range(0, 8):
            initialize_system((final_A << 3) + i)
            run_test()
            exec_A, out = reg_A, reg_A % 8
            if (exec_A == final_A) and (out == target):
                input_As.append((final_A << 3) + i)
    return input_As

def find_initial_test_A(targets):
    final_As = [0]
    for target in targets:
        final_As = find_test_input_As(final_As, target)
    return final_As

def find_input_As(possible_final_As, target):
    input_As = []
    global reg_A, reg_B
    for final_A in possible_final_As:
        for i in range(0, 8):
            initialize_system((final_A << 3) + i)
            run_input()
            exec_A, out = reg_A, reg_B % 8
            if (exec_A == final_A) and (out == target):
                input_As.append((final_A << 3) + i)
    return input_As

def find_initial_A(targets):
    final_As = [0]
    for target in targets:
        final_As = find_input_As(final_As, target)
    return final_As

def get_target(filename):
    f = open(filename,"r")
    line = f.readline().split(" ")[1].split(",")
    out_list = [int(x) for x in line]
    f.close()
    return out_list

def part2():
    print("PART 2:")
    targets = get_target("input_inst.txt")
    #targets = [0,3,5,4,3,0]
    targets.reverse()
    print(min(find_initial_A(targets)))
#part1()
part2()