from gurobipy import *
f = Model("Furniture")
x1 = f.addVar(name="chairs")
x2 = f.addVar(name="tables")
f.setObjective(45*x1+80*x2, GRB.MAXIMIZE)
f.addConstr(5*x1+20*x2 <= 400, "mahogany")
f.addConstr(10*x1+15*x2 <= 450, "labour")
f.optimize()
for v in f.getVars():
    print(v.varName, v.x)
print('Optimal total revenue: ', f.objVal)