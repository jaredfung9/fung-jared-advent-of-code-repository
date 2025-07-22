from sys import getsizeof
_blink_cache = dict()
# Given a stone's value, returns a list with the resulting stones created from blinking at the input stone.
def blink_at(val):
    val_str = (str(val))
    if val == 0:
        return [1]
    elif ((len(val_str) % 2) == 0):
        midpoint = int(len(val_str) / 2)
        return [int(val_str[:midpoint]), int(val_str[midpoint:])]
    else:
        return [val * 2024]

def recursive_blink(val, remaining_blinks):
    if (val, remaining_blinks) in _blink_cache:
        return _blink_cache[(val, remaining_blinks)]
    
    resulting_stones = blink_at(val)
    if remaining_blinks == 1:
        return len(resulting_stones)
    else:
        sum = 0
        for stone in resulting_stones:
            sum += recursive_blink(stone, remaining_blinks - 1)
    _blink_cache[(val, remaining_blinks)] = sum
    return sum

def part1():
    filename = "input.txt"
    f = open(filename, "r")
    line = f.read().replace("\n", "")
    tokens = iter(list(map(lambda x:int(x),line.split(" "))))
    
    count = 0
    for token in tokens:
        count += recursive_blink(token, 75)
    print("PART 1:", count)
part1()