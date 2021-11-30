import math
import sys
from typing import Iterator, List, Tuple
import gurobipy as gp
from gurobipy import GRB , Model , Var , tupledict , Constr
is_maximizing = False
best_solution = sys . maxsize

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
    global best_solution , constraint_stack
    print ("Num constraints : ", len( constraint_stack ) )
    print (" Depth : ", depth )
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
    print ( f" left value : { left_value } , right value : { right_value }")

    # Branch

    # Left child
    constr_name = name + str( depth )
    model . addConstr (model . getVarByName ( name ) <= left_value , constr_name)
    model . update ()
    constraint_stack . append ( model . getConstrByName ( constr_name ) )
    bnb ( model , x , depth + 1 , solution )
    model . remove ( constraint_stack . pop () )

    print (" Finished going left ")

    # Right child
    model . addConstr (model . getVarByName ( name ) >= right_value ,constr_name)
    model . update ()
    constraint_stack . append ( model . getConstrByName ( constr_name ) )
    bnb ( model , x , depth + 1 , solution )
    model . remove ( constraint_stack . pop () )

    return best_solution


def solve () :
    try :
        # Setup model for root node
        m = gp . Model (" Cutting Stock ")

        M = 100 # max number
        N = 4 # number of widths
        y = m . addVars (1 , M , vtype = GRB . BINARY )
        x = m . addVars (M , N , name ="x")

        d = [38 , 32 , 27 , 18]
        b = [84 , 60 , 30 , 20]
        D = 100

        m . addConstrs (
        sum( x [m , n ] * d [ n ] for n in range ( N ) ) <= D * y [0 , m ] for m in range ( M ))

        m . addConstrs (sum( x [m , n ] for m in range ( M ) ) == b [ n ] for n in range ( N ) )

        m . addConstrs ( y [0 , m + 1] <= y [0 , m ] for m in range ( M - 1) )

        m . setObjective (sum( y [0 , m ] for m in range ( M ) ) , GRB . MINIMIZE )

        solution = bnb (m , x , 0 , best_solution )

        print ( f" Optimal Solution : { solution }")
    except gp . GurobiError as e :
        print ('Error code ' + str( e . errno ) + ': ' + str( e ) )
    except AttributeError as e :
        print ( e )
        print ('Encountered an attribute error ')

if __name__ == '__main__':
    solve ()
