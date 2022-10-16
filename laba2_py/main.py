import numpy as np
from numpy import linalg as LA
import math


def printMatrix(n):
    H = [[None for _ in range(n)] for __ in range(n)]
 
    for i in range(n):
        for j in range(n):
            # using the formula to generate
            # hilbert matrix
            H[i][j] = 1 / ((i + 1) + (j + 1) - 1)
 
    return H



# 12+3
print(LA.cond(printMatrix(12+3)))