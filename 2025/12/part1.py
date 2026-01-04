# The hint for this day was to perform a simple sanity check first to identify the truly impossible regions.
# EG, if the total spaces required to fit all presents is greater than the region's area, it is clearly impossible.
# If this filter is insufficient, I will have to go back to the drawing board.

from math import prod
def parsePresentSizes(filename):
    f = open(filename)
    sizes = dict()
    i = 0
    count = 0
    for line in f:
        if (line == "\n"):
            sizes[i]=count
            count = 0
            i += 1
            continue
        else:
            for c in line:
                if c == "#":
                    count += 1
    sizes[i] = count
    f.close()
    return sizes

def validLine(line, sizes):
    tokens = line.split(": ")
    area = prod([int(x) for x in tokens[0].split("x")])
    presentArea = 0
    i = 0
    for token in tokens[1].split(" "):
        presentArea += int(token)*sizes[i]
        i += 1
    return area >= presentArea

def main(): 
    sizes = parsePresentSizes("inputs/input-blocks.txt")
    for i in range(0, 5):
        print(sizes[i])

    f = open("inputs/input-regions.txt")
    count = 0
    for line in f:
        if validLine(line, sizes):
            count += 1
    f.close()
    print(count)
    return 0

if __name__ == "__main__":
    main()