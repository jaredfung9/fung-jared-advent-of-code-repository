def get_next_block(file):
    line = file.readline()
    result = []
    while (line != "\n") and (line != ""):
        result.append(line.strip())
        line = file.readline()
    return result

def is_lock(block):
    top_row = block[0]
    for char in top_row:
        if char != "#":
            return False
    return True

def print_block(block):
    for row in block:
        print(row)
    print()
    return

def block_heights(block):
    h = [-1 for i in range(5)]
    for row in block:
        i = 0
        for char in row:
            if char == "#":
                h[i] += 1
            i += 1
    return h

def parse_input(filename):
    keys, locks = [], []
    f = open(filename, "r")
    block = get_next_block(f)
    while block:
        h = block_heights(block)
        if is_lock(block):
            locks.append(h)
        else:
            keys.append(h)
        block = get_next_block(f)
    f.close()
    return keys, locks

def part1():
    print("PART 1:")
    real = "input.txt"
    demo = "demo.txt"
    input = real
    keys, locks = parse_input(input)
    
    unique_pairs = 0
    for lock in locks:
        for key in keys:
            valid_h = True
            for i in range(5):
                if (key[i] + lock[i]) > 5:
                    valid_h = False
            if valid_h:
                unique_pairs += 1
    print(unique_pairs)
    return
def main():
    part1()
    return
if __name__ == "__main__":
    main()