from gurobipy import *
f = Model('nutrients')
x = f.addVar(name="num_x")
y = f.addVar(name="num_y")
f.setObjective(25*x+20*y, GRB.MINIMIZE)
f.addConstr(2*x+y>=12, 'min_a_nutrient')
f.addConstr(2*x+9*y >= 36 , 'min_b_nutrient')
f.addConstr(2*x+3*y >= 24 , 'min_c_nutrient')
f.optimize()
for v in f.getVars():
    print(v.varName, v.x)

print(f'Optimal total profit {f.objVal}')