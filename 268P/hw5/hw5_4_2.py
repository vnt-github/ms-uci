import math
import sys
from typing import Iterator, List, Tuple
import gurobipy as gp
from gurobipy import GRB , Model , Var , tupledict , Constr
from functools import lru_cache
from collections import Counter
import cProfile

def getInitialColumns(lengths, L):
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

def addNewColumn(n, model, lengths, N, L, columns, dual):
    sub = gp.Model("Knapsack")
    x = sub.addVars(1, N, vtype=GRB.INTEGER)
    sub_pi = sub.addVars(1, N)
    # for i in range(L):
    #     sum_yet = 0
    #     for j in range(len(columns)):
    #         sum_yet += n[j, i]
    #     sub_pi[0, i] = sum_yet
    for i in range(len(dual)):
        sub_pi[0, i] = dual[i]

    sub.addConstr((sum(x[0, s]*lengths[s] for s in range(len(lengths))) <= L))
    sub.setObjective(sum(-sub_pi[0, s]*x[0, s] for s in range(len(lengths))), GRB.MINIMIZE )
    sub.write('sub_knapsack.lp')
    sub.optimize()
    new_column = []
    for v in sub.getVars():
        if (abs(v.x) > 1e-6):
            print(v.varName, v.x)
            new_column.append(v.x)
    return new_column

def solve():
    try:
        m = gp.Model("Cutting stock")
        m.setParam('OutputFlag', 0)
        N = 5 # number of widths
        M = N # max number
        L = 110

        demands = [48, 8, 10, 24, 35]
        lengths = [20, 75, 55, 50, 45]
        columns = getInitialColumns(lengths, L)
        for each in columns:
            print(each)
        # NOTE: to include each rool at most once add vtype=GRB.BINARY
        # x = m.addVars(1, len(columns), name="x", vtype=GRB.BINARY)
        # NOTE: to permit each rool to be included more that once remove the vtype=GRB.BINARY
        x = m.addVars(1, len(columns), name="x")
        n = m.addVars(len(columns), len(demands))
    
        for c in range(len(columns)):
            for s in range(len(demands)):
                n[c, s] = columns[c][s]

        for c in range(len(columns)):
            for s in range(len(demands)):
                print(n[c, s])
            print('-'*10)
    
        pro = m.addConstrs((sum(n[c, s]*x[0, c] for c in range(len(columns))) >= demands[s] for s in range(len(demands))))
        m.setObjective(sum(x[0, c] for c in range(len(columns))), GRB.MINIMIZE)
        solution = getSolution(m)
        
        dual = []
        for p in pro:
            if (abs(pro[p].Pi) > 1e-6):
                print(pro[p].Pi)
                dual.append(pro[p].Pi)
        while addNewColumn(n, m, lengths, N, L, columns, dual):
            solution = getSolution(m)
        print(solution)
        print (f"Optimal Solution : { solution }")
    
    except gp . GurobiError as e :
        print ('Error code ' + str(e.errno) + ': ' + str(e))
    except AttributeError as e:
        print(e)
        print('Encountered an attribute error')


if __name__ == "__main__":
    solve()
    # cProfile.run('solve()')