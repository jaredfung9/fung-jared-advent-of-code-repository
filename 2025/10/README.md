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