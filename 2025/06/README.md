# 2025 DAY 06
## Input:
Rows of numbers
Single row of operations indicating which operation to apply across the entire column.
First thing: Can split the input into numbers and operations.
Then, build a matrix and transpose it.

## Straightforward Solution - Space Inefficient
* Let's try to just read EVERYTHING into memory. (Aside: if the dataset was larger than memory, I would then attempt to convert the dataset into matrix blocks and then perform matrix transposition to rearrange the inputs into rows that are easily accessible individually.

## Minor analysis
* We only have four rows, let's just read them into four vectors and iterate forward (if order doesn't matter, stack also works and we pop)

## Debugging missing pops
* Pops are not aligned with accesses
Sample output:
5 5 4 =401
4 4 3 =302
3 3 2 =1934226
2 2 1 =398
1 1 =168
=1
=0
* suspecting that stacks are improperly allocated.
Order of accesses:  
5 0x63a19abb54f0
5 0x63a19abb57e0
4 0x63a19abb5ae0
4 0x63a19abb54f0
4 0x63a19abb57e0
3 0x63a19abb5ae0
3 0x63a19abb54f0
3 0x63a19abb57e0
2 0x63a19abb5ae0
2 0x63a19abb54f0
2 0x63a19abb57e0
1 0x63a19abb5ae0
1 0x63a19abb54f0
1 0x63a19abb57e0

* Looks like stacks are being improperly built? 5 5 4
* Each stack should have 4 items
* suspecting that it's pushing the newlines to the stack
* main issue is input is not being read correctly
* double adding last element? seems like EOF check is not working how I expected
* maybe getline isn't reading in an EOF to the istringstream
* needed to use (buffer_stream >> x) as the while condition