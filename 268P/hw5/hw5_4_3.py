import math
import sys
from typing import Iterator, List, Tuple
import gurobipy as gp
from gurobipy import GRB , Model , Var , tupledict , Constr
from functools import lru_cache
from collections import Counter
import cProfile

# dual = None
# demands = [48, 8, 10, 24, 35]
# lengths = [20, 75, 55, 50, 45]
# N = 5 # number of widths
# M = N # max number
# L = 110


# demands = [25, 20, 18]
# lengths = [3, 6, 7]
# N = 3 # number of widths
# M = N # max number
# L = 16

N = 15
demands = [1]*N
lengths = list(range(1, N+1))
M = N
L = N

def getInitialColumns(L):
    columns = [[0 for _ in range(len(lengths))] for _ in range(len(lengths))]
    for i in range(len(lengths)):
        columns[i][i] = math.floor(L/lengths[i])
    return columns

def getSolution(model):
    model.optimize()
    if not hasattr(model, 'objVal'):
        return None
    solution = model.objVal
    return solution

def getReducedCost(new_column):
    global dual
    reduced_cost = 0
    for i in range(len(dual)):
        reduced_cost += dual[i]*new_column[i]
    return 1-reduced_cost

def addNewColumn(N, L):
    global dual
    sub = gp.Model("Knapsack")
    x = sub.addVars(1, N, vtype=GRB.INTEGER)
    sub_pi = sub.addVars(1, N)
    for i in range(len(dual)):
        sub_pi[0, i] = dual[i]

    sub.addConstr((sum(x[0, s]*lengths[s] for s in range(len(lengths))) <= L))
    sub.setObjective(sum(sub_pi[0, s]*x[0, s] for s in range(len(lengths))), GRB.MAXIMIZE )
    sub.write('sub_knapsack.lp')
    sub.optimize()
    new_column = []
    for i in range(N):
        new_column.append(int(math.ceil(x[0, i].X)))
    return new_column

def solveModel(columns):
    global dual
    m = gp.Model("Cutting stock")
    # m.setParam('OutputFlag', 0)

    # NOTE: to include each rool at most once add vtype=GRB.BINARY
    # x = m.addVars(1, len(columns), name="x", vtype=GRB.BINARY)
    # NOTE: to permit each rool to be included more that once remove the vtype=GRB.BINARY
    x = m.addVars(1, len(columns), name="x")
    n = m.addVars(len(columns), len(demands))
    for c in range(len(columns)):
        for s in range(len(demands)):
            n[c, s] = columns[c][s]
    
    # for c in range(len(columns)):
    #     for s in range(len(demands)):
    #         print(n[c, s])
    #     print('-'*10)

    pro = m.addConstrs((sum(n[c, s]*x[0, c] for c in range(len(columns))) == demands[s] for s in range(len(demands))))
    m.setObjective(sum(x[0, c] for c in range(len(columns))), GRB.MINIMIZE)
    solution = getSolution(m)
    dual = []
    for p in pro:
        # print(pro[p].Pi)
        dual.append(pro[p].Pi)
    return solution

def solve():
    global dual
    try:
        m = gp.Model("Cutting stock")

        columns = getInitialColumns(L)
        # for each in columns:
        #     print(each)
    
        # NOTE: this is do;
        solution = solveModel(columns)
        new_column = addNewColumn(N, L)
        reduced_cost = getReducedCost(new_column)
        while reduced_cost < 0:
            columns.append(new_column)
            solution = solveModel(columns)
            new_column = addNewColumn(N, L)
            reduced_cost = getReducedCost(new_column)
        
        solution = math.ceil(solution)
        print(solution)
        print (f"Optimal Solution : { solution }")
    
    except gp . GurobiError as e :
        print ('Error code ' + str(e.errno) + ': ' + str(e))
    except AttributeError as e:
        print(e)
        print('Encountered an attribute error')


if __name__ == "__main__":
    # solve()
    cProfile.run('solve()')