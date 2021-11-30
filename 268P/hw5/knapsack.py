from gurobipy import *
f = Model('knapsack')
x1 = f.addVar(name='x1', vtype=GRB.INTEGER)
x2 = f.addVar(name='x2', vtype=GRB.INTEGER)
x3 = f.addVar(name='x3', vtype=GRB.INTEGER)
x4 = f.addVar(name='x4', vtype=GRB.INTEGER)
x5 = f.addVar(name='x5', vtype=GRB.INTEGER)
f.addConstr(20*x1 + 75*x2 + 55*x3 + 50*x4 + 45*x5 <= 110)

f.setObjective(-5*x1-x2-2*x3-2*x4-2*x5, GRB.MINIMIZE)
f.optimize()
for v in f.getVars():
    print(v.varName, v.x)
print('Optimal val', f.objVal)


# from gurobipy import *
# f = Model('knapsack')
# x1 = f.addVar(name='x1', vtype=GRB.INTEGER)
# x2 = f.addVar(name='x2', vtype=GRB.INTEGER)
# x3 = f.addVar(name='x3', vtype=GRB.INTEGER)
# f.addConstr(x1 + 4*x2 + 9*x3 <= 10)
# f.setObjective(-4*x1-10*x2-30*x3, GRB.MINIMIZE)
# f.optimize()
# for v in f.getVars():
#     print(v.varName, v.x)
# print('Optimal val', f.objVal)