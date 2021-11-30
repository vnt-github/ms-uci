import math
import sys
from typing import Iterator, List, Tuple
import gurobipy as gp
from gurobipy import GRB , Model , Var , tupledict , Constr
from functools import lru_cache
from collections import Counter
import cProfile

is_maximizing = False
best_solution = sys . maxsize
prod = None

constraint_stack : List [ Constr ] = []


def is_integral ( var : Var ) -> bool :
    return var . X . is_integer ()

def is_superior ( solution : float , other : float ) -> bool :
    if is_maximizing :
        return solution > other
    else :
        return solution < other


def is_not_worse ( solution : float , other : float ) -> bool :
    if is_maximizing :
        return solution >= other
    else :
        return solution <= other


def get_xs ( model ) -> Iterator [ Var ]:
    return list ( filter ( lambda v : v . VarName . startswith ('x') , model . getVars() ) )


def bnb (model, x, depth : int, prev : float) -> float :
    global best_solution , constraint_stack, pro
    # print ("Num constraints : ", len( constraint_stack ) )
    # print (" Depth : ", depth )
    if depth >= len ( x ) :
        return best_solution

    # Optimize this node , see what we get
    model . optimize ()

    # Infeasible
    if not hasattr ( model , "objVal") :
        return best_solution

    # Pull out solution
    solution = model . objVal

    # Bound
    if depth > 1 and not is_not_worse ( solution , prev ) :
        return best_solution

    # Integrality
    if all (map ( is_integral , get_xs ( model ) ) ) :
        best_solution = solution
        return best_solution

    # Get first non - integral variable to branch on
    branching_var = next ( v for v in get_xs ( model ) if not is_integral ( v ) )
    value = branching_var . X
    name = branching_var . VarName

    # Branch values
    left_value = math . floor ( value )
    right_value = math . ceil ( value )
    # print ( f" left value : { left_value } , right value : { right_value }")

    # Branch

    # Left child
    constr_name = name + str( depth )
    prod = model . addConstr (model . getVarByName ( name ) <= left_value , constr_name)
    model . update ()
    constraint_stack . append ( model . getConstrByName ( constr_name ) )
    bnb ( model , x , depth + 1 , solution )
    model . remove ( constraint_stack . pop () )

    # print (" Finished going left ")

    # Right child
    pro = model . addConstr (model . getVarByName ( name ) >= right_value ,constr_name)
    model . update ()
    constraint_stack . append ( model . getConstrByName ( constr_name ) )
    bnb ( model , x , depth + 1 , solution )
    model . remove ( constraint_stack . pop () )

    return best_solution



def getPatterns(lengths, limit):
    @lru_cache(None)
    def dp(n):
        if n == 0:
            return [[]]
        
        sub = dp(n-1)
        ans = []
        for l in lengths:
            for each in sub:
                if l not in each:
                    new_sub = [l]+each
                    if sum(new_sub) <= limit:
                        ans.append(new_sub)
        ans += sub
        final = set()
        for each in ans:
            final.add(tuple(sorted(each)))
        return list(list(each) for each in final)

    final = []
    for each in dp(limit):
        leftover = limit-sum(each)
        if leftover < min(list(set(range(1, limit+1)) - set(each))):
            final.append(each)

    return sorted(final, key=lambda x: (len(x), x))

def solve():
    global pro
    try:
        m = gp.Model("Cutting stock")
        m.setParam('OutputFlag', 0)
        N = 15 # number of widths
        M = N # max number

        demands = [1]*N
        columns = getPatterns(list(range(1, N+1)), N)
        for each in columns:
            print(each)
        # NOTE: to include each rool at most once add vtype=GRB.BINARY
        # x = m.addVars(1, len(columns), name="x", vtype=GRB.BINARY)
        # NOTE: to permit each rool to be included more that once remove the vtype=GRB.BINARY
        x = m.addVars(1, len(columns), name="x")
        
        n = m.addVars(len(columns), len(demands))
    
        for c in range(len(columns)):
            ctr = Counter(columns[c])
            for s in range(len(demands)):
                n[c, s] = ctr.get(s+1, 0)

        # for c in range(len(columns)):
        #     for s in range(len(demands)):
        #         print(n[c, s])
        #     print('-'*10)
    
        pro = m.addConstrs((sum(n[c, s]*x[0, c] for c in range(len(columns))) >= demands[s] for s in range(len(demands))))
        m.setObjective(sum(x[0, c] for c in range(len(columns))), GRB.MINIMIZE)
        solution = bnb(m , x , 0 , best_solution )
        print (f"Optimal Solution : { solution }")
        for v in m.getVars():
            if (abs(v.x) > 1e-6):
                print(v.varName, v.x)

        for p in pro:
            if (abs(pro[p].Pi) > 1e-6):
                print(pro[p].ConstrName, pro[p].Pi)

    except gp . GurobiError as e :
        print ('Error code ' + str(e.errno) + ': ' + str(e))
    except AttributeError as e:
        print(e)
        print('Encountered an attribute error')


if __name__ == "__main__":
    # n = 5
    # patterns = getPatterns(list(range(1, n+1)), n)
    # for each in sorted(patterns, key=lambda x: (len(x), x)):
    #     print(each)
    
    # n = 10
    # patterns = getPatterns(list(range(1, n+1)), n)
    # for each in sorted(patterns, key=lambda x: (len(x), x)):
    #     print(each)
    
    # n = 15
    # patterns = getPatterns(list(range(1, n+1)), n)
    # for each in sorted(patterns, key=lambda x: (len(x), x)):
    #     print(each)
    solve()
    # cProfile.run('solve()')