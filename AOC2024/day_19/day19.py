def parse_input(filename):
    substrings = []
    f = open(filename, "r")
    substrings = [substr for substr in f.readline().strip().split(", ")]
    f.readline()
    return substrings, f

def composable(string, substrings, compose_dict):
    if len(string) <= 0:
        return False
    if len(string) == 1:
        if compose_dict.get(string) is None:
            compose_dict[string] = False
        return compose_dict[string]
    if compose_dict.get(string):
        return True
    for i in range(1, len(string)):
        substr1, substr2 = string[:i], string[i:]
        if compose_dict.get(substr1) is None:
            compose_dict[substr1] = composable(substr1, substrings, compose_dict)
        if compose_dict.get(substr2) is None:
            compose_dict[substr2] = composable(substr2, substrings, compose_dict)
        if compose_dict[substr1] and compose_dict[substr2]:
            compose_dict[string] = True
            return True
    compose_dict[string] = False
    return False

def create_perm_dict(substrings):
    perm_dict = {}
    for substr in substrings:
        temp_list = substrings.copy()
        temp_list.remove(substr)
        perm_dict[substr] = permutations(substr, temp_list, perm_dict)
        perm_dict[substr] += 1
    return perm_dict

def permutations(string, substrings, perm_dict):
    if len(string) <= 0:
        return 1
    if perm_dict.get(string):
        return perm_dict[string]
    count = 0
    for i in range(1, len(string)+1):
        substr1, substr2 = string[:i], string[i:]
        if substr1 in substrings:
            count += permutations(substr2, substrings, perm_dict)
    perm_dict[string] = count
    return count

def main():
    demo = "demo_in.txt"
    real = "input.txt"
    input = real

    substr_list, f = parse_input(input)
    compose_dict = {string : True for string in substr_list} 
    #perm_dict = create_perm_dict(substr_list)
    perm_dict = {}
    comp_count, perm_count = 0,0
    for line in f:
        string = line.strip()
        if composable(string, substr_list, compose_dict):
            comp_count += 1
            perm_count += permutations(string, substr_list, perm_dict)
    print("POSSIBLE:", comp_count)
    print("PERMUTATIONS:", perm_count)

def test():
    substr_list = ["r", "g", "rg", "w", "rgw", "rgrg"]
    target = "rgw"
    perm_dict = create_perm_dict(substr_list)
    for key in perm_dict:
        print(key, perm_dict[key])
if __name__ == "__main__":
    #test()
    main()