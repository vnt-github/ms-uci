from gurobipy import *
f = Model('Laptops')
x = f.addVar(name="num_2500_l", vtype=GRB.INTEGER)
y = f.addVar(name="num_3000_l", vtype=GRB.INTEGER)
f.setObjective(450*x + 550*y, GRB.MAXIMIZE)
f.addConstr(x + y <= 250, 'max_total_units')
f.addConstr(x >= 100, 'min_cheaper_units')
f.addConstr(x*2500 + y*3000 <= 650000)
f.optimize()
for v in f.getVars():
    print(v.varName, v.x)

print(f'Optimal total profit {f.objVal}')