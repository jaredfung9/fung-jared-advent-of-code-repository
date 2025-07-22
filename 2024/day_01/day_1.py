from heapq import heapify, heappop

def get_lists(filename, separator):
    f = open(filename, 'r', encoding="utf-8")
    l1, l2 = [], []
    for line in f:
        line = line.replace('\n', '')
        pair = line.split(separator)
        l1.append(pair[0])
        l2.append(pair[1])
    f.close()
    return [l1, l2]

def get_dist_diff(l1, l2):
    heapify(l1)
    heapify(l2)

    difference = 0
    while (l1 and l2):
        difference += abs(int(heappop(l1)) - int(heappop(l2)))
    return difference

def calculate_simularity_score(l1, l2):
    freq = {}
    for entry_in_2 in l2:
        if (entry_in_2 not in freq):
            freq[entry_in_2] = 1
        else:
            freq[entry_in_2] += 1
    
    sim_score = 0
    for entry_in_1 in l1:
        if entry_in_1 not in freq:
            continue
        sim_score += freq[entry_in_1]*int(entry_in_1)
    return sim_score

l1,l2 = get_lists("input_1.txt", "   ")
print("Distance difference: " + str(get_dist_diff(l1,l2)))

l1,l2 = get_lists("demo_input_1.txt", "   ")
print("sim_score: " + str(calculate_simularity_score(l1,l2)))

