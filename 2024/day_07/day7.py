import math
def process_line(line):
    return line.split(": ")

def read_file(file):
    inputs = []
    for line in file:
        if line != '\n':
            tokens = process_line(line.replace("\n", ""))
            tokens[0] = int(tokens[0])
            tokens[1] = [int(token) for token in tokens[1].split(" ")]
            inputs.append(tokens)
    return inputs

""" Branch Operations
Must return (int, [int, int, int...])"""

def add(total, parameters):
    sum = parameters[0] + parameters[1]
    return [total, [sum] + parameters[2:]]
def mul(total, parameters):
    product = parameters[0] * parameters[1]
    return [total, [product] + parameters[2:]]
def concat(total, parameters):
    if (len(parameters) < 2):
        return None
    joined_str = str(parameters[0]) + str(parameters[1])
    new_parameters = [int(joined_str)] + parameters[2:]
    return [total, new_parameters]

""" Returns True iff the given input can be satisfied by using the input ops. 
    Input should be of the form: [TOTAL, [n0, n1, n2..., ni]], [func0, func1,...,funcj]"""
def valid_equation(total, parameters, ops):
    if not parameters:
        return False
    if len(parameters) == 1:
        return total == parameters[0]
    else:
        branches = []
        for op in ops:
            branch = op(total, parameters)
            if branch:
                if (branch[0] >= parameters[0]):
                    branches.append(branch)
        for branch in branches:
            if valid_equation(branch[0], branch[1], ops):
                return True
        return False
    
def part1():
    print("PART 1:")
    f = open("input7.txt")
    inputs = read_file(f)
    f.close()

    ops = [add, mul]
    count = 0
    for input in inputs:
        total, parameters = input
        if valid_equation(total, parameters, ops):
            count += total
    print(count)

def slow_part2():
    print("PART 2:")
    f = open("input7.txt")
    inputs = read_file(f)
    f.close()

    ops = [add, mul, concat]
    count = 0
    for input in inputs:
        total, parameters = input
        if valid_equation(total, parameters, ops):
            count += total
    print(count)
def calculate_branches(total, parameters):
    branches = []
    if (total/parameters[-1]).is_integer():
        branches.append([total/parameters[-1], parameters[:-1]])
    
    digits = math.floor(math.log10(parameters[-1]) + 1)
    if ((total % (pow(10, digits))) == parameters[-1]):
            branches.append([total//(pow(10,digits)), parameters[:-1]])
    branches.append([total-parameters[-1], parameters[:-1]])
    return branches

def optimized_equation(total, parameters):
    if len(parameters) == 1:
        return total == parameters[0]
    
    branches = calculate_branches(total, parameters)
    for branch in branches:
        if optimized_equation(branch[0], branch[1]):
            return True
    return False
 
def part2():
    print("PART 2:")
    f = open("input7.txt")
    inputs = read_file(f)
    f.close()

    count = 0
    for input in inputs:
        if optimized_equation(input[0], input[1]):
            count += input[0]
    print(count)

#part1()
part2()
#slow_part2()
