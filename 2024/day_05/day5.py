
""" Given a properly formatted rules file, returns a dictionary of lists containing the first number of rules where the key is the second number in the pair.
    This list represents all pages that must be placed in the manual first."""
def process_rules(rules_file):
    rule_hashmap = {}
    for rule in rules_file:
        rule = rule.replace("\n","")
        predecessor, key = rule.split("|")
        predecessor, key = int(predecessor), int(key)

        if key not in rule_hashmap:
            new_list = [predecessor]
            rule_hashmap[key] = new_list
        else:
            rule_hashmap[key].append(predecessor)
    return rule_hashmap

def process_updates(updates_file):
    master_list = []
    for update in updates_file:
        update = update.replace("\n", "")
        pages = update.split(",")
        master_list.append([int(page) for page in pages])
    return master_list

"""BIT STUFF"""
""" Given a bitstring, returns the nth bit"""
def get_bit(bitstring, n):
    return bitstring&(1 << n)
""" Given a bitstring and x, returns a bitstring where the nth bit to be equal to 1 (and all other bits are the same)
    Returns the same bitstring if the nth bit is already set."""
def set_bit(bitstring, n):
    if (not get_bit(bitstring, n)):
        return bitstring+(1<<n)
    return bitstring
# sets bitstring's nth bit to zero
def unset_bit(bitstring, n):
    if (get_bit(bitstring, n)):
        return bitstring-(1<<n)
    return bitstring
"""----------------------------------------------"""

""" Returns true iff the bitstring satisfies the given a list of constraints (predecessors that must be seen)"""
def valid_insertion(constraints, bitstring):
    for prereq in constraints:
        if not get_bit(bitstring, prereq):
            return False
    return True

""" Returns a list numbers where numbers appear in both rules_list and pages"""
def get_relevant_rules(prereq_list, pages):
    relevant = []
    for page in pages:
        if page in prereq_list:
            relevant.append(page)
    return relevant

""" Given a list of pages, manual bitstring, sorted_dict, and pagelist, attempts to insert the nth page into the manual"""
def insert_page(n, manual_bitstring, sorted_dict, pagelist):
    if n not in sorted_dict:
        return set_bit(manual_bitstring, n)
    relevant_rules = get_relevant_rules(sorted_dict[n], pagelist)
    if valid_insertion(relevant_rules, manual_bitstring):
        return set_bit(manual_bitstring, n)
    else:
        return None

""" Attempts to construct a manual. Returns True iff the update_list is valid."""
def valid_manual(sorted_dict, update_list):
    bitstring = 0
    for page in update_list:
        bitstring = insert_page(page, bitstring, sorted_dict, update_list)
        if not bitstring:
            return False
    return True

def fix_manual(update, dict):
    page_rule_pairs = []
    for page in update:
        pair = (page, 0)
        if page in dict:
            pair = (page, len(get_relevant_rules(dict[page], update)))
        page_rule_pairs.append(pair)

    page_rule_pairs.sort(key=lambda pair : pair[1])
    return [pair[0] for pair in page_rule_pairs]
    
def help_elves():
    rules = open("input5_rules.txt", "r")
    updates = open("input5_updates.txt", "r")
    sorted_rules = process_rules(rules)
    master_updates_list = process_updates(updates)
    rules.close()
    updates.close()

    total = 0
    fix_total = 0
    for update_list in master_updates_list:
        if valid_manual(sorted_rules, update_list):
            total += update_list[len(update_list)//2]
        else:
            fixed = fix_manual(update_list, sorted_rules)
            fix_total += fixed[len(fixed)//2]
    print("Valid manual middle # total:", total)
    print("Fixed manual middle # total:", fix_total)
    
help_elves()