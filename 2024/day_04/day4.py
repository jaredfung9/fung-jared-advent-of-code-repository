f = open("input4.txt", "r")
lines = []
for line in f:
    lines.append(line)
      
def forward_xmas(row, col, lines):
    if len(lines[0]) - col >= 4:
        return lines[row][col+1] == 'M' and lines[row][col+2] == 'A' and lines[row][col+3] == 'S' 
    else:
        return False
    
def backwards_xmas(row, col, lines):
    if col >= 3:
        return lines[row][col-1] == 'M' and lines[row][col-2] == 'A' and lines[row][col-3] == 'S' 
    else:
        return False

def up_xmas(row, col, lines):
    if row >= 3:
        return lines[row-1][col] == 'M' and lines[row-2][col] == 'A' and lines[row-3][col] == 'S'
    else:
        return False

def down_xmas(row, col, lines):
    if (len(lines) - row) >= 4:
        return lines[row+1][col] == 'M' and lines[row+2][col] == 'A' and lines[row+3][col] == 'S'
    return False

def ne_xmas(row, col, lines):
    if (row >= 3) and (len(lines[0]) - col >= 4):
        return lines[row-1][col+1] == 'M' and lines[row-2][col+2] == 'A' and lines[row-3][col+3] == 'S'
    return False

def nw_xmas(row, col, lines):
    if (row >=3) and (col >= 3):
        return lines[row-1][col-1] == 'M' and lines[row-2][col-2] == 'A' and lines[row-3][col-3] == 'S'
    return False

def se_xmas(row, col, lines):
    if (len(lines)-row >= 4) and (len(lines[0])-col >= 4):
        return lines[row+1][col+1] == 'M' and lines[row+2][col+2] == 'A' and lines[row+3][col+3] == 'S'
    return False

def sw_xmas(row, col, lines):
    if (len(lines)-row >= 4) and (col >= 3):
        return lines[row+1][col-1] == 'M' and lines[row+2][col-2] == 'A' and lines[row+3][col-3] == 'S'
    return False

def XMAS(row, col, lines):
    functions = [up_xmas, down_xmas, forward_xmas, backwards_xmas, ne_xmas, nw_xmas, se_xmas, sw_xmas]
    count = 0
    for function in functions:
        if function(row, col, lines):
            count += 1
    return count

count = 0
for row in range (0, len(lines)):
   for col in range(0, len(lines[0])-1):
       if lines[row][col] == 'X':
           count += XMAS(row,col,lines)

print("XMAS:", count)
           
def valid_a_space(row, col, lines):
    return row >= 1 and len(lines)-1-row >= 1 and col >= 1 and len(lines[0]) - 1 - col >= 1

def valid_nw(row, col, lines):
    nw = lines[row-1][col-1]
    se = lines[row+1][col+1]
    if nw == 'M':
        return se == 'S'
    elif nw == 'S':
        return se == 'M'
    
def valid_ne(row, col, lines):
    ne = lines[row-1][col+1]
    sw = lines[row+1][col-1]
    if ne == 'M':
        return sw == 'S'
    elif ne == 'S':
        return sw == 'M'

def mas(row, col, lines):
    if valid_a_space(row, col, lines):
        return valid_nw(row, col, lines) and valid_ne(row, col, lines)
    
mas_count = 0
for row in range (0, len(lines)):
   for col in range(0, len(lines[0])-1):
       if lines[row][col] == 'A' and mas(row,col,lines):
           mas_count += 1
print("MAS count:", mas_count)