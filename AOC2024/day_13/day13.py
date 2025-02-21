import numpy as np
import sympy as sp
import re

#print(sp.Matrix([[94,22,8400],[34,67,5400]]).rref())


def build_matrix(file):
    p = re.compile(r'\d+')
    line = next(file)
    if line == '\n':
        line = next(file)
    A_button_input = [int(x) for x in p.findall(line)]
    B_button_input = [int(x) for x in p.findall(next(file))]
    Prize_input = [int(x) for x in p.findall(next(file))]
    matrix = sp.Matrix([[A_button_input[0], B_button_input[0], 10000000000000 + Prize_input[0]], [A_button_input[1], B_button_input[1], 10000000000000 + Prize_input[1]]])
    return matrix

f = open("input.txt", "r")
cost = 0
matrix = build_matrix(f).rref()[0]
while matrix:
    if(type(matrix[2]) == sp.Integer):
        results = matrix.col(2)
        cost += 3*results[0] + results[1]
    try:
        matrix = build_matrix(f).rref()[0]
    except StopIteration as e:
        break
print(cost)
f.close()