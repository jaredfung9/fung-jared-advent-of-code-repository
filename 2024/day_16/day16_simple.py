from heapq import heappop, heappush
def read_input(lines):
    grid = []
    line = 0
    for line in lines:
        grid.append(list(line))
    
    s,e = None,None
    for r, row in enumerate(grid):
        for c, ch in enumerate(row):
            if ch == "S":
                s = (r,c)
            elif ch == "E":
                e = (r,c)
    return grid, s, e
def dijkstra(grid, starts):
    delta = {"E":(0,1), "W":(0,-1), "N":(-1,0), "S":(1,0)}

    dist = {}
    pq = []
    for sr, sc, dir in starts:
        dist[(sr, sc, dir)] = 0
        heappush(pq, (0, sr, sc, dir))
    
    while pq:
        (d, row, col, dir) = heappop(pq)
        if dist[(row,col,dir)] < d:
            continue
        for next_dir in "NESW".replace(dir,""):
            if (row, col, next_dir) not in dist or dist[(row,col,next_dir)] > d + 1000:
                dist[(row,col,next_dir)] = d + 1000
                heappush(pq, (d+1000,row,col,next_dir))
        dr, dc = delta[dir]
        next_r, next_c = row + dr, col + dc
        if (
            0 <= next_r < len(grid)
            and 0 <= next_c < len(grid[0])
            and grid[next_r][next_c] != "#"
            and (
                (next_r, next_c, dir) not in dist
                or dist[(next_r, next_c, dir)] > d + 1
            )
        ):
            dist[(next_r, next_c, dir)] = d + 1
            heappush(pq, (d+1, next_r, next_c, dir))
    return dist
def part1():
    demo1 = "demomap.txt"
    demo2 = "demomap2.txt"
    real = "input.txt"
    input = real
    best = 1e9
    f = open(input, "r")
    grid,s,e = read_input(f.readlines())
    f.close()

    (sr,sc), (er, ec) = s,e
    dist = dijkstra(grid, [(sr, sc, "E")])
    for dir in "NESW":
        if (er, ec, dir) in dist:
            best = min(best, dist[(er, ec, dir)])
    return best
def part2():
    demo1 = "demomap.txt"
    demo2 = "demomap2.txt"
    real = "input.txt"
    input = real
    best = 1e9
    f = open(input, "r")
    grid,s,e = read_input(f.readlines())
    f.close()

    (sr, sc), (er, ec) = s,e
    from_start = dijkstra(grid, [(sr,sc,"E")])
    from_end = dijkstra(grid, [(er,ec,d) for d in "EWNS"])
    optimal = part1()

    inverted = {"E":"W", "W":"E", "N":"S", "S":"N"}
    result = set()

    for row in range(len(grid)):
        for col in range(len(grid[0])):
            for dir in "NESW":
                state_from_start = (row, col, dir)
                state_from_end = (row, col, inverted[dir])
                if state_from_start not in from_start:
                    continue
                elif state_from_end not in from_end:
                    continue
                
                path_score = from_start[state_from_start] + from_end[state_from_end]
                if path_score == optimal:
                    result.add((row,col))
    return len(result)
print(part1())
print(part2())


    