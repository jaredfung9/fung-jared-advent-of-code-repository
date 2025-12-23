#https://topaz.github.io/paste/#XQAAAQDPBAAAAAAAAAAzHIoib6rV29ThgSH/UljQcDfAA8q7i6qPvi6J5rxVjcFH+YB5bFDayX9SVEm5DLolFCht3qp0OoV8O4iJEpCKpJA7kvAb9VCnGKeNQQH8nSkhm+cBhHHV5tPGU92+LxzEej3ZGSFk3lafp+ilSBie9I4xWv0K2SI/qcAnuiUPz3Og4KgTNcYGuBCyNo0iHas/lnSKp11BxOj5Ikn3hmBpSwTYsOZBKKbhyu4AoPAhbx1JIuVJIVyfrkQ3gIKiP5OQcOBMjjE/+FhU+ONABIY8mmQvHrs7y46ieOkPbMLAkS39zMEgcPa3qj0HREfwle1uqSHMgwLioeUoqAX3o+W/rwii1/POi6B64ke2aTa+Pu9JDQchRzQj/UPtEiKCg7FLSN5P8s8VNEDiC2zNLn9jekmDnW9A7qrNkbXjkkE9aeR3dBxaX1EnxzGsF0koLf5+CWxxM59seNwVVAdnSX5J8VsNqH2C9XI2sbKGN/w1IfTSk2EW9MBHsVnnxxAz/ANB4kNe7hz6nldot39oPJBOCPFp2hA1Yox4AluAjnbuTZugxYL22JTu2eAZlkI/WJxYMXELXQD35SuGCf20ZH4QetUqOgOOyfWB04A/uu6C7/9VSDpjDszFBhWVsaHIiHEy2t3Vg0KUJTN8g033K5eZLzOST8qcl0/22dFV7UVisZSdmYqACS70PsZCeaCWHMU8L3NMvFtuFHuOCNJaiZhPhgUedlLyiUuZK8MVGx1/E2fJo1HA5VOqaJUZGLA/9mPfDILCmW8lsO/g80SmQqV0DvzTCTrgpudgVLJyYw8C5dtjdSZOScqVGftbVPT/E7rIAA==
from z3 import Int, Optimize, sat

def solve_buttons(target, buttons):
    n = len(target)
    m = len(buttons)
    # Convert button definitions into coefficient matrix B[i][j]
    B = [[0]*m for _ in range(n)]
    for j, btn in enumerate(buttons):
        for i in btn:
            B[i][j] += 1
    # Z3 integer variables: x_j = number of presses of button j
    x = [Int(f"x_{j}") for j in range(m)]                           # Can combine list comprehension with text-variable
    opt = Optimize()                                                # Z3 optimize-solver
    # Variables must be nonnegative integers
    for j in range(m):
        opt.add(x[j] >= 0)                                          # Adding constraints
    # Constraints: B * x = target
    for i in range(n):
        opt.add(sum(B[i][j] * x[j] for j in range(m)) == target[i]) # Adding constraints: Basically iterating through each terminal's formula and adding the corresponding variable
    # Objective: minimize total presses
    opt.minimize(sum(x))                                            # Want to minimize the sum of our button presses
    if opt.check() != sat:                                          # Optimize.check() (or model.check()) returns whether or not the set of constraints is satisfable.
        print("No solution")
        return None
    mod = opt.model()                                               # If the current Solver is satisifable, Optimize.model() returns the current inputs which satisfies the model's constraints.
    solution = [mod[x[j]].as_long() for j in range(m)]              # Extracting each button presses into a list to return
    return solution

def part2():
    res = 0
    with open("input2.txt") as f:
        for line in f:
            tokens = line.split()
            buttons = [eval(f'[{b.strip("()")}]') for b in tokens[1:-1]]
            target = eval(f'[{tokens[-1].strip("{}")}]')
            res += sum(solve_buttons(target, buttons))
    print(res)

if __name__ == "__main__":
    part2()
