import numpy as np
import math


def gilbert(n):
    matrix=[[]]*n
    for i in range(n):
        for j in range(n):
            el = math.pow((i+j+1),-1)
            matrix[i].append(el)
    return matrix


print(np.cond(gilbert(7)))