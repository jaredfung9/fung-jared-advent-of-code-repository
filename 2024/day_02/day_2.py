def increasing_comp(x, y):
    return x < y
def decreasing_comp(x, y):
    return x > y

def valid_difference(x,y):
    diff = abs(x - y)
    return (diff == 1) or (diff == 2) or (diff == 3)

def is_safe_report(tokens):
    comparator = decreasing_comp
    if int(tokens[0]) < int(tokens[1]):
        comparator = increasing_comp
    previous_seen = None
    for token in tokens:
        token = int(token)
        if previous_seen == None:
            previous_seen = token
            continue
        if (not comparator(previous_seen, token)) or (not valid_difference(previous_seen, token)):
            return False
        previous_seen = token
    return True

def problem_dampener(tokens, dampener):
    if not dampener:
        return is_safe_report(tokens)
    if not is_safe_report(tokens):
        i = 0
        while (i < len(tokens)):
            candidate_tokens = tokens.copy()
            candidate_tokens.pop(i)
            if is_safe_report(candidate_tokens):
                return True
            i += 1
        return False
    return True

def count_safe_reports(file, dampener=False):
    safe_reports = 0
    f = file
    for report in f:
        tokens = report.split(" ")
        if problem_dampener(tokens, dampener):
            safe_reports += 1
    f.close()
    return safe_reports

f = open("input2.txt", "r")
print(count_safe_reports(f, True))
f.close()