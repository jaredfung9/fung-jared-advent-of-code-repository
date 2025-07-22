import re

def match_muls(file):
    f = file
    total = 0
    for line in f:
        matches = re.findall("mul[(][0-9]+,[0-9]+[)]", line)
        for match in matches:
            cleaned_match = match.replace("mul(", "").replace(")","")
            tokens = cleaned_match.split(",")
            total += int(tokens[0]) * int(tokens[1])
    print(total)

def conditional_mul(file):
    f = file
    total = 0
    queue = []
    conditional = True
    for line in f:
        matches = re.findall("mul[(][0-9]+,[0-9]+[)]|do[(][)]|don[']t[(][)]", line)
        for match in matches:
            queue.append(match)
    for command in queue:
        if command == "do()":
            conditional = True
        elif command == "don't()":
            conditional = False
        elif conditional:
            cleaned_match = command.replace("mul(", "").replace(")","")
            tokens = cleaned_match.split(",")
            total += int(tokens[0]) * int(tokens[1])
    print(total)

f = open("input3.txt", "r")
conditional_mul(f)
f.close()

