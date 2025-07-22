def AND(a,b):
    return 1 if (a == 1) and (b == 1) else 0
def XOR(a,b):
    return 1 if a != b else 0
def OR(a,b):
    return 1 if ((a == 1) or (b == 1)) else 0

op_map = {
    "AND" : AND,
    "XOR" : XOR,
    "OR" : OR
}
def process_queue(signal, queue, signals):
    if signal in queue:
        for _tuple in queue[signal]:
            op,a,b,dest = _tuple
            if (a in signals) and (b in signals):
                if dest in signals:
                    continue
                signals[dest] = op_map[op](signals[a],signals[b])
                process_queue(dest, queue, signals)
    return 

def parse_input(filename):
    signals, queue = dict(), dict()
    f = open(filename, "r")
    line = f.readline()
    while line != "\n":
        wire, val = line.strip().split(": ")
        signals[wire] = int(val)
        line = f.readline()
    
    for line in f.readlines():
        inst, dest = line.strip().split(" -> ")
        a, op, b = inst.split(" ")
        if (a in signals) and (b in signals):
            if dest in signals:
                continue
            signals[dest] = op_map[op](signals[a],signals[b])
            if dest in queue:
                process_queue(dest, queue, signals)
        else:
            inst_tuple = (op, a, b, dest)
            if a not in queue:
                queue[a] = []
            if b not in queue:
                queue[b] = []
            queue[a].append(inst_tuple)
            queue[b].append(inst_tuple)
    f.close()
    return signals

def part1():
    print("PART 1:")
    signals = parse_input("input.txt")
    i = 0
    for key in signals.keys():
        if key[0] == "z":
            i += int(signals[key]) << int(key.lstrip("z"))
    print(i)
    return
    
def build_DAG(filename):
    parents = dict()
    children = dict()
    seen_zs = []
    f = open(filename, "r")
    line = f.readline()
    while line != '\n':
        line = f.readline()

    for line in f.readlines():
        inst, dest = line.strip().split(" -> ")
        a, op, b = inst.split(" ")
        parents[dest] = (op, a, b)
        children[(op, a, b)] = dest
        if dest[0] == 'z':
            seen_zs.append(dest)
    f.close()
    return parents, children, seen_zs

def get_id(id_chars):
    return int(id_chars.strip("xyz"))
    
def build_circuit_to_file(filename):
    parents, children, zs = build_DAG(filename)
    zs.sort()
    out = open("out.txt", "w")
    for z in zs:
        opcode, a, b = parents[z]
        out.write(str(z) + " " + str(opcode) + " " + str(a) + " " + str(b) +'\n')
        if a in parents:
            _op, _a, _b = parents[a]
            out.write(str(a) + " " + str(_op) + " " + str(_a) + " " + str(_b)+'\n')
        if b in parents:
            _op, _a, _b = parents[b]
            out.write(str(b) + " " + str(_op) + " " + str(_a) + " " + str(_b)+'\n')
        out.write("-"*5)
        out.write("\n")
    out.close()
    return 0

def find_XOR(id, children):
    op = "XOR"

    a = "x" + id
    b = "y" + id
    tuple0 = (op, a, b)
    tuple1 = (op, b, a)
    print(tuple0, end = " : ")
    if tuple0 in children:
        print(children[tuple0])
    if tuple1 in children:
        print(children[tuple1])
    return 0

"""
Strategy: read https://en.wikipedia.org/wiki/Adder_(electronics)
1. build_circuit_to_file outputs the current input gates to all z wires
2. parse through zs to find any which have incorrect opcodes (all zs must have XOR to be a full adder)
* we note that for any given zn must be an XOR of (XOR xn yn) ??
3. find the gate which outputs XOR xn yn by using find_XOR.
4. find the XOR instruction which uses the gate from #3, the output wire for this instruction needs to be swapped with the incorrect zn
5. parse through out.txt to ensure each wire has a structure of (XOR (XOR ...) (OR ... )) or (XOR Sn Cn-1)
"""
def part2():
    print("PART 2:")
    input = "input.txt"
    parents, children, zs = build_DAG(input)
    # Parents where parents[output_gate] returns the (op, in_a, in_b) that compose the gate
    # Children maps a desired instruction code (op, a, b) to an output gate.
    build_circuit_to_file(input)
    # build_circuit_to_file processes the input file:
    # 1. outputs the input gates + operation for each z wire
    # 2. attempts to output the input gates + operation for each of the z wires' parents
    incorrect_zs = []
    for z in zs:
        id = get_id(z)
        opcode, a, b = parents[z]
        if opcode != "XOR":
            incorrect_zs.append((z, (opcode, a, b)))
    incorrect_zs.sort()
    for z in incorrect_zs:
        print(z)
    print()
    
    id = "09"
    find_XOR(id, children)

    # l contains the gates which have output wires which need to be swapped
    l = ["z09", "nnf", "z20", "nhs", "z34", "wrc", "kqh", "ddn"]
    l.sort()
    for x in l:
        print(x, end=",") # output answer
    print()
    
    return
def main():
    part1()
    part2()
    return

if __name__ == "__main__":
    main()