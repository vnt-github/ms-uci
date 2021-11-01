import gurobipy as gp
from gurobipy import GRB


def logSolution():
    try:
        m = gp.Model("Ecotricty")

        x = m.addVars(
            ['no_type_a', 'no_type_b'],
            [1, 2, 23, 45, 56], vtype=GRB.INTEGER)

        x1 = m.addVar(name="x1", vtype=GRB.INTEGER)
        x2 = m.addVar(name="x2", vtype=GRB.INTEGER)

        m.addConstr(
        96 * x['no_type_a', 1] + 48 * x['no_type_b', 1] >= 197, "5")
        m.addConstr(
        96 * x['no_type_a', 2] + 48 * x['no_type_b', 2] >= 334, "6")
        m.addConstr(
        96 * x['no_type_a', 23] + 48 * x['no_type_b', 23] >= 436, "7")
        m.addConstr(
        96 * x['no_type_a', 45] + 48 * x['no_type_b', 45] >= 325, "8")
        m.addConstr(
        96 * x['no_type_a', 56] + 48 * x['no_type_b', 56] >= 473, "9")

        m.addConstr( x1 == x['no_type_a', 1] + x['no_type_a', 2]
        + x['no_type_a', 23] + x['no_type_a', 45] + x['no_type_a', 56],
        "10")
        m.addConstr( x2 == x['no_type_b', 1] + x['no_type_b', 2] 
        + x['no_type_b', 23] + x['no_type_b', 45] + x['no_type_b', 56],
        "11")
        
        m.addConstr(x['no_type_a', 1] <= 3, "12")
        m.addConstr(x['no_type_a', 2] <= 2, "13")
        m.addConstr(x['no_type_a', 23] <= 4, "14")
        m.addConstr(x['no_type_a', 45] <= 2, "15")
        m.addConstr(x['no_type_a', 56] <= 2, "16")

        m.addConstr(x['no_type_b', 1] <= 9, "17")
        m.addConstr(x['no_type_b', 2] <= 5, "18")
        m.addConstr(x['no_type_b', 23] <= 4, "19")
        m.addConstr(x['no_type_b', 45] <= 4, "20")
        m.addConstr(x['no_type_b', 56] <= 7, "21")

        m.setObjective(35000 * x1 + 10000 * x2, GRB.MINIMIZE)

        m.optimize()

        for key in x:
            print(f'{key}: {x[key]}')

        for v in m.getVars():
            print(v.varName, v.x)

        print(f"Optimal value of objective function z = {m.objVal}")
    except gp.GurobiError as e:
        print('GurobiError ' + str(e))

    except AttributeError:
        print('attribute error', AttributeError)


if __name__ == '__main__':
    logSolution()