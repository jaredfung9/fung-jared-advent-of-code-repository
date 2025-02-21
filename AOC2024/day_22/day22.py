from collections import deque
def next_secret(s):
    salt = 16777216
    s_prime = (s % salt) ^ ((64*s) % salt)
    s_prime2 = (s_prime % salt) ^ ((s_prime // 32) % salt)
    s_prime3 = ((s_prime2 * 2048) % salt) ^ (s_prime2 % salt)
    return s_prime3

def get_price_sequence(s, n=2000):
    prev_price = int(s) % 10
    price_list = [(prev_price, None)]
    for i in range(n):
        s = next_secret(s)
        next_price = s % 10
        delta = next_price - prev_price
        price_list.append((delta, next_price))
        prev_price = next_price
    return price_list

def generate_price_lists(filename):
    sellers = []
    inputs = read_input(filename)
    for input in inputs:
        sellers.append(get_price_sequence(int(input)))
    return sellers

def get_price_map(s, n=2000):
    prev_price = int(s) % 10
    sequence = deque()
    price_map = dict()
    # initialize sequence by reading processing the first 4 secrets
    for i in range(4):
        s = next_secret(s)
        next_price = s % 10
        sequence.append((next_price - prev_price))
        prev_price = next_price
    
    price_map[(sequence[0],sequence[1],sequence[2],sequence[3])] = next_price
    for i in range(n-2):
        s = next_secret(s)
        next_price = s % 10
        sequence.popleft()
        sequence.append((next_price - prev_price))
        prev_price = next_price
        key = (sequence[0], sequence[1], sequence[2], sequence[3])
        if key not in price_map:
            price_map[key] = next_price
    return price_map

def generate_price_maps(filename):
    sellers = []
    inputs = read_input(filename)
    for input in inputs:
        sellers.append(get_price_map(int(input)))
    return sellers

def read_input(filename):
    f = open(filename, "r")
    l = f.readlines()
    f.close()
    return [x.strip() for x in l]

def part1():
    print("PART 1:")
    demo = "demo.txt"
    real = "input.txt"
    input = real
    
    total = 0
    inputs = read_input(input)
    for _input in inputs:
        s = int(_input)
        for _ in range(2000):
            s = next_secret(s)
        total += s
    print(total)
    return

def match(seq, l, tail):
    i = 0
    while i < len(seq):
        l_index = tail - i
        seq_index = len(seq) - i -1
        a = int(l[l_index][0])
        b = int(seq[seq_index])
        if a != int(seq[seq_index]):
            return False
        i += 1
    return True

def boyer_moore(seq, l):
    seq_end = len(seq) - 1
    i = seq_end # begin looking at the ith index into list
    while i < len(l):
        tail = l[i][0]
        if tail != seq[seq_end]:
            if tail not in seq:
                i += len(seq)
            else:
                i += 1
        else:
            if match(seq, l, i):
                return l[i][1]
            else:
                i += 1
    return None
def part2():
    demo = "demo2.txt"
    real = "input.txt"
    input = real

    price_lists = generate_price_maps(input)
    best_total = 0
    best_sequence = None
    
    keys = set()
    for seller in price_lists:
        for key in seller.keys():
            keys.add(key)
    
    for key in keys:
        seq = key
        total = 0
        for seller in price_lists:
            total += seller.get(key, 0)
        if total >= best_total:
            best_total = total
            best_sequence = seq
        
    print(best_total)
    return
def main():
    #part1()
    part2()
if __name__ == "__main__":
    main()