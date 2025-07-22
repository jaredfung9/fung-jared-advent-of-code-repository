neighbors = None
def get_neighbors(filename):
    global neighbors
    neighbors = dict()
    f = open(filename, "r")
    for line in f:
        pair = line.strip().split('-')
        a,b = pair

        if a not in neighbors:
            neighbors[a] = {b}
        else:
            neighbors[a].add(b)
        if b not in neighbors:
            neighbors[b] = {a}
        else:
            neighbors[b].add(a)
    f.close()
    for key in neighbors:
        neighbors[key] = sorted(neighbors[key])
    return neighbors

def vertex_set():
    global neighbors
    return neighbors.keys()

def get_sets(neighbors):
    all_sets = set()
    for a in neighbors:
        for b in neighbors[a]:
            for c in neighbors[b]:
                if (c in neighbors[a]):
                    _set = [a,b,c]
                    _set.sort()
                    all_sets.add((_set[0], _set[1], _set[2]))
    return all_sets

def identify_t_in_sets(sets):
    positive = set()
    for _set in sets:
        for pc in _set:
            if pc[0] == 't':
                positive.add(_set)
    return positive

def part1():
    print("PART 1:")
    real = "input.txt"
    demo = "demo.txt"
    input = real
    neighbors = get_neighbors(input)
    all_sets = get_sets(neighbors)
    print(len(identify_t_in_sets(all_sets)))
    return

def intersect(A, B):
    l = []
    for x in A:
        if x in B:
            l.append(x)
    return l

def complement(A,B):
    l = []
    for x in A:
        if x not in B:
            l.append(x)
    return l

def select_pivot(P):
    global neighbors
    pivot = None
    len_pivot = 0
    for v in P:
        if len(neighbors[v]) > len_pivot:
            pivot = v
            len_pivor = len(neighbors[v])
            
def BronKerbosch(P, R=[], X=[]):
    global neighbors
    if (len(P) <= 0) and (len(X) <= 0):
        R.sort()
        yield R
        return
    for v in P:
        _R = [] + R + [v]
        _P = intersect(P, neighbors[v])
        _X = intersect(X, neighbors[v])
        yield from BronKerbosch(_P, _R, _X)
        P = complement(P, v)
        X = X + [v]

def part2():
    print("PART 2:")
    real = "input.txt"
    demo = "demo.txt"
    input = real
    neighbors = get_neighbors(input)
    #print(list(vertex_set()))
    print("Finding best clique.")
    best_clique = None
    best_clique_len = 0
    best_clique_gen = BronKerbosch(list(vertex_set()))
    for clique in best_clique_gen:
        if len(clique) > best_clique_len:
            best_clique_len = len(clique)
            best_clique = clique
    
    for word in best_clique:
        print(word,end=',')
    return
def main():
    #part1()
    part2()
if __name__ == "__main__":
    main()