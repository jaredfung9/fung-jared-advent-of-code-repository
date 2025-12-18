# 2025 DAY 06
## Input:
Rows of numbers
Single row of operations indicating which operation to apply across the entire column.
First thing: Can split the input into numbers and operations.
Then, build a matrix and transpose it.

## Straightforward Solution - Space Inefficient
* Let's try to just read EVERYTHING into memory. (Aside: if the dataset was larger than memory, I would then attempt to convert the dataset into matrix blocks and then perform matrix transposition to rearrange the inputs into rows that are easily accessible individually.
