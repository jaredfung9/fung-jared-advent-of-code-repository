# DAY 10
## Observations
* At last, a bit manip problem
* Rep machine state, target state, and buttons as int
* Buttons = bit masks (2,4) -> build by adding first adding (1 << 2) and then (1 << 4)
* To apply a button, XOR current state with button's bitmask.
* TASK: how to find minimum number of inputs to get to target state.
* Considerations, working backwards; start with target state and try each button press; build a tree and use DFS?
* Basically, use BFS? Pass a pair (int curr_state, int64_t button_presses) into a queue. If curr_state = 0, return button_presses. Otherwise, increment button_presses by 1 and try all buttons again.
* Init BFS is a queue containing (curr_state w/ 1 button, 1) for every button in the list.

## File Processing
* Maybe regex?
* Write a separate cpp. Treat everything as strings and push to vector
* vector[0] = machine state
* vector[END] = joltages
* everything else = buttons
* Then use sed to process each individual file
* Maybe easier just to not do any preprocessing and treat each as a token.
* '[' indicates process machine state -> int
* '(' indicates process button -> bitmask
* '{' indicates joltage req [IGNORED FOR PART 1; use as the terminator for the machine]

## PART 2 OBSERVATIONS
* Very similar to part 1, except we can no longer use bits, need to track each individual integer?
* Part 1's solution is infeasible for part 2, each stage will grow the buffer by N
* Just to solve the first machine, took 4.6mil button presses. Clearly we need to cull some of these branches.
## BRAINSTORMING
* Instead of simulating every button press, maybe we need to convert the problem to a system of linear equations.
* A Python library would work well here
## RESEARCH
* This is a linear algebra problem with multiple solutions
* We want to find the minimum solution
* Further research: Z3-solver
* Linear Programming
* Simplex Algorithms
* LPP solvers

# WRITE-UP ON PART 2
Part 2 really stumped me and it sounds like the go-to option for this style of problem was Linear Programming, specifically Integer Linear Programming.
## Observations
* The first thing I noticed was that attempting to simulate each button press quickly ran out of control for even the simplest inputs.
* The second thing I noticed was that the problem was very similar to a system of linear equations.
* We can express the target joltages as a single vector J, where j_k represents the target voltage of each terminal.
* For example, {3,5,4,7} has 4 terminals, with j_0 needing to hit 3, j_1 needing to hit 5, and so on.
* The other thing I noticed was that the order of button presses didn't matter. This meant that pressing button 0, then button 1, then button 0 again could be expressed as a vector B [2,1] where b_k represented the number of times a given button was pressed.
* Using this, we could build an NxM coefficient matrix, where N := # of terminals and M := # of buttons. For each tile, (row, col), is 1 iff the terminal represented by row is incremented when the button represented by col is pressed. For the demo input we would end up with a coefficient matrix of 4x6 looking something like this:
    0 0 0 0 1 1
    0 1 0 0 0 1
    0 0 1 1 1 0
    1 1 0 1 0 0
* We can quickly notice that solving this with Gaussian elimination that we are left with free variables.
* Another solution I saw used GE to identify additional constraints and the free variables, then brute forced the free variables until they reached a solution.
## Constraints
1. We have N equations representing the final joltage each terminal needs to be at.
1. All M buttons (inputs) must be non-negative integers.
1. We want to minimize the sum of all inputs.

## Z3-Solver
* https://github.com/Z3Prover/z3
* https://z3prover.github.io/papers/programmingz3.html